#ifndef ETAP2_SIMULATEDANNEALING_H
#define ETAP2_SIMULATEDANNEALING_H


#include "Graph.h"
#include "vector"
#include <random>

using namespace std;

class SimulatedAnnealing {

private:

    int *finalCost;
public:
    int *getFinalCost() const;

    // z matrix na graph
    Graph *getMatrixWeights() const;

    static void showPath(vector<unsigned> path);

    void showPRD(int iter);

private:
    // z matrix na graph
    Graph *matrixWeights;
    std::vector<std::vector<int>> matrix;
    vector<unsigned> *globalPath;
public:
    vector<unsigned int> *getGlobalPath() const;

private:
    void generatePath(int startingVertex, vector<unsigned int> *path, mt19937 &g);

    int calculateCost(vector<unsigned> path);

    static double coolingFunction(int delta, const double *T);

    static void calculateTemperature(double *T, double alfa);

    int swapNeighbors(vector<unsigned int> *path, int i, int j);

    void initialTemperature(double *temperature, double alfa);

    void mainLoop(double *temperature, double alfa, int iterationOfEra, int numberOfEras,
                  vector<unsigned> *p2);

    int generateRandomNeighbour(vector<unsigned int> *p2, pair<int, int> *pPair);

    static bool checkToChangeWorstSolution(int delta, double *T,  double probability);

public:

    SimulatedAnnealing(std::vector<std::vector<int>> inputGraph) {
        //z matrix na graph
        matrixWeights = new Graph(inputGraph);
        if (!matrixWeights->getGraph().empty() ){
            globalPath = new vector<unsigned>;
            finalCost = new int;
            *finalCost = 0;
            matrix = matrixWeights->getGraph();
        }
    }

    const vector<std::vector<int>> &getMatrix() const;

    SimulatedAnnealing(std::string fileName){
        std::vector<std::vector<int>> inputGraph;
        matrixWeights = new Graph(inputGraph);
        matrixWeights->readGraph(fileName);
        matrix = matrixWeights->getGraph();
        globalPath = new vector<unsigned>;
        finalCost = new int;
        *finalCost = 0;
    }

    ~SimulatedAnnealing(){
        if (!matrixWeights->getGraph().empty() ) {
            delete finalCost;
            delete globalPath;
//            matrixWeights->deleteMatrixTable(matrix);
        }
        delete matrixWeights;
    }

    void beginSimulatedAnnealing(int startingVertex, double alfa, int numberOfEras,
                                 int iterationOfEra, int startingTemperature);


};


#endif //ETAP2_SIMULATEDANNEALING_H
