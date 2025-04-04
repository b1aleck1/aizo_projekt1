#include "Konfiguracja.h"

bool Konfiguracja::wczytaj(const std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);
    if (!plik) {
        std::cerr << "Błąd: Nie można otworzyć pliku konfiguracyjnego!" << std::endl;
        return false;
    }

    std::string klucz, wartosc;
    while (plik >> klucz >> wartosc) {
        parametry[klucz] = wartosc;
    }

    // Sprawdzenie wymaganych parametrów
    if (parametry.find("algorytm") == parametry.end() || parametry["algorytm"].empty()) {
        std::cerr << "Błąd: Musisz podać algorytm sortowania w pliku konfiguracyjnym!" << std::endl;
        return false;
    }

    if (parametry["algorytm"] == "shell") {
        int shellWzor = pobierzInt("shell_wzor", -1);
        if (shellWzor != 1 && shellWzor != 2) {
            std::cerr << "Błąd: Wartość 'shell_wzor' musi być 1 lub 2!" << std::endl;
            return false;
        }
    }

    return true;
}

std::string Konfiguracja::pobierz(const std::string& klucz, const std::string& domyslna) const {
    auto it = parametry.find(klucz);
    return (it != parametry.end()) ? it->second : domyslna;
}

int Konfiguracja::pobierzInt(const std::string& klucz, int domyslna) const {
    auto it = parametry.find(klucz);
    if (it != parametry.end()) {
        try {
            return std::stoi(it->second);
        } catch (...) {
            std::cerr << "Błąd: Niepoprawna wartość dla '" << klucz << "' w pliku konfiguracyjnym!" << std::endl;
            return domyslna;
        }
    }
    return domyslna;
}