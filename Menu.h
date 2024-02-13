#ifndef PEA_PROJEKT_1_MENU_H
#define PEA_PROJEKT_1_MENU_H

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include "Graph.h"
#include "DataGenerator.h"

class Menu {

public:
    Menu();

    void show_menu();

private:
    Graph graph;
    double stop = 120;
    double temperatureChangeCoefficient = 0.99;
    double startingTemp = 100000;
    int numberOfEras = 100000;
    int iterationsEra = 100000;

    void exit_program();

    void load_matrix_from_file();

    void generate_matrix();

    void display_matrix();

    void run_simulated_annealing();

    void set_stop_criterion();

    void set_temperature_change_coefficient();

    bool is_digit(std::string input);


};

#endif //PEA_PROJEKT_1_MENU_H