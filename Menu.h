#ifndef PEA_PROJEKT_1_MENU_H
#define PEA_PROJEKT_1_MENU_H

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include "Graph.h"
#include "Time_measure.h"
#include "DataGenerator.h"

class Menu {

public:
    void show_menu();

private:
    bool is_digit(std::string input);


};

#endif //PEA_PROJEKT_1_MENU_H