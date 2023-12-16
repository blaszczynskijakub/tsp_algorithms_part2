#include "Menu.h"
#include "SimulatedAnnealing.h"

void Menu::show_menu() {
    using namespace std;
    std::vector<std::vector<int>> init_vector;
    std::vector<int> path;

    DataGenerator generator;
    Graph graph(init_vector);

    std::string fromFile;
    std::string choice_s;


    while (true) {
        std::cout
                << "Problem komiwojazera rozwiazywany metoda symulowanego wyrzazania.\nAutor: Jakub Blaszczynski #263966\n\n";
        std::cout << "0 - Wyjdz z programu\n";
        std::cout << "1 - Wczytaj macierz z pliku\n";
        std::cout << "2 - Wygeneruj macierz\n";
        std::cout << "3 - Wyswietl ostatnio wczytana z pliku lub wygenerowana macierz\n";
        std::cout << "4 - Uruchom symulowane wyrzazanie dla ostatnio wczytanej lub wygenerowanej macierzy i wyswietl wyniki\n";
        std::cout << "5 - Uruchom bnb dla ostatnio wczytanej lub wygenerowanej macierzy i wyswietl wyniki\n";

        std::cout << ">";

        std::cin >> choice_s;
        while (!is_digit(choice_s)) {
            std::cout << "Podany ciag znakow nie jest liczba!\nWpisz liczbe\n>";
            std::cin >> choice_s;
        }
        int choice = std::stoi(choice_s);

        switch (choice) {
            case 0:
                exit(0);
            case 1:

                std::cout << "Podaj nazwe pliku do wczytania\n>";
                std::cin >> choice_s;
                graph.readGraph(choice_s);

                break;
            case 2:
                std::cout << "Podaj wielkosc macierzy (rozmiar MAX_CITIES)\n>";
                std::cin >> choice_s;
                while (!is_digit(choice_s)) {
                    std::cout << "Podany ciag znakow nie jest liczba!\nWpisz liczbe\n>";
                    std::cin >> choice_s;
                }
                graph.setGraph(generator.generate_data(atoi(choice_s.c_str())));
                break;
            case 3:

                graph.printGraph();
                break;
            case 4: {
                int avg=0;
                int choice_ss = 24;
                SimulatedAnnealing simulatedAnnealing(graph.getGraph());

//                for(int h=0;h<10;h++) {

//                    graph.setGraph(generator.generate_data(choice_ss));




                    int sV, e, t, iE;
                    double a;
//                    std::cout << "Podaj startowy wierzcholek \n";
//                    cin >> sV;
//                    std::cout << "Podaj alfe \n";
//                    cin >> a;
//                    std::cout << "Podaj liczbe epok \n";
//                    cin >> e;
//                    std::cout << "Podaj liczbe iteracji w epoce \n";
//                    cin >> iE;
//                    std::cout << "Podaj startowa temperature \n";
//                    cin >> t;
//                simulatedAnnealing.startAlgorithm(sV, a, e, iE, t);
                simulatedAnnealing.startAlgorithm(0, 0.99, 100, 100, 100);


                    cout<<endl<<simulatedAnnealing.getFinalCost()<<endl;
                    for(int i=0;i<graph.getNumOfVertices()+1;i++)
                cout<<simulatedAnnealing.getGlobalPath()->at(i)<<"->";



//                    simulatedAnnealing.showPath(0);
//                cout<<endl<<simulatedAnnealing.getFinalCost()<<endl;


                    auto start = std::chrono::high_resolution_clock::now();
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    if(duration.count()> 120000) {
                        avg += 1;
                    }
//                }
            }

                break;
            case 5: {
                int choice_sss = 26;

                graph.setGraph(generator.generate_data(choice_sss));

                if (!graph.getGraph().empty()) {


                    auto start = std::chrono::high_resolution_clock::now();
                    auto end = std::chrono::high_resolution_clock::now();
                    auto durationnn = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    cout<<endl<<durationnn.count();

                } else {
                    cout << "BRAK ostatnio wczytanej lub wygenerowanej macierzy!" << endl;
                }
            }


                break;
            default:
                std::cout << "Program nie zawiera funkcji dla podanej liczby!\n";
                break;
        }
    }

}

bool Menu::is_digit(std::string input) {

    for (int i = 0; i < input.size(); i++) {
        if (isdigit(input[i]) == false) {
            return false;
        }
    }
    return true;

}