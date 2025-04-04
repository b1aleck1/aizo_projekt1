#include <iostream>

#include "Aplikacja.h"
#include "Konfiguracja.h"

int main() {
    Konfiguracja config;
    if (!config.wczytaj("./data/config.txt")) {
        std::cerr << "Błąd: Nie można wczytać pliku konfiguracyjnego!" << std::endl;
        return 1;
    }

    std::string tryb = config.pobierz("tryb", "symulacja");
    int rozmiar = config.pobierzInt("rozmiar", 100);
    std::string typ_danych = config.pobierz("typ_danych", "int");
    std::string uklad = config.pobierz("uklad_tablicy", "losowy");
    std::string algorytm = config.pobierz("algorytm", "");
    std::string zrodlo_danych = config.pobierz("zrodlo_danych", "generuj");
    int shell_wzor = config.pobierzInt("shell_wzor", 1);
    std::string pivot = config.pobierz("pivot", "prawy");

    if (typ_danych == "int") {
        Application<int> app = Application<int>(rozmiar, uklad, algorytm, zrodlo_danych, pivot, shell_wzor);
        if (tryb == "test") {
            app.trybTestowy();
        } else if (tryb == "symulacja") {
            app.uruchomSymulacje();
        } else {
            std::cerr << "Blad: Nieprawidlowy tryb aplikacji: " << tryb << std::endl;
            return 1;
        }
    } else if (typ_danych == "float") {
        Application<float> app = Application<float>(rozmiar, uklad, algorytm, zrodlo_danych, pivot, shell_wzor);
        if (tryb == "test") {
            app.trybTestowy();
        } else if (tryb == "symulacja") {
            app.uruchomSymulacje();
        } else {
            std::cerr << "Blad: Nieprawidlowy tryb aplikacji: " << tryb << std::endl;
            return 1;
        }
    } else if (typ_danych == "long") {
        Application<long> app = Application<long>(rozmiar, uklad, algorytm, zrodlo_danych, pivot, shell_wzor);
        if (tryb == "test") {
            app.trybTestowy();
        } else if (tryb == "symulacja") {
            app.uruchomSymulacje();
        } else {
            std::cerr << "Blad: Nieprawidlowy tryb aplikacji: " << tryb << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Blad: Nieprawidlowy typ danych: " << typ_danych << std::endl;
        return 1;
    }

    return 0;
}
