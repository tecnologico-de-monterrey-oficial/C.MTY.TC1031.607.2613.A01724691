#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include <vector>
#include <string>
#include "Registro.h"
using namespace std;

void intercambiar(Registro &a, Registro &b) {
    Registro temp = a;
    a = b;
    b = temp;
}

void swapSort(vector<Registro> &v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[j].llave < v[i].llave) {
                intercambiar(v[i], v[j]);
            }
        }
    }
}

void selectionSort(vector<Registro> &v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j].llave < v[menor].llave) {
                menor = j;
            }
        }
        if (menor != i) {
            intercambiar(v[i], v[menor]);
        }
    }
}

void bubbleSort(vector<Registro> &v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j].llave > v[j + 1].llave) {
                intercambiar(v[j], v[j + 1]);
            }
        }
    }
}

void insertionSort(vector<Registro> &v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        Registro actual = v[i];
        int j = i - 1;
        while (j >= 0 && v[j].llave > actual.llave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = actual;
    }
}

void juntar(vector<Registro> &v, int inicio, int medio, int fin) {
    vector<Registro> temp;
    int i = inicio;
    int j = medio + 1;

    while (i <= medio && j <= fin) {
        if (v[i].llave <= v[j].llave) {
            temp.push_back(v[i]);
            i++;
        } else {
            temp.push_back(v[j]);
            j++;
        }
    }
    while (i <= medio) {
        temp.push_back(v[i]);
        i++;
    }
    while (j <= fin) {
        temp.push_back(v[j]);
        j++;
    }

    int total = temp.size();
    for (int k = 0; k < total; k++) {
        v[inicio + k] = temp[k];
    }
}

void mergeSortAux(vector<Registro> &v, int inicio, int fin) {
    if (inicio >= fin) {
        return;
    }
    int medio = (inicio + fin) / 2;
    mergeSortAux(v, inicio, medio);
    mergeSortAux(v, medio + 1, fin);
    juntar(v, inicio, medio, fin);
}

void mergeSort(vector<Registro> &v) {
    int n = v.size();
    mergeSortAux(v, 0, n - 1);
}

int particion(vector<Registro> &v, int inicio, int fin) {
    int medio = (inicio + fin) / 2;
    intercambiar(v[medio], v[fin]);

    long long pivote = v[fin].llave;
    int posicion = inicio;

    for (int j = inicio; j < fin; j++) {
        if (v[j].llave <= pivote) {
            if (posicion != j) {
                intercambiar(v[posicion], v[j]);
            }
            posicion++;
        }
    }
    intercambiar(v[posicion], v[fin]);
    return posicion;
}

void quickSortAux(vector<Registro> &v, int inicio, int fin) {
    if (inicio >= fin) {
        return;
    }
    int p = particion(v, inicio, fin);
    quickSortAux(v, inicio, p - 1);
    quickSortAux(v, p + 1, fin);
}

void quickSort(vector<Registro> &v) {
    int n = v.size();
    quickSortAux(v, 0, n - 1);
}

void shellSort(vector<Registro> &v) {
    int n = v.size();
    for (int salto = n / 2; salto > 0; salto = salto / 2) {
        for (int i = salto; i < n; i++) {
            Registro actual = v[i];
            int j = i;
            while (j >= salto && v[j - salto].llave > actual.llave) {
                v[j] = v[j - salto];
                j = j - salto;
            }
            v[j] = actual;
        }
    }
}

string nombreAlgoritmo(int a) {
    if (a == 1) return "swapSort";
    if (a == 2) return "selectionSort";
    if (a == 3) return "bubbleSort";
    if (a == 4) return "insertionSort";
    if (a == 5) return "mergeSort";
    if (a == 6) return "quickSort";
    if (a == 7) return "shellSort";
    return "desconocido";
}

string mejorCaso(int a) {
    if (a == 1) return "O(n^2)";
    if (a == 2) return "O(n^2)";
    if (a == 3) return "O(n^2)";
    if (a == 4) return "O(n)";
    if (a == 5) return "O(n log n)";
    if (a == 6) return "O(n log n)";
    if (a == 7) return "O(n log n)";
    return "-";
}

string peorCaso(int a) {
    if (a == 1) return "O(n^2)";
    if (a == 2) return "O(n^2)";
    if (a == 3) return "O(n^2)";
    if (a == 4) return "O(n^2)";
    if (a == 5) return "O(n log n)";
    if (a == 6) return "O(n^2)";
    if (a == 7) return "O(n^2)";
    return "-";
}

void ordenar(vector<Registro> &v, int a) {
    if (a == 1) swapSort(v);
    else if (a == 2) selectionSort(v);
    else if (a == 3) bubbleSort(v);
    else if (a == 4) insertionSort(v);
    else if (a == 5) mergeSort(v);
    else if (a == 6) quickSort(v);
    else if (a == 7) shellSort(v);
}

#endif
