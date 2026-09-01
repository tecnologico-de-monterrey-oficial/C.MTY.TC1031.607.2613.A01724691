#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

int sequentialSearch(vector<int> &v, int target) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        if (v[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(vector<int> &v, int target) {
    int low = 0;
    int high = v.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (v[mid] == target) {
            return mid;
        }
        if (v[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    srand(time(0));

    vector<int> numeros;
    for (int i = 0; i < 10000; i++) {
        numeros.push_back((rand() % 1000) * 1000 + (rand() % 1000) + 1);
    }
    sort(numeros.begin(), numeros.end());

    cout << "Se generaron 10000 numeros ordenados." << endl;
    cout << "Uno que si esta, por si lo quieres probar: " << numeros[5000] << endl;

    int numero = -1;
    while (numero != 0) {
        cout << endl << "Escribe un numero entre 1 y 1000000 (0 para salir): ";
        cin >> numero;

        if (numero != 0) {
            auto t1 = chrono::high_resolution_clock::now();
            int posSeq = sequentialSearch(numeros, numero);
            auto t2 = chrono::high_resolution_clock::now();
            int posBin = binarySearch(numeros, numero);
            auto t3 = chrono::high_resolution_clock::now();

            if (posSeq == -1 && posBin == -1) {
                cout << "El numero " << numero << " NO esta en la lista." << endl;
            } else {
                cout << "El numero " << numero << " SI esta en la lista." << endl;
            }

            cout << "Secuencial: " << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() << " nanosegundos" << endl;
            cout << "Binaria:    " << chrono::duration_cast<chrono::nanoseconds>(t3 - t2).count() << " nanosegundos" << endl;
        }
    }
    return 0;
}
