#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

string nombres[7] = {"swapSort", "selectionSort", "bubbleSort", "insertionSort", "mergeSort", "quickSort", "shellSort"};
int tamanos[3] = {1000, 10000, 100000};

vector<int> listaInt[3];
vector<double> listaDouble[3];
vector<string> listaString[3];

template <typename T>
void intercambiar(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void print(vector<T> &v) {
    int n = v.size();
    int limite = 20;
    if (n < limite) {
        limite = n;
    }
    for (int i = 0; i < limite; i++) {
        cout << v[i] << " ";
    }
    cout << "... (primeros " << limite << " de " << n << ")" << endl;
}

template <typename T>
void swapSort(vector<T> &v, long long &comparaciones, long long &intercambios) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            comparaciones++;
            if (v[j] < v[i]) {
                intercambiar(v[i], v[j]);
                intercambios++;
            }
        }
    }
}

template <typename T>
void selectionSort(vector<T> &v, long long &comparaciones, long long &intercambios) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            comparaciones++;
            if (v[j] < v[menor]) {
                menor = j;
            }
        }
        if (menor != i) {
            intercambiar(v[i], v[menor]);
            intercambios++;
        }
    }
}

template <typename T>
void bubbleSort(vector<T> &v, long long &comparaciones, long long &intercambios) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparaciones++;
            if (v[j] > v[j + 1]) {
                intercambiar(v[j], v[j + 1]);
                intercambios++;
            }
        }
    }
}

template <typename T>
void insertionSort(vector<T> &v, long long &comparaciones, long long &intercambios) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        T actual = v[i];
        int j = i - 1;
        while (j >= 0) {
            comparaciones++;
            if (v[j] <= actual) {
                break;
            }
            v[j + 1] = v[j];
            intercambios++;
            j--;
        }
        v[j + 1] = actual;
    }
}

template <typename T>
void juntar(vector<T> &v, int inicio, int medio, int fin) {
    vector<T> temp;
    int i = inicio;
    int j = medio + 1;

    while (i <= medio && j <= fin) {
        if (v[i] <= v[j]) {
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

template <typename T>
void mergeSortAux(vector<T> &v, int inicio, int fin) {
    if (inicio >= fin) {
        return;
    }
    int medio = (inicio + fin) / 2;
    mergeSortAux(v, inicio, medio);
    mergeSortAux(v, medio + 1, fin);
    juntar(v, inicio, medio, fin);
}

template <typename T>
void mergeSort(vector<T> &v) {
    int n = v.size();
    mergeSortAux(v, 0, n - 1);
}

template <typename T>
int particion(vector<T> &v, int inicio, int fin) {
    T pivote = v[fin];
    int posicion = inicio;

    for (int j = inicio; j < fin; j++) {
        if (v[j] <= pivote) {
            intercambiar(v[posicion], v[j]);
            posicion++;
        }
    }
    intercambiar(v[posicion], v[fin]);
    return posicion;
}

template <typename T>
void quickSortAux(vector<T> &v, int inicio, int fin) {
    if (inicio >= fin) {
        return;
    }
    int p = particion(v, inicio, fin);
    quickSortAux(v, inicio, p - 1);
    quickSortAux(v, p + 1, fin);
}

template <typename T>
void quickSort(vector<T> &v) {
    int n = v.size();
    quickSortAux(v, 0, n - 1);
}

template <typename T>
void shellSort(vector<T> &v) {
    int n = v.size();
    for (int salto = n / 2; salto > 0; salto = salto / 2) {
        for (int i = salto; i < n; i++) {
            T actual = v[i];
            int j = i;
            while (j >= salto && v[j - salto] > actual) {
                v[j] = v[j - salto];
                j = j - salto;
            }
            v[j] = actual;
        }
    }
}

template <typename T>
long long aplicar(vector<T> &v, int algoritmo, long long &comparaciones, long long &intercambios) {
    comparaciones = 0;
    intercambios = 0;

    auto inicio = chrono::high_resolution_clock::now();
    if (algoritmo == 1) {
        swapSort(v, comparaciones, intercambios);
    } else if (algoritmo == 2) {
        selectionSort(v, comparaciones, intercambios);
    } else if (algoritmo == 3) {
        bubbleSort(v, comparaciones, intercambios);
    } else if (algoritmo == 4) {
        insertionSort(v, comparaciones, intercambios);
    } else if (algoritmo == 5) {
        mergeSort(v);
    } else if (algoritmo == 6) {
        quickSort(v);
    } else if (algoritmo == 7) {
        shellSort(v);
    }
    auto fin = chrono::high_resolution_clock::now();

    return chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();
}

template <typename T>
void ordenarYMostrar(vector<T> &original, int algoritmo) {
    vector<T> v = original;
    long long comparaciones;
    long long intercambios;
    long long tiempo = aplicar(v, algoritmo, comparaciones, intercambios);

    cout << "Lista ordenada: ";
    print(v);
    cout << "Tiempo: " << tiempo << " nanosegundos" << endl;
    if (algoritmo <= 4) {
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Intercambios: " << intercambios << endl;
    }
}

template <typename T>
long long soloTiempo(vector<T> &original, int algoritmo) {
    vector<T> v = original;
    long long comparaciones;
    long long intercambios;
    return aplicar(v, algoritmo, comparaciones, intercambios);
}

void mostrarOrdenamiento(int algoritmo, int tipo, int t) {
    if (tipo == 1) {
        ordenarYMostrar(listaInt[t], algoritmo);
    } else if (tipo == 2) {
        ordenarYMostrar(listaDouble[t], algoritmo);
    } else {
        ordenarYMostrar(listaString[t], algoritmo);
    }
}

long long medirTiempo(int algoritmo, int tipo, int t) {
    if (tipo == 1) {
        return soloTiempo(listaInt[t], algoritmo);
    } else if (tipo == 2) {
        return soloTiempo(listaDouble[t], algoritmo);
    } else {
        return soloTiempo(listaString[t], algoritmo);
    }
}

void crearListas() {
    for (int t = 0; t < 3; t++) {
        listaInt[t].clear();
        listaDouble[t].clear();
        listaString[t].clear();

        for (int i = 0; i < tamanos[t]; i++) {
            listaInt[t].push_back(rand() % 100000);
            listaDouble[t].push_back((rand() % 100000) / 100.0);

            string palabra = "";
            for (int j = 0; j < 5; j++) {
                char letra = 'A' + rand() % 26;
                palabra += letra;
            }
            listaString[t].push_back(palabra);
        }
    }
    cout << "Listas creadas de 1000, 10000 y 100000 para int, double y string." << endl;
}

void analisisComparativo() {
    string tipos[3] = {"int", "double", "string"};

    cout << endl << "Esto tarda varios minutos, no se trabo. Espera..." << endl;
    cout << endl << "algoritmo, tipo de dato, tiempo1000, tiempo10000, tiempo100000" << endl;

    for (int algoritmo = 1; algoritmo <= 7; algoritmo++) {
        for (int tipo = 1; tipo <= 3; tipo++) {
            cout << nombres[algoritmo - 1] << ", " << tipos[tipo - 1];
            for (int t = 0; t < 3; t++) {
                cout << ", " << medirTiempo(algoritmo, tipo, t);
            }
            cout << endl;
        }
    }
}

void mostrarMenu() {
    cout << endl << "----- MENU -----" << endl;
    cout << "1. Crear las listas otra vez" << endl;
    for (int i = 0; i < 7; i++) {
        cout << i + 2 << ". " << nombres[i] << endl;
    }
    cout << "9. Analisis comparativo" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}

int main() {
    srand(time(0));
    crearListas();

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            crearListas();
        } else if (opcion >= 2 && opcion <= 8) {
            int tipo;
            int tam;
            cout << "Tipo (1=int, 2=double, 3=string): ";
            cin >> tipo;
            cout << "Tamano (1=1000, 2=10000, 3=100000): ";
            cin >> tam;

            if (tipo < 1 || tipo > 3 || tam < 1 || tam > 3) {
                cout << "Opcion invalida." << endl;
            } else {
                mostrarOrdenamiento(opcion - 1, tipo, tam - 1);
            }
        } else if (opcion == 9) {
            analisisComparativo();
        } else if (opcion == 0) {
            cout << "Adios." << endl;
        } else {
            cout << "Opcion invalida." << endl;
        }
    }
    return 0;
}
