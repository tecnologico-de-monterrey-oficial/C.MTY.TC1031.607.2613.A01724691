#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class List {
private:
    vector<T> data;
    int size;

public:
    List(int capacidad = 10) {
        data.resize(capacidad);
        size = 0;
    }

    int getSize() {
        return size;
    }

    void insert(T valor) {
        if (size == (int)data.size()) {
            cout << "LISTA LLENA" << endl;
            return;
        }
        data[size] = valor;
        size++;
    }

    void removeLast() {
        if (size == 0) {
            cout << "NO HAY ELEMENTOS" << endl;
            return;
        }
        cout << data[size - 1] << endl;
        size--;
    }

    T getData(int pos) {
        if (pos < 0 || pos >= size) {
            cout << "POSICIÓN INVÁLIDA" << endl;
            return T();
        }
        return data[pos];
    }

    T getMax() {
        if (size == 0) {
            cout << "NO HAY ELEMENTOS" << endl;
            return T();
        }
        T mayor = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > mayor) {
                mayor = data[i];
            }
        }
        return mayor;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] - " << data[i] << endl;
        }
    }

    void insertAt(int pos, T valor) {
        if (pos < 0 || pos > size) {
            cout << "POSICIÓN INVÁLIDA" << endl;
            return;
        }
        if (size == (int)data.size()) {
            cout << "LISTA LLENA" << endl;
            return;
        }
        for (int i = size; i > pos; i--) {
            data[i] = data[i - 1];
        }
        data[pos] = valor;
        size++;
    }

    void removeAt(int pos) {
        if (size == 0) {
            cout << "NO HAY ELEMENTOS" << endl;
            return;
        }
        if (pos < 0 || pos >= size) {
            cout << "POSICIÓN INVÁLIDA" << endl;
            return;
        }
        cout << data[pos] << endl;
        for (int i = pos; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }si borro 
};

#endif
