#include <iostream>
#include "Graph.h"
#include "DataGenerator.h"
#include "Time_measure.h"
#include "Write_to_csv.h"
#include "Menu.h"

int MIN = 1;
int MAX = 200;
int CITIES = 13;
int num_of_vertices;
std::vector<std::vector<int>> init_vector;

int num_of_measures = 100;
int matrix_size = 10;
std::string file_name_to_read = "../data";
std::string matrix_name = "matrix";
int path_cost;
long long time_measured;
std::string lowest_path;
std::vector<std::string> results;

int main() {
    Menu menu;
    menu.show_menu();
    //generating file
    //DataGenerator dataGenerator;
    //dataGenerator.generateData(MIN,MAX,CITIES);

    //Time_measure measure(10);
    //measure.test_brute_force(10);


    //Graph graph(x);
    //graph.readGraph("../6x6.txt");
    //graph.printGraph();
    //Brute_force force(graph.getGraph());
    //force.perform_brute_force();
    //force.show_lowest_path();
    Time_measure measure(num_of_measures);
    for (int i = 5; i < 14; i++) {
        Graph graph(init_vector);
        std::string data_variable = file_name_to_read + std::to_string(i) + ".txt";
        graph.readGraph(data_variable);



        time_measured = measure.test_brute_force(graph.getGraph());
        std::string final_name = matrix_name + std::to_string(i) + "x" + std::to_string(i);
        Write_to_csv file(final_name, lowest_path, path_cost, time_measured, num_of_measures);
        results.push_back(file.to_string());
    }
    Write_to_csv x("", "", 1, 1, 1);
    x.save_results("../wyniki.csv", results);


    return 0;
}