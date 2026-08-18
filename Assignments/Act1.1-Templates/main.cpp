#include <iostream>
#include <string>
#include "List.h"
using namespace std;

int main() {
    List<int> lista(5);

    cout << "--- LISTA VACIA ---" << endl;
    lista.removeLast();
    lista.removeAt(0);
    lista.getMax();

    cout << endl << "--- INSERT ---" << endl;
    lista.insert(10);
    lista.insert(45);
    lista.insert(7);
    lista.print();
    cout << "getSize(): " << lista.getSize() << endl;
    cout << "getData(1): " << lista.getData(1) << endl;
    cout << "getMax(): " << lista.getMax() << endl;

    cout << endl << "--- INSERTAT ---" << endl;
    lista.insertAt(0, 99);
    lista.insertAt(2, 55);
    lista.print();
    cout << "insertAt(20, 5): ";
    lista.insertAt(20, 5);

    cout << endl << "--- LISTA LLENA ---" << endl;
    cout << "insert(777) con getSize() = " << lista.getSize() << ": ";
    lista.insert(777);

    cout << endl << "--- REMOVEAT ---" << endl;
    cout << "removeAt(0): ";
    lista.removeAt(0);
    lista.print();
    cout << "removeAt(50): ";
    lista.removeAt(50);

    cout << endl << "--- REMOVELAST ---" << endl;
    cout << "removeLast(): ";
    lista.removeLast();
    lista.print();
    cout << "getSize(): " << lista.getSize() << endl;

    cout << endl << "--- LISTA DE STRINGS ---" << endl;
    List<string> palabras(3);
    palabras.insert("Laptop");
    palabras.insert("bottle");
    palabras.insertAt(1, "cable");
    palabras.print();
    cout << "getData(0): " << palabras.getData(0) << endl;
    cout << "getMax(): " << palabras.getMax() << endl;
    cout << "removeAt(0): ";
    palabras.removeAt(0);
    cout << "removeLast(): ";
    palabras.removeLast();
    palabras.print();
    cout << "getSize(): " << palabras.getSize() << endl;

    return 0;
}
