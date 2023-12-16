#include <iostream>
#include <algorithm>
#include <random>
#include "SimulatedAnnealing.h"

using namespace std;

/// metoda realizujaca algorytm SA
void SimulatedAnnealing::startAlgorithm(int startingVertex, double const alfa, int numberOfEras, int iterationOfEra,
                                        int startingTemperature) {
    //pierwsza losowa sciezka, przygotowane ziarno bedzie jeszcze jeden raz uzyte wiec generujemy je tutaj zamiast w metodzie generatePath
    std::random_device rd;
    mt19937 gen(rd());
    //global path bedzie sciezka wynikowa, a finalCost kosztem naszego wyniku
    generatePath(startingVertex, globalPath, gen);
    finalCost = calculateCost(*globalPath);

    //komentowane przy pomiarach
    showPRD(0);


    temperature = startingTemperature;

    auto *nextPath = new vector<unsigned>;
    //teraz generujemy kolejna sciezke nextPath, ktora bedzie przechowywac rozpatrywane sciezki
    generatePath(startingVertex, nextPath, gen);

    mainLoop(alfa, iterationOfEra, numberOfEras, nextPath);

    //global path i final cost zostawiamy do odczytow
    delete nextPath;
}

/// generowanie  sciezki pseudolosowej
void SimulatedAnnealing::generatePath(int startingVertex, vector<unsigned int> *path, mt19937 &gen) {

    //wygenerowane sciezka bedzie miec taka dlugosc jak liczba wierzcholkow w macierzy wejsciowej
    for (int i = 0; i < matrixWeights->getNumOfVertices(); i++) {
        path->push_back(i);
    }

    uniform_int_distribution<int> shuffle_times(5, matrixWeights->getNumOfVertices() + 5);

    for (int i = 0; i < shuffle_times(gen); i++)
        shuffle(path->begin() + 1, path->end(), gen);

    path->push_back(startingVertex);

}

/// główna pętla programu
void SimulatedAnnealing::mainLoop(const double alfa, int iterationOfEra, int numberOfEras,
                                  vector<unsigned> *testedPath) {

    //przygotowanie losowosci
    random_device rd;
    default_random_engine g(rd());
    uniform_int_distribution<int> vertexToSwap(1, matrixWeights->getNumOfVertices() - 1);
    uniform_real_distribution<> generateProbability(0.0, 1.0);


    int localCost;
    int localMinCost = calculateCost(*testedPath);
    auto *edge = new pair<int, int>;


    for (int i = 0; i < numberOfEras; i++) {
        for (int j = 0; j < iterationOfEra; j++) {

            localCost = localMinCost;
            edge->first = vertexToSwap(g);
            edge->second = vertexToSwap(g);

            localCost += returnRandomNeighbour(testedPath, edge);

            if (localCost < finalCost) {
                finalCost = localCost;
                *globalPath = *testedPath;
                swap(globalPath->at(edge->first), globalPath->at(edge->second));
                showPRD(i * iterationOfEra + j);
            }

            int delta = localCost - localMinCost;

            if (delta < 0 || checkToChangeWorstSolution(delta, generateProbability(g))) {
                localMinCost = localCost;
                swap(testedPath->at(edge->first), testedPath->at(edge->second));
            }
        }
        calcTemperature(alfa);
    }
    delete edge;
}

/// wywołujemy odpowiednie podliczanie zamiany wierzchołków
int SimulatedAnnealing::returnRandomNeighbour(vector<unsigned int> *p2, pair<int, int> *c) {

    if (c->first > c->second)
        return changePath(p2, c->second, c->first);
    else
        return changePath(p2, c->first, c->second);
}

/// sprawdzamy czy z prawdopodbienstwa zaakceptujemy
bool SimulatedAnnealing::checkToChangeWorstSolution(int const delta, double probability) {

    return probability < coolingFunction(delta);
}

/// funkcja chlodzaca
void SimulatedAnnealing::calcTemperature(double const alfa) {

    temperature *= alfa;
}

/// obliczanie wzoru na prawdopodobieństwo akceptacji
double SimulatedAnnealing::coolingFunction(int const delta) const {

    return exp(-delta / (temperature));
}

/// podliczanie zamiany wierzchołków
int SimulatedAnnealing::changePath(vector<unsigned int> *path, int i, int j) {

    int subtractOldEdges = 0;
    int addNewEdges = 0;
    // jezeli sasiaduja
    if (j - i == 1) {

        subtractOldEdges += matrix[path->at(i - 1)][path->at(i)];
        subtractOldEdges += matrix[path->at(i)][path->at(j)];
        subtractOldEdges += matrix[path->at(j)][path->at(j + 1)];

        addNewEdges += matrix[path->at(i - 1)][path->at(j)];
        addNewEdges += matrix[path->at(j)][path->at(i)];
        addNewEdges += matrix[path->at(i)][path->at(j + 1)];
        // jezeli nie sasiaduja
    } else {
        subtractOldEdges += matrix[path->at(i - 1)][path->at(i)];
        subtractOldEdges += matrix[path->at(i)][path->at(i + 1)];
        subtractOldEdges += matrix[path->at(j - 1)][path->at(j)];
        subtractOldEdges += matrix[path->at(j)][path->at(j + 1)];

        addNewEdges += matrix[path->at(i - 1)][path->at(j)];
        addNewEdges += matrix[path->at(j)][path->at(i + 1)];
        addNewEdges += matrix[path->at(j - 1)][path->at(i)];
        addNewEdges += matrix[path->at(i)][path->at(j + 1)];
    }

    return addNewEdges - subtractOldEdges;
}


/// obliczanie kosztu ścieżki
int SimulatedAnnealing::calculateCost(vector<unsigned> path) {

    int cost = 0;
    auto i = path.begin();
    while (i != (path.end() - 1)) {
        cost += matrix[i.operator*()][(i + 1).operator*()];
        i.operator++();
    }
    return cost;
}

/// wyświetlanie PRD
void SimulatedAnnealing::showPRD(int iter) {
    std::cout << iter << "   " << finalCost << "   " << (((float) (finalCost - matrixWeights->getNumOfVertices())) /
                                                         (float) matrixWeights->getNumOfVertices()) << "% \n";
}

int SimulatedAnnealing::getFinalCost() const {
    return finalCost;
}


vector<unsigned int> *SimulatedAnnealing::getGlobalPath() const {
    return globalPath;
}

SimulatedAnnealing::SimulatedAnnealing(std::vector<std::vector<int>> inputGraph) {
    matrixWeights = new Graph(inputGraph);
    if (!matrixWeights->getGraph().empty()) {
        globalPath = new vector<unsigned>;
        finalCost = 0;
        matrix = matrixWeights->getGraph();
    }

}

SimulatedAnnealing::SimulatedAnnealing(std::string fileName) {

    std::vector<std::vector<int>> inputGraph;
    matrixWeights = new Graph(inputGraph);
    matrixWeights->readGraph(fileName);
    matrix = matrixWeights->getGraph();

    //przechowuje sciezke - wynik
    globalPath = new vector<unsigned>;


    finalCost = 0;

}

SimulatedAnnealing::~SimulatedAnnealing() {


    delete globalPath;
    delete matrixWeights;


}
