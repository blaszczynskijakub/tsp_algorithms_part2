//
// Created by Jakub on 16.10.2023.
//
#include <iostream>

#include "OptionMenu.h"

using namespace std;

void OptionMenu::show() {

    char option;
    do {
        cout << endl;
        cout << "==== MENU GLOWNE ===" << endl;
        cout << "1.Tablica" << endl;
        cout << "2.Lista" << endl;
        cout << "3.Kopiec" << endl;
        cout << "0.Wyjscie" << endl;
        cout << "Podaj opcje:";
        cin >> option;
        cout << endl;


//            switch (option) {
//                case '1':
//                    menu_table(infile);
//                    break;
//
//                case '2':
//                    menu_list(infile);
//                    break;
//
//                case '3':
//                    menu_heap(infile);
//                    break;
//            }

    } while (option != '0');


}
