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
    void generatePath(int startingVertex, vector<unsigned int> *path, mt19937 &g);
    int calculateCost(vector<unsigned> path);
    int changePath(vector<unsigned int> *path, int i, int j);
    int returnRandomNeighbour(vector<unsigned int> *p2, pair<int, int> *c);
public:
    int getFinalCost() const;
    void showPRD(int iter);
    vector<unsigned int> *getGlobalPath() const;


    SimulatedAnnealing(std::vector<std::vector<int>> inputGraph);


    SimulatedAnnealing(std::string fileName);

    ~SimulatedAnnealing();

    void startAlgorithm(int startingVertex, double alfa, int numberOfEras,
                        int iterationOfEra, int startingTemperature);

    void initialTemperature(const double alfa);

    void mainLoop(const double alfa, int iterationOfEra, int numberOfEras, vector<unsigned int> *testedPath);

    bool checkToChangeWorstSolution(const int delta, double probability);

    void calcTemperature(const double alfa);

    double coolingFunction(const int delta) const;
};


