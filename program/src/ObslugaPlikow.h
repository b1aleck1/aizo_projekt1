//
// Created by Wojtek Białecki on 01/04/2025.
//

#ifndef OBSLUGAPLIKOW_H
#define OBSLUGAPLIKOW_H
#include <iostream>
#include <ostream>
#include <string>
#include <fstream>

template <typename T>
class DataReader {
    public:
    DataReader(const std::string nazwaPliku) {
        this->nazwaPliku = nazwaPliku;
    }

    T* wczytajDane(int& n) {
        std::ifstream plik(nazwaPliku);
        if (!plik) {
            std::cerr << "Błąd: Nie można otworzyć pliku z danymi!" << std::endl;
            return nullptr;
        }
        // odczytanie rozmiaru tablicy danych
        plik>>n;
        if (plik.fail() || n<=0) {
            std::cerr << "Błąd: Nieprawidłowy rozmiar tablicy!" << std::endl;
            return nullptr;
        }

        // odczytanie danych
        T* tablica = new T[n];
        for (int i = 0; i < n; i++) {
            if (!(plik >> tablica[i])) {
                std::cerr << "Błąd: Nie udało się odczytać danych!" << std::endl;
                delete[] tablica;
            }
        }
        std::cout << "Tablica wczytana pomyślnie." << std::endl;
        plik.close();
        return tablica;
    }

    private:
    std::string nazwaPliku;
};

#endif //OBSLUGAPLIKOW_H
