//
// Created by Wojtek Białecki on 01/04/2025.
//

#ifndef APLIKACJA_H
#define APLIKACJA_H

#include <string>
#include <iostream>
#include <chrono>
#include <type_traits>
#include <filesystem>

#include "Generowanie.h"
#include "ObslugaPlikow.h"
#include "ObslugaWynikow.h"
#include "Sortowanie.h"

template<typename T>
class Application {
    public:

    Application(int rozmiar,
                std::string uklad,
                std::string algorytm,
                std::string zrodlo_danych,
                std::string pivot,
                int shell_wzor) {
        this->rozmiar = rozmiar;
        this->uklad = uklad;
        this->algorytm = algorytm;
        this->zrodlo_danych = zrodlo_danych;
        this->pivot = pivot;
        this->shell_wzor = shell_wzor;
    }

    void trybTestowy() {
        T* tablica;
        Generator<T> generator = Generator<T>(uklad);
        if (zrodlo_danych == "generuj") {
            tablica = new T[rozmiar];
            generator.generujDane(tablica, rozmiar);
        } else {
            DataReader<T> reader = DataReader<T>(zrodlo_danych);
            tablica = reader.wczytajDane(rozmiar);
            if (tablica == nullptr) {
                return;
            }
        }

        T* kopia = new T[rozmiar];
        memcpy(kopia, tablica, sizeof(T) * rozmiar);

        ResultParser<T> parser = ResultParser<T>();
        if (rozmiar <= 20) {
            std::cout << "Tablica przed sortowaniem: ";
            parser.wypiszTablice(kopia, rozmiar);
        }

        const auto start = std::chrono::high_resolution_clock::now();

        if (algorytm == "wstawianie") {
            Sorter::sortowaniePrzezWstawianie(kopia, rozmiar);
        } else if (algorytm == "kopcowanie") {
            Sorter::sortowaniePrzezKopcowanie(kopia, rozmiar);
        } else if (algorytm == "shell") {
            if ((shell_wzor != 1) && (shell_wzor != 2)) {
                std::cerr << "Błąd: Nieprawidłowy wzór Shella. Dozwolone wartości: 1 lub 2." << std::endl;
                return;
            }
            Sorter::sortowanieShella(kopia, rozmiar, shell_wzor);
        } else if (algorytm == "quick") {
            Sorter::sortowanieSzybkie(kopia, 0, rozmiar - 1, pivot);
        } else {
            std::cerr << "Błąd: Nieznany algorytm sortowania!" << std::endl;
            return;
        }
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double,std::milli> elapsed_millis = end - start;
        if (rozmiar <= 20) {
            std::cout << "Tablica po sortowaniu: ";
            parser.wypiszTablice(kopia, rozmiar);
        } else {
            parser.sprawdzTablice(kopia, rozmiar);
        }
        std::cout << "Czas sortowania: " << elapsed_millis.count() << " ms" << std::endl;
    }



void uruchomSymulacje() {
    std::string folder = "wyniki";
    std::filesystem::create_directory(folder); // Tworzy folder, jeśli nie istnieje

    // Budowa nazwy pliku na podstawie parametrów
    auto format = [](const std::string& s) {
        std::string out = s;
        for (char& c : out) {
            if (c == ' ') c = '_';
        }
        return out;
    };

        std::string typDanych = getTypDanych();

        std::string nazwaPliku = folder + "/"
            + format(algorytm) + "_"
            + format(uklad) + "_"
            + format(pivot) + "_"
            + "shell" + std::to_string(shell_wzor) + "_"
            + format(typDanych) + ".txt";

    std::ofstream plikWyniki(nazwaPliku);
    if (!plikWyniki) {
        std::cerr << "Błąd: Nie można otworzyć pliku wyników!" << std::endl;
        return;
    }

    // Nagłówek pliku
    plikWyniki << "Algorytm: " << algorytm
               << ", Źródło danych: " << zrodlo_danych
               << ", Układ: " << uklad
               << ", Pivot: " << pivot
               << ", Shell wzór: " << shell_wzor << "\n\n";

    // Lista rozmiarów tablic do testowania
    std::vector<int> rozmiary = {10000, 25000, 40000, 55000, 70000, 85000, 100000};

    // Nagłówek kolumn
    for (int r : rozmiary) {
        plikWyniki << r << "\t";
    }
    plikWyniki << std::endl;

    for (int i = 0; i < 100; ++i) {
        for (int rozmiar : rozmiary) {
            T* tablica;
            Generator<T> generator(uklad);

            if (zrodlo_danych == "generuj") {
                tablica = new T[rozmiar];
                generator.generujDane(tablica, rozmiar);
            } else {
                DataReader<T> reader(zrodlo_danych);
                tablica = reader.wczytajDane(rozmiar);
                if (tablica == nullptr) {
                    return;
                }
            }

            T* kopia = new T[rozmiar];
            memcpy(kopia, tablica, sizeof(T) * rozmiar);

            auto start = std::chrono::high_resolution_clock::now();

            if (algorytm == "wstawianie") {
                Sorter::sortowaniePrzezWstawianie(kopia, rozmiar);
            } else if (algorytm == "kopcowanie") {
                Sorter::sortowaniePrzezKopcowanie(kopia, rozmiar);
            } else if (algorytm == "shell") {
                Sorter::sortowanieShella(kopia, rozmiar, shell_wzor);
            } else if (algorytm == "quick") {
                Sorter::sortowanieSzybkie(kopia, 0, rozmiar - 1, pivot);
            } else {
                std::cerr << "Błąd: Nieznany algorytm sortowania!" << std::endl;
                return;
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;

            plikWyniki << std::fixed << std::setprecision(2) << elapsed.count() << " ms" << "\t";

            delete[] kopia;
            delete[] tablica;
        }
        plikWyniki << std::endl;
    }

    plikWyniki.close();
    std::cout << "Symulacja zakończona. Wyniki zapisano w: " << nazwaPliku << std::endl;
}
private:
    int rozmiar;
    std::string uklad;
    std::string algorytm;
    std::string zrodlo_danych;
    std::string pivot;
    int shell_wzor;

    std::string getTypDanych() const {
        if (std::is_same<T, int>::value) return "int";
        else if (std::is_same<T, float>::value) return "float";
        else if (std::is_same<T, long>::value) return "long";
        else return "unknown";
    }
};

#endif //APLIKACJA_H
