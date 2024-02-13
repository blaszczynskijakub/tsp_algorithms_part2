#include "Menu.h"
#include "Data_parser.h"
#include "SimulatedAnnealing.h"
#include <iostream>

#include <string>
#include <algorithm>

void Menu::show_menu() {
    std::string choice_s;

    while (true) {
        std::cout << "Menu: \n";
        std::cout << "1 - Load matrix from file\n";
        std::cout << "2 - Generate matrix\n";
        std::cout << "3 - Display matrix\n";
        std::cout << "4 - Run simulated annealing\n";
        std::cout << "5 - Set stop criterion\n";
        std::cout << "6 - Set temperature change coefficient\n";
        std::cout << "0 - Exit\n> ";
        std::cin >> choice_s;
        if (!is_digit(choice_s)) {
            std::cout << "Invalid input. Please enter a number.\n>";
            continue;
        }
        int choice = std::stoi(choice_s);

        switch (choice) {
            case 0:
                exit(0);
            case 1:
                load_matrix_from_file();
                break;
            case 2:
                generate_matrix();
                break;
            case 3:
                display_matrix();
                break;
            case 4:
                run_simulated_annealing();
                break;
            case 5:
                set_stop_criterion();
                break;
            case 6:
                set_temperature_change_coefficient();
                break;
            default:
                std::cout << "Invalid option.\n";
                break;
        }
    }
}


void Menu::load_matrix_from_file() {
    std::string filename;
    std::cout << "Enter filename:\n> ";
    std::cin >> filename;
    Data_parser dataParser(filename);
    if (dataParser.openFile()) {
        this->graph.setGraph(dataParser.readFile());
    } else {
        std::cout << "Failed to open file.\n";
    }
}

void Menu::generate_matrix() {
    int size;
    std::cout << "Enter matrix size:\n> ";
    std::cin >> size;
    DataGenerator generator;
    this->graph.setGraph(generator.generate_data(size));
}

void Menu::display_matrix() {
    this->graph.printGraph();
}

void Menu::run_simulated_annealing() {
    SimulatedAnnealing sa(this->graph.getGraph());
    sa.startAlgorithm(0, this->temperatureChangeCoefficient, numberOfEras, iterationsEra, startingTemp, stop);
}

void Menu::set_stop_criterion() {
    std::cout << "Enter new stop criterion:\n> ";
    std::cin >> this->stop;
}

void Menu::set_temperature_change_coefficient() {
    std::cout << "Enter new temperature change coefficient:\n> ";
    std::cin >> this->temperatureChangeCoefficient;
}

bool Menu::is_digit(std::string input) {

    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i]) == false) {
            return false;
        }
    }
    return true;

}

Menu::Menu() {}
