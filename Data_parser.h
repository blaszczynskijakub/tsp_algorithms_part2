

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Data_parser {
public:
    Data_parser(std::string filename);

    ~Data_parser();
    bool openFile();
    std::vector<std::vector<int>> readFile();



private:

    const char delimiter = ':';

    std::vector<int> numbers;
    std::string filename;
    std::ifstream file;
    int dimension{};

    static std::vector<std::vector<int>> write_to_matrix(int rows, int columns, std::vector<int> &v);
};
