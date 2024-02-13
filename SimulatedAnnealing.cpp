#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "SimulatedAnnealing.h"


using namespace std;

void SimulatedAnnealing::startAlgorithm(int startingVertex, double const alfa, int numberOfEras, int iterationOfEra,
                                        int startingTemperature, double timebound) {

    std::clock_t start;
    double time = 0;
    start = std::clock();


    std::random_device rd;
    generatePath(startingVertex, globalPath);
    finalCost = calculateCost(*globalPath);


    temperature = startingTemperature;

    auto *nextPath = new vector<unsigned>;
    generatePath(startingVertex, nextPath);


    mainLoop(alfa, iterationOfEra, numberOfEras, nextPath, timebound, start);
    cout << endl << "cost: " << finalCost << endl;
    delete nextPath;
}

void SimulatedAnnealing::generatePath(int startingVertex, vector<unsigned int> *path) {

    int min = INT_MAX;
    int min_vertex = 0;
    path->push_back(0);
    int cur_vertex = 0;

    for (int i = 0; i < matrixWeights->getNumOfVertices() - 1; i++) {
        for (int j = 0; j < matrix.size(); j++) {
            if (matrix[cur_vertex][j] < min && std::find(path->begin(), path->end(), j) == path->end()) {
                min_vertex = j;
                min = matrix[cur_vertex][j];


            }
        }
        cur_vertex = min_vertex;
        path->push_back(min_vertex);
        min = INT_MAX;
    }
    path->push_back(startingVertex);

}

void SimulatedAnnealing::mainLoop(const double alfa, int iterationOfEra, int numberOfEras, vector<unsigned> *testedPath,
                                  double timebound, double start) {
    random_device rd;
    default_random_engine g(rd());
    uniform_int_distribution<int> vertexToSwap(1, matrixWeights->getNumOfVertices() - 1);
    uniform_real_distribution<> generateProbability(0.0, 1.0);

    int localMinCost = calculateCost(*testedPath);
    auto *edge = new pair<int, int>;
    double time = 0;

    while (temperature > 0.5) {
        for (int j = 0; j < iterationOfEra; j++) {
            iterationLogic(iterationOfEra, testedPath, edge, g, vertexToSwap, generateProbability, localMinCost);
        }

        if (checkTimeBound(time, timebound, start)) {
            break;
        }

        calcTemperature(alfa);
    }
    delete edge;
}

void SimulatedAnnealing::iterationLogic(int iterationOfEra, vector<unsigned> *testedPath, pair<int, int> *edge,
                                        default_random_engine &g, uniform_int_distribution<int> &vertexToSwap,
                                        uniform_real_distribution<> &generateProbability, int &localMinCost) {
    int localCost = localMinCost;
    do {
        edge->first = vertexToSwap(g);
        edge->second = vertexToSwap(g);
    } while (edge->first == edge->second);
    edge->first = vertexToSwap(g);
    edge->second = vertexToSwap(g);

    localCost += tryAnotherPath(testedPath, edge);

    if (localCost < finalCost) {
        finalCost = localCost;
        *globalPath = *testedPath;
        swap(globalPath->at(edge->first), globalPath->at(edge->second));
    }

    int delta = localCost - localMinCost;
    if (delta < 0 || checkToChangeWorstSolution(delta, generateProbability(g))) {
        localMinCost = localCost;
        swap(testedPath->at(edge->first), testedPath->at(edge->second));
    }
}

bool SimulatedAnnealing::checkTimeBound(double &time, double timebound, double start) {
    time = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    if (time >= timebound) {
        cout << "Time limit reached\n";
        return true;
    }
    return false;
}

int SimulatedAnnealing::tryAnotherPath(vector<unsigned int> *p2, pair<int, int> *c) {

    if (c->first > c->second)
        return changePath(p2, c->second, c->first);
    else
        return changePath(p2, c->first, c->second);
}

bool SimulatedAnnealing::checkToChangeWorstSolution(int const delta, double probability) {

    return probability < coolingFunction(delta);
}

void SimulatedAnnealing::calcTemperature(double const alfa) {

    temperature *= alfa;
}

double SimulatedAnnealing::coolingFunction(int const delta) const {

    return exp(-delta / (temperature));
}

int SimulatedAnnealing::subtractOldEdges(const vector<unsigned int> *path, int firstVertex, int secondVertex,
                                         bool areAdjacent) {
    int subtract = 0;
    if (areAdjacent) {
        subtract += matrix[path->at(firstVertex - 1)][path->at(firstVertex)];
        subtract += matrix[path->at(firstVertex)][path->at(secondVertex)];
        subtract += matrix[path->at(secondVertex)][path->at(secondVertex + 1)];
    } else {
        subtract += matrix[path->at(firstVertex - 1)][path->at(firstVertex)];
        subtract += matrix[path->at(firstVertex)][path->at(firstVertex + 1)];
        subtract += matrix[path->at(secondVertex - 1)][path->at(secondVertex)];
        subtract += matrix[path->at(secondVertex)][path->at(secondVertex + 1)];
    }
    return subtract;
}

int
SimulatedAnnealing::addNewEdges(const vector<unsigned int> *path, int firstVertex, int secondVertex, bool areAdjacent) {
    int add = 0;
    if (areAdjacent) {
        add += matrix[path->at(firstVertex - 1)][path->at(secondVertex)];
        add += matrix[path->at(secondVertex)][path->at(firstVertex)];
        add += matrix[path->at(firstVertex)][path->at(secondVertex + 1)];
    } else {
        add += matrix[path->at(firstVertex - 1)][path->at(secondVertex)];
        add += matrix[path->at(secondVertex)][path->at(firstVertex + 1)];
        add += matrix[path->at(secondVertex - 1)][path->at(firstVertex)];
        add += matrix[path->at(firstVertex)][path->at(secondVertex + 1)];
    }
    return add;
}


int SimulatedAnnealing::changePath(vector<unsigned int> *path, int firstVertex, int secondVertex) {

    bool areAdjacent = secondVertex - firstVertex == 1;
    int subtract = subtractOldEdges(path, firstVertex, secondVertex, areAdjacent);
    int add = addNewEdges(path, firstVertex, secondVertex, areAdjacent);
    return add - subtract;
}


int SimulatedAnnealing::calculateCost(vector<unsigned> path) {

    int cost = 0;

    for (int i = 0; i < path.size() - 1; i++) {
        cost += matrix[path.at(i)][path.at(i + 1)];
    }


    return cost;
}

void SimulatedAnnealing::showPRD(int iter) {
    cout << iter << "   " << finalCost << "   " << ((float) (finalCost - matrixWeights->getNumOfVertices()) /
                                                    ((float) matrixWeights->getNumOfVertices())) << "%" << endl;
}


SimulatedAnnealing::SimulatedAnnealing(std::vector<std::vector<int>>
                                       inputGraph) {
    matrixWeights = new Graph(inputGraph);
    if (!matrixWeights->getGraph().empty()) {
        globalPath = new vector<unsigned>;
        finalCost = 0;
        matrix = matrixWeights->getGraph();
    }

}


SimulatedAnnealing::~SimulatedAnnealing() {


    delete globalPath;
    delete matrixWeights;


}





