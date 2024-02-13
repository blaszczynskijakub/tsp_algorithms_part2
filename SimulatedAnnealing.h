#include "Graph.h"
#include "vector"
#include <random>

using namespace std;

class SimulatedAnnealing {


private:
    double temperature;

    int finalCost;
    Graph *matrixWeights;
    std::vector<std::vector<int>> matrix;
    vector<unsigned> *globalPath;

    int calculateCost(vector<unsigned> path);

    int changePath(vector<unsigned int> *path, int firstVertex, int secondVertex);

    int tryAnotherPath(vector<unsigned int> *p2, pair<int, int> *c);


    bool checkToChangeWorstSolution(const int delta, double probability);

    void calcTemperature(const double alfa);

    double coolingFunction(const int delta) const;

    void generatePath(int startingVertex, vector<unsigned int> *path);

    void showPRD(int iter);


    void
    mainLoop(const double alfa, int iterationOfEra, int numberOfEras, vector<unsigned> *testedPath,
             double timebound,
             double start);

    int subtractOldEdges(const vector<unsigned int> *path, int firstVertex, int secondVertex, bool areAdjacent);

    int addNewEdges(const vector<unsigned int> *path, int firstVertex, int secondVertex, bool areAdjacent);


    void
    iterationLogic(int iterationOfEra, vector<unsigned int> *testedPath, pair<int, int> *edge, default_random_engine &g,
                   uniform_int_distribution<int> &vertexToSwap, uniform_real_distribution<> &generateProbability,
                   int &localMinCost);

    bool checkTimeBound(double &time, double timebound, double start);

public:
    void
    startAlgorithm(int startingVertex, const double alfa, int numberOfEras, int iterationOfEra, int startingTemperature,
                   double timebound);

    SimulatedAnnealing(std::vector<std::vector<int>> inputGraph);


    ~SimulatedAnnealing();


};