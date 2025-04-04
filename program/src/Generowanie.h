//
// Created by Wojtek Białecki on 01/04/2025.
//

#ifndef GENEROWANIE_H
#define GENEROWANIE_H
#include <string>
#include <random>

template <typename T>
class Generator {
    public:

    Generator(std::string uklad) {
        this->uklad = uklad;
    }

    void generujDane(T* tablica, int n) {
        std::random_device rd;
        std::mt19937 gen(rd());

        int i = 0;
        
        if (uklad == "33") {
            while (i < n / 3) {
                tablica[i] = 0;
                i++;
            }
        }
        
        if (uklad == "66") {
            while (i < 2 * n / 3) {
                tablica[i] = 0;
                i++;
            }
        }
        
        if (uklad == "rosnaco") {
            for (int j = 0; j < n; j++) {
                tablica[j] = static_cast<T>(j + 1);
            }
            return;
        }
        
        if (uklad == "malejaco") {
            int k = n;
            for (int j = 0; j < n; j++) {
                tablica[j] = static_cast<T>(k);
                k--;
            }
            return;
        }

        // Obsługa RANDOM
        T low = 1;
        if (uklad == "33" || uklad == "66") {
            low = static_cast<T>(i + 1);
        }

        if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(low, std::numeric_limits<T>::max());
            while (i < n) {
                tablica[i] = dist(gen);
                i++;
            }
        } else {
            std::uniform_int_distribution<T> dist(low, std::numeric_limits<T>::max());
            while (i < n) {
                tablica[i] = dist(gen);
                i++;
            }
        }
    }

    private:
    std::string uklad;
};

#endif //GENEROWANIE_H
