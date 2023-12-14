//
// Created by Jakub on 16.10.2023.
//

#ifndef PEA_PROJEKT_1_DATAGENERATOR_H
#define PEA_PROJEKT_1_DATAGENERATOR_H


class DataGenerator {


public:
    void generateDataToFile(int min, int max, int cities);
    std::vector<std::vector<int>> generate_data(int matrix_size);
};


#endif //PEA_PROJEKT_1_DATAGENERATOR_H
