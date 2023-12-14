#ifndef PEA_PROJEKT_1_GRAPH_H
#define PEA_PROJEKT_1_GRAPH_H

#include <vector>

class Graph {

public:
    Graph(std::vector<std::vector<int>> graph);

    ~Graph();

    int getOptimum() const;

    bool readGraph(std::string file);

    void setGraph(std::vector<std::vector<int>> new_graph);

    void printGraph();

    std::vector<std::vector<int>> getGraph();

    int getNumOfVertices() const;

private:
    std::vector<std::vector<int>> graph_matrix;
    int num_of_vertices;
    int optimum;

};

#endif //PEA_PROJEKT_1_GRAPH_H
