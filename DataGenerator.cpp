//
// Created by Jakub on 16.10.2023.
//
#include <random>
#include "DataGenerator.h"

using namespace std;




std::vector<std::vector<int>> DataGenerator::generate_data(int matrix_size) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random(1, 200);
    std::vector<std::vector<int>> temp_matrix(matrix_size, std::vector<int>(matrix_size, 0));

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            if (i == j) {
                temp_matrix[i][j] = -1;
            } else {
                temp_matrix[i][j] = random(gen);
            }
        }
    }

    return temp_matrix;
}
