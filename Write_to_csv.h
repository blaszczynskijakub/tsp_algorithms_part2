#ifndef PEA_PROJEKT_1_WRITE_TO_CSV_H
#define PEA_PROJEKT_1_WRITE_TO_CSV_H

#include <string>

class Write_to_csv {

public:
    Write_to_csv(std::string graph_name, std::string path, int path_weight, long long time, int number_of_repeats);

    void save_results(std::string results_file_name, std::vector<std::string> results);

    std::string to_string();

private:
    std::string graph_name;
    std::string path;
    int path_weight;
    long long time;
    int number_of_repeats;
};

#endif //PEA_PROJEKT_1_WRITE_TO_CSV_H
