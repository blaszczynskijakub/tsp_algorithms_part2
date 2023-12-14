//
// Created by Jakub on 29.03.2023.
//

#include <sstream>
#include "FileReader.h"

using namespace std;


bool FileReader::file_read_line(ifstream &file, int tab[], int size) {
    string s;
    getline(file, s);

    if (file.fail() || s.empty())
        return (false);

    istringstream in_ss(s);

    for (int i = 0; i < size; i++) {
        in_ss >> tab[i];
        if (in_ss.fail())
            return (false);
    }
    return (true);

}
