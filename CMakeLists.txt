cmake_minimum_required(VERSION 3.24)
project(pea_projekt_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(pea_projekt_1 main.cpp DataGenerator.cpp DataGenerator.h
        Data_parser.h
        Data_parser.cpp
        Graph.h
        Graph.cpp
        Menu.cpp SimulatedAnnealing.h SimulatedAnnealing.cpp)
