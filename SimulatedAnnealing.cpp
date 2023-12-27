#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "SimulatedAnnealing.h"

double calculateTemperature();

using namespace std;

/// metoda realizujaca algorytm SA
void SimulatedAnnealing::startAlgorithm(int startingVertex, double const alfa, int numberOfEras, int iterationOfEra,
                                        int startingTemperature, double timebound) {

    std::clock_t start;
    double time = 0;
    double finalTime = 0;
    start = std::clock();



    //pierwsza losowa sciezka, przygotowane ziarno bedzie jeszcze jeden raz uzyte wiec generujemy je tutaj zamiast w metodzie generatePath
    std::random_device rd;
    mt19937 gen(rd());
    //global path bedzie sciezka wynikowa, a finalCost kosztem naszego wyniku
    generatePath(startingVertex, globalPath);
    finalCost = calculateCost(*globalPath);

    //komentowane przy pomiarach
    showPRD(0);


    temperature = startingTemperature;

    auto *nextPath = new vector<unsigned>;
    //teraz generujemy kolejna sciezke nextPath, ktora bedzie przechowywac rozpatrywane sciezki
    generatePath(startingVertex, nextPath);


    mainLoop(alfa, iterationOfEra, numberOfEras, nextPath, timebound, time, start);

    //global path i final cost zostawiamy do odczytow
    delete nextPath;
}

/// generowanie  sciezki pseudolosowej
void SimulatedAnnealing::generatePath(int startingVertex, vector<unsigned int> *path) {

    int min = INT_MAX;
    int min_vertex = 0;
    //wygenerowane sciezka bedzie miec taka dlugosc jak liczba wierzcholkow w macierzy wejsciowej
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
//    for (int u = 0; u < path->size(); u++)
//        cout << path->at(u) << endl;
//    cout << endl << endl;
}

/// główna pętla programu
void SimulatedAnnealing::mainLoop(const double alfa, int iterationOfEra, int numberOfEras,
                                  vector<unsigned> *testedPath, double timebound, double time, double start) {

    //przygotowanie losowosci
    random_device rd;
    default_random_engine g(rd());
    uniform_int_distribution<int> vertexToSwap(1, matrixWeights->getNumOfVertices() - 1);
    uniform_real_distribution<> generateProbability(0.0, 1.0);


    int localCost;
    int localMinCost = calculateCost(*testedPath);
    auto *edge = new pair<int, int>;


    while(temperature>0.5) {
        for (int j = 0; j < iterationOfEra; j++) {

            localCost = localMinCost;
            edge->first = vertexToSwap(g);
            edge->second = vertexToSwap(g);

            localCost += tryAnotherPath(testedPath, edge);
//            cout<<localCost<<" "<<finalCost<<endl;

            //nowa sciezka lepsza
            if (localCost < finalCost) {
                finalCost = localCost;
                *globalPath = *testedPath;
                //zmieniamy sciezke na nowa
                swap(globalPath->at(edge->first), globalPath->at(edge->second));
                showPRD(  iterationOfEra + j);
            }

            int delta = localCost - localMinCost;
            if (delta < 0 || checkToChangeWorstSolution(delta, generateProbability(g))) {
                localMinCost = localCost;

                //zmieniamy sciezke na nowa
                swap(testedPath->at(edge->first), testedPath->at(edge->second));
            }

        }
        time = (std::clock() - start) / (double) CLOCKS_PER_SEC;

        if (time >= timebound) {
            cout<<"Koniec czasu";
            return;
        }

        calcTemperature(alfa);
    }
    delete edge;
}

/// sprawdzamy inna sciezke
int SimulatedAnnealing::tryAnotherPath(vector<unsigned int> *p2, pair<int, int> *c) {

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

/// wzor z algorytmu co do akceptacji zeby wyjsc lokalnego optimum
double SimulatedAnnealing::coolingFunction(int const delta) const {

    return exp(-delta / (temperature));
}

/// podliczanie zamiany wierzcholkow
int SimulatedAnnealing::changePath(vector<unsigned int> *path, int firstVertex, int secondVertex) {

    int subtractOldEdges = 0;
    int addNewEdges = 0;
    // jezeli sasiaduja
    if (secondVertex - firstVertex == 1) {

        subtractOldEdges += matrix[path->at(firstVertex - 1)][path->at(firstVertex)];
        subtractOldEdges += matrix[path->at(firstVertex)][path->at(secondVertex)];
        subtractOldEdges += matrix[path->at(secondVertex)][path->at(secondVertex + 1)];

        addNewEdges += matrix[path->at(firstVertex - 1)][path->at(secondVertex)];
        addNewEdges += matrix[path->at(secondVertex)][path->at(firstVertex)];
        addNewEdges += matrix[path->at(firstVertex)][path->at(secondVertex + 1)];
        // jezeli nie sasiaduja
    } else {
        subtractOldEdges += matrix[path->at(firstVertex - 1)][path->at(firstVertex)];
        subtractOldEdges += matrix[path->at(firstVertex)][path->at(firstVertex + 1)];
        subtractOldEdges += matrix[path->at(secondVertex - 1)][path->at(secondVertex)];
        subtractOldEdges += matrix[path->at(secondVertex)][path->at(secondVertex + 1)];

        addNewEdges += matrix[path->at(firstVertex - 1)][path->at(secondVertex)];
        addNewEdges += matrix[path->at(secondVertex)][path->at(firstVertex + 1)];
        addNewEdges += matrix[path->at(secondVertex - 1)][path->at(firstVertex)];
        addNewEdges += matrix[path->at(firstVertex)][path->at(secondVertex + 1)];
    }

    //wartosc zmiany
    return addNewEdges - subtractOldEdges;
}


/// koszt sciezki
int SimulatedAnnealing::calculateCost(vector<unsigned> path) {

    int cost = 0;

    for (int i = 0; i < path.size() - 1; i++) {
        cost += matrix[path.at(i)][path.at(i + 1)];
    }


    return cost;
}

/// wyświetlanie PRD
void SimulatedAnnealing::showPRD(int iter) {
    cout << iter << "   " << finalCost << "   " << ((float )(finalCost - matrixWeights->getNumOfVertices()) /
            ((float) matrixWeights->getNumOfVertices())) << "%" << endl;
}

int SimulatedAnnealing::getFinalCost() const {
    return finalCost;
}


vector<unsigned int> *SimulatedAnnealing::getGlobalPath() const {
    return globalPath;
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


SimulatedAnnealing::~SimulatedAnnealing()
{


    delete globalPath;
    delete matrixWeights;


}


double SimulatedAnnealing::calculateTemperature()
{
    vector<unsigned >* pathTwo;
    vector<unsigned > *pathOne;

    generatePath(0, pathOne);

    int buffer = 0;
    auto *edge = new pair<int, int>;
    random_device rd;
    default_random_engine g(rd());
    uniform_int_distribution<int> vertexToSwap(1, matrixWeights->getNumOfVertices() - 1);
int cost;

   int  firstCost = calculateCost(*pathOne);
    for (int i = 0; i < 10000; i++)
    {

            edge->first = vertexToSwap(g);
            edge->second = vertexToSwap(g);

            cost += tryAnotherPath(pathOne, edge);


        buffer += cost;

    }

    buffer /= 10000;

    return (-1*buffer)/log(0.99);
}

double SimulatedAnnealing::getTemperature() const {
    return temperature;
}

void SimulatedAnnealing::setTemperature(double temperature) {
    SimulatedAnnealing::temperature = temperature;
}
