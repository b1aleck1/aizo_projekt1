#ifndef KONFIGURACJA_H
#define KONFIGURACJA_H

#include <map>
#include <string>
#include <fstream>
#include <iostream>

class Konfiguracja {
private:
    std::map<std::string, std::string> parametry;

public:
    bool wczytaj(const std::string& nazwaPliku);
    std::string pobierz(const std::string& klucz, const std::string& domyslna = "") const;
    int pobierzInt(const std::string& klucz, int domyslna) const;
};

#endif // KONFIGURACJA_H