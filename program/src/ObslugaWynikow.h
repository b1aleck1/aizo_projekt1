//
// Created by Wojtek Białecki on 01/04/2025.
//

#ifndef OBSLUGAWYNIKOW_H
#define OBSLUGAWYNIKOW_H
#include <iostream>
#include <ostream>

template<typename T>
class ResultParser {
    public:

    void sprawdzTablice(const T* tablica, int n) {
        for (int i = 0; i < n-1; i++) {
            if (tablica[i] > tablica[i+1]) {
                std::cout << "Tablica nie jest poprawnie posortowana." << std::endl;
                return;
            }
        }
        std::cout << "Tablica jest posortowana poprawnie." << std::endl;
    }

    void wypiszTablice(const T* tablica, int n) {
        for (int i = 0; i < n; i++) {
            std::cout << tablica[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif //OBSLUGAWYNIKOW_H
