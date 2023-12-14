#include <vector>
#include <random>
#include <iostream>
#include "chrono"
#include "Time_measure.h"


Time_measure::Time_measure(int num_of_tests) {

    this->num_of_tests = num_of_tests;
}

long long Time_measure::test_brute_force_random_matrices(int matrix_size) {
    long long sum = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random(1, 200);
    std::vector<std::vector<int>> temp_matrix(matrix_size, std::vector<int>(matrix_size, 0));
    for (int t = 0; t < num_of_tests; t++) {

        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                if (i == j) {
                    temp_matrix[i][j] = -1;
                } else {
                    temp_matrix[i][j] = random(gen);
                }
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
        sum += duration.count();
    }
    long long averageTime = sum / num_of_tests;
    std::cout << "Average time taken to perform brute force " << averageTime << " microseconds.\n" << num_of_tests
              << " test done\n";
    return averageTime;
}

long long Time_measure::test_brute_force(std::vector<std::vector<int>> matrix) {
    long long sum = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random(1, 200);

    for (int t = 0; t < num_of_tests; t++) {

        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        //std::cout << "Time taken by function: " << duration.count() << " microseconds" << "\n";
        sum += duration.count();

    }
    //long long averageTime = sum / num_of_tests;
    //std::cout << "Average time taken to perform brute force " << averageTime << " microseconds.\n" << num_of_tests << " test done\n";
    return sum;
}


