#ifndef SORTOWANIE_H
#define SORTOWANIE_H

#include <algorithm>
#include <ranges>

class Sorter {
public:
    // Sortowanie przez wstawianie
    template <typename T>
    static void sortowaniePrzezWstawianie(T* tablica, int n) {
        for (int i = 1; i < n; i++) {
            T klucz = tablica[i];
            int j = i - 1;
            while (j >= 0 && tablica[j] > klucz) {
                tablica[j + 1] = tablica[j];
                j--;
            }
            tablica[j + 1] = klucz;
        }
    }

    // Rekurencyjna implementacja QuickSorta
    template <typename T>
    static void sortowanieSzybkie(T* tablica, int lewy, int prawy, const std::string& metoda) {
        if (lewy < prawy) {
            int pivotIndex = partition(tablica, lewy, prawy, metoda);
            sortowanieSzybkie(tablica, lewy, pivotIndex - 1, metoda);
            sortowanieSzybkie(tablica, pivotIndex + 1, prawy, metoda);
        }
    }

    template <typename T>
    static void sortowaniePrzezKopcowanie(T* tablica, int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(tablica, n, i);
        for (int i = n - 1; i > 0; i--) {
            std::swap(tablica[0], tablica[i]);
            heapify(tablica, i, 0);
        }
    }

    // Funkcja sortująca metodą Shell Sort z wybranym wzorem odstępów
    template <typename T>
    static void sortowanieShella(T* tablica, int n, int tryb) {
        std::vector<int> gaps;

        if (tryb == 2) {
            // Generowanie ciągu Hibbarda: 1, 3, 7, 15, 31, ...
            for (int k = 1; (1 << k) - 1 < n; k++) {
                gaps.push_back((1 << k) - 1); // 2^k - 1
            }
            std::ranges::reverse(gaps);
        } else if (tryb == 1) {
            // Standardowy ciąg Shella: N/2, N/4, ..., 1
            for (int h = n / 2; h > 0; h /= 2) {
                gaps.push_back(h);
            }
        }

        for (int gap : gaps) {
            for (int i = gap; i < n; i++) {
                T temp = tablica[i];
                int j;
                for (j = i; j >= gap && tablica[j - gap] > temp; j -= gap) {
                    tablica[j] = tablica[j - gap];
                }
                tablica[j] = temp;
            }
        }
    }

private:

    template <typename T>
    static void heapify(T* tablica, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && tablica[l] > tablica[largest])
            largest = l;
        if (r < n && tablica[r] > tablica[largest])
            largest = r;
        if (largest != i) {
            std::swap(tablica[i], tablica[largest]);
            heapify(tablica, n, largest);
        }
    }

    // Funkcja pomocnicza do podziału tablicy na podstawie pivota
    template <typename T>
 static int partition(T* tablica, int lewy, int prawy, const std::string& metoda) {
        int pivotIndex = prawy; // Domyślnie ostatni element

        if (metoda == "lewy") {
            pivotIndex = lewy;
        } else if (metoda == "srodkowy") {
            pivotIndex = (lewy + prawy) / 2;
        } else if (metoda == "losowy") {
            pivotIndex = lewy + rand() % (prawy - lewy + 1);
        } else if (metoda == "prawy") {
            pivotIndex = prawy;
        } else {
            static bool pokazanoBlad = false;
            if (!pokazanoBlad) {
                std::cerr << "Nieznana metoda wyboru pivota: " << metoda << ", używam 'prawy'" << std::endl;
                pokazanoBlad = true;
            }
            pivotIndex = prawy;
        }

        // Przenosimy pivot na koniec
        std::swap(tablica[pivotIndex], tablica[prawy]);
        T pivot = tablica[prawy];

        int i = lewy - 1;
        for (int j = lewy; j < prawy; j++) {
            if (tablica[j] < pivot) {
                i++;
                std::swap(tablica[i], tablica[j]);
            }
        }
        std::swap(tablica[i + 1], tablica[prawy]);
        return i + 1;
    }


};
#endif // SORTOWANIE_H
