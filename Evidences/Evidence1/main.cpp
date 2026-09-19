// Evidencia 1 - Parte 1: Entrada (lectura, almacenamiento y ordenamiento cronologico)
// A01724691
// Lee cualquiera de los dos archivos de log, guarda los registros en un vector
// y los ordena por fecha y hora. Guarda el resultado en output608.txt.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

// Un registro del log: "Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts"
struct Registro {
    string mes;        // "Sep"
    int dia;           // 29
    int anio;          // 2024
    int hora, minuto, segundo;
    string ip;
    string razon;
    long long llave;   // numero para comparar fechas facilmente
};

// Convierte el mes de texto a numero (Jan = 1, Feb = 2, ...)
int mesANumero(string mes) {
    string meses[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; i++) {
        if (meses[i] == mes) {
            return i + 1;
        }
    }
    return 0;
}

// Arma un numero con la forma AAAAMMDDHHMMSS para poder comparar con < y >
long long calcularLlave(Registro &r) {
    long long llave = r.anio;
    llave = llave * 100 + mesANumero(r.mes);
    llave = llave * 100 + r.dia;
    llave = llave * 100 + r.hora;
    llave = llave * 100 + r.minuto;
    llave = llave * 100 + r.segundo;
    return llave;
}

// Regresa la linea con el mismo formato del archivo original
string aTexto(Registro &r) {
    stringstream ss;
    ss << r.mes << " ";
    if (r.dia < 10) ss << "0";
    ss << r.dia << " " << r.anio << " ";
    if (r.hora < 10) ss << "0";
    ss << r.hora << ":";
    if (r.minuto < 10) ss << "0";
    ss << r.minuto << ":";
    if (r.segundo < 10) ss << "0";
    ss << r.segundo << " " << r.ip << " " << r.razon;
    return ss.str();
}

// Lee el archivo y llena el vector de registros
bool leerArchivo(string nombreArchivo, vector<Registro> &datos) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        return false;
    }

    datos.clear();
    string linea;
    while (getline(archivo, linea)) {
        if (linea.size() < 10) {   // ignora lineas vacias
            continue;
        }

        Registro r;
        stringstream ss(linea);
        string horaCompleta;

        // "Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts"
        ss >> r.mes >> r.dia >> r.anio >> horaCompleta >> r.ip;

        // la hora viene como "14:37:38", cambiamos los ':' por espacios
        for (int i = 0; i < (int)horaCompleta.size(); i++) {
            if (horaCompleta[i] == ':') {
                horaCompleta[i] = ' ';
            }
        }
        stringstream sh(horaCompleta);
        sh >> r.hora >> r.minuto >> r.segundo;

        // lo que sobra de la linea es la razon (puede traer varias palabras)
        getline(ss, r.razon);
        if (r.razon.size() > 0 && r.razon[0] == ' ') {
            r.razon = r.razon.substr(1);
        }

        r.llave = calcularLlave(r);
        datos.push_back(r);
    }

    archivo.close();
    return true;
}

// Ordenamiento por insercion usando la llave cronologica
void insertionSort(vector<Registro> &datos) {
    int n = datos.size();
    for (int i = 1; i < n; i++) {
        Registro actual = datos[i];
        int j = i - 1;
        while (j >= 0 && datos[j].llave > actual.llave) {
            datos[j + 1] = datos[j];
            j--;
        }
        datos[j + 1] = actual;
    }
}

// Imprime los primeros n registros del vector
void mostrar(vector<Registro> &datos, int n) {
    if (n > (int)datos.size()) {
        n = datos.size();
    }
    for (int i = 0; i < n; i++) {
        cout << "   " << aTexto(datos[i]) << endl;
    }
}

// Guarda todos los registros en un archivo con el formato original
void guardarArchivo(string nombreArchivo, vector<Registro> &datos) {
    ofstream archivo(nombreArchivo.c_str());
    for (int i = 0; i < (int)datos.size(); i++) {
        archivo << aTexto(datos[i]) << endl;
    }
    archivo.close();
}

int main() {
    vector<Registro> datos;
    int opcion = -1;

    while (opcion != 0) {
        cout << endl;
        cout << "===== EVIDENCIA 1 - PARTE 1: ENTRADA =====" << endl;
        cout << "Elige el archivo a procesar:" << endl;
        cout << "  1) data/log607-1.txt  (desordenado)" << endl;
        cout << "  2) data/log607-2.txt  (casi ordenado)" << endl;
        cout << "  0) Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        string nombreArchivo;
        if (opcion == 1) {
            nombreArchivo = "data/log607-1.txt";
        } else if (opcion == 2) {
            nombreArchivo = "data/log607-2.txt";
        } else if (opcion == 0) {
            cout << "Adios." << endl;
            continue;
        } else {
            cout << "Opcion invalida." << endl;
            continue;
        }

        if (!leerArchivo(nombreArchivo, datos)) {
            cout << "ERROR: no se pudo abrir " << nombreArchivo << endl;
            continue;
        }

        cout << endl << "Archivo leido: " << nombreArchivo << endl;
        cout << "Registros almacenados: " << datos.size() << endl;
        cout << endl << "Primeros 5 registros ANTES de ordenar:" << endl;
        mostrar(datos, 5);

        // se mide cuanto tarda el ordenamiento
        auto inicio = chrono::high_resolution_clock::now();
        insertionSort(datos);
        auto fin = chrono::high_resolution_clock::now();
        double tiempo = chrono::duration<double>(fin - inicio).count();

        cout << endl << "Primeros 5 registros DESPUES de ordenar:" << endl;
        mostrar(datos, 5);
        cout << endl << "Algoritmo: insertionSort" << endl;
        cout << "Tiempo de ordenamiento: " << tiempo << " segundos" << endl;

        guardarArchivo("output608.txt", datos);
        cout << "Resultado guardado en output608.txt" << endl;
    }

    return 0;
}
