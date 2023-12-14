#include "Data_parser.h"
#include <algorithm>

#include <utility>
#include <sstream>
#include <iterator>


Data_parser::Data_parser(std::string filename) {

    this->filename = std::move(filename);

}

Data_parser::~Data_parser() {
    if (file.is_open()) {
        file.close();
    }
}

bool Data_parser::openFile() {
    file.open(filename);
    return file.is_open();
}

std::vector<std::vector<int>> Data_parser::readFile() {
    if (file.is_open()) {
        std::string line;
        bool isMatrix = false;
        while (std::getline(file, line)) {

            if (line == "EDGE_WEIGHT_SECTION") {
                isMatrix = true;
            }
            if (line.find(delimiter) != std::string::npos) {
                std::string keyword = line.substr(0, line.find(delimiter));
                std::string value = line.substr(line.find(delimiter) + 1, std::string::npos);
                if (keyword == "DIMENSION") {
                    dimension = std::stoi(value);
                }
            }

            if (isMatrix) {
                std::stringstream stream(line);
                int n;
                while (stream >> n) {
                    this->numbers.push_back(n);
                }
            }
        }

        std::vector<std::vector<int>> matrix = write_to_matrix(dimension, dimension, numbers);
        file.close();
        return matrix;
    } else {
        std::cerr << "Failed to open the file: " << filename << "\n";
    }
    return {};
}

std::vector<std::vector<int>> Data_parser::write_to_matrix(int rows, int columns, std::vector<int> &v) {
    std::vector<std::vector<int>> matrix(columns, std::vector<int>(rows)); // Initialize matrix with rows and columns
    auto iter = v.begin();
    for (int y = 0; y < columns; ++y) {
        for (int x = 0; x < rows; ++x) {
            if (iter != v.end()) {
                matrix[y][x] = *iter; // Assign the element to the matrix
                iter++;
            } else {
                // Handle the case where there are not enough elements in the input vector
                // You can throw an exception or handle it according to your application's logic
            }
        }
    }
    return matrix;
}