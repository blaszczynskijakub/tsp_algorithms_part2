#include <iostream>
#include <fstream>
#include "Graph.h"

Graph::Graph(std::vector<std::vector<int>> graph) {

    this->graph_matrix = graph;
    this->num_of_vertices = graph_matrix.size();
}

Graph::~Graph() = default;

bool Graph::readGraph(std::string fileName) {

    std::ifstream file(fileName);
    if (!file) {
        std::cout << "Error: Unable to open a file\n";
    } else {
        file >> num_of_vertices;
        if (!file || this->num_of_vertices > 1) {
            std::vector<std::vector<int>> temp(num_of_vertices, std::vector<int>(num_of_vertices, 0));
            for (int i = 0; i < this->num_of_vertices; i++) {
                for (int j = 0; j < this->num_of_vertices; j++) {
                    file >> temp[i][j];
                }
            }

            graph_matrix = temp;
        } else {
            std::cout << "Error: Amount of vertices given incorrectly\n";
            return false;
        }
    }

    return true;
}

int Graph::getNumOfVertices() const {
    return num_of_vertices;
}

void Graph::setGraph(std::vector<std::vector<int>> new_graph) {
    this->graph_matrix = new_graph;
    this->num_of_vertices = graph_matrix.size();
}

void Graph::printGraph() {

    if (!graph_matrix.empty()) {
        for (int i = 0; i < this->num_of_vertices; i++) {
            for (int j = 0; j < this->num_of_vertices; j++) {
                std::cout << graph_matrix[i][j] << "\t";
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "Graph is empty!\n";
    }

}

std::vector<std::vector<int>> Graph::getGraph() {
    return this->graph_matrix;
}

Graph::Graph() {}



