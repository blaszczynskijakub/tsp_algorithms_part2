
#include <iostream>
#include <fstream>
#include <vector>
#include "Write_to_csv.h"

Write_to_csv::Write_to_csv(std::string graph_name, std::string path, int path_weight, long long int time,
                           int number_of_repeats) {

    this->graph_name = graph_name;
    this->path = path;
    this->path_weight = path_weight;
    this->time = time;
    this->number_of_repeats = number_of_repeats;

}

void Write_to_csv::save_results(std::string results_file_name, std::vector<std::string> results) {


    std::cout << "Saving results\n";
    std::fstream file_out;
    file_out.open(results_file_name, std::ios::out);
    if (file_out.is_open()) {
        file_out << "graph_name,path,path_weight,time,number_of_repeats\n";
        for (int i = 0; i < results.size(); i++) {
            file_out << results[i] << "\n";
        }
        file_out.close();
        std::cout << "Correctly saved " << results.size() << " results\n";
    } else {
        std::cerr << "Error opening the file: " << results_file_name << std::endl;
    }


}

std::string Write_to_csv::to_string() {
    return (graph_name + "," + path + "," + std::to_string(path_weight) + "," + std::to_string(time) + "," +
            std::to_string(number_of_repeats));
}



