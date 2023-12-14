//
// Created by Jakub on 29.03.2023.
//
#include <fstream>
#include <iostream>

#ifndef SDIZO_PROJEKT_FILEREADER_H
#define SDIZO_PROJEKT_FILEREADER_H

class FileReader {
public:
    static bool file_read_line(std::ifstream &file, int tab[], int size);


};


#endif //SDIZO_PROJEKT_FILEREADER_H
