#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

struct Registro {
    string mes;
    int dia;
    int anio;
    int hora, minuto, segundo;
    string ip;
    string razon;
    long long llave;
};

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

long long calcularLlave(Registro &r) {
    long long llave = r.anio;
    llave = llave * 100 + mesANumero(r.mes);
    llave = llave * 100 + r.dia;
    llave = llave * 100 + r.hora;
    llave = llave * 100 + r.minuto;
    llave = llave * 100 + r.segundo;
    return llave;
}

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

bool leerArchivo(string nombreArchivo, vector<Registro> &datos) {
    ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()) {
        return false;
    }

    datos.clear();
    string linea;
    while (getline(archivo, linea)) {
        if (linea.size() < 10) {
            continue;
        }

        Registro r;
        stringstream ss(linea);
        string horaCompleta;

        ss >> r.mes >> r.dia >> r.anio >> horaCompleta >> r.ip;

        for (int i = 0; i < (int)horaCompleta.size(); i++) {
            if (horaCompleta[i] == ':') {
                horaCompleta[i] = ' ';
            }
        }
        stringstream sh(horaCompleta);
        sh >> r.hora >> r.minuto >> r.segundo;

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

void mostrar(vector<Registro> &datos, int n) {
    if (n > (int)datos.size()) {
        n = datos.size();
    }
    for (int i = 0; i < n; i++) {
        cout << "   " << aTexto(datos[i]) << endl;
    }
}

void guardarArchivo(string nombreArchivo, vector<Registro> &datos) {
    ofstream archivo(nombreArchivo.c_str());
    for (int i = 0; i < (int)datos.size(); i++) {
        archivo << aTexto(datos[i]) << endl;
    }
    archivo.close();
}

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

int main() {
    vector<Registro> datos;

    while (true) {
        cout << endl;
        cout << "===== EVIDENCIA 1 - ORDENAMIENTO DE LOGS =====" << endl;
        cout << "Elige el archivo a procesar:" << endl;
        cout << "  1) data/log607-1.txt  (desordenado)" << endl;
        cout << "  2) data/log607-2.txt  (casi ordenado)" << endl;
        cout << "  0) Salir" << endl;
        cout << "Opcion: ";

        int opcionArchivo;
        cin >> opcionArchivo;

        if (opcionArchivo == 0) {
            cout << "Adios." << endl;
            break;
        }

        string nombreArchivo;
        string tipoArchivo;
        if (opcionArchivo == 1) {
            nombreArchivo = "data/log607-1.txt";
            tipoArchivo = "desordenado";
        } else if (opcionArchivo == 2) {
            nombreArchivo = "data/log607-2.txt";
            tipoArchivo = "casi ordenado";
        } else {
            cout << "Opcion invalida." << endl;
            continue;
        }

        cout << endl << "Elige el algoritmo de ordenamiento:" << endl;
        cout << "  1) swapSort" << endl;
        cout << "  2) selectionSort" << endl;
        cout << "  3) bubbleSort" << endl;
        cout << "  4) insertionSort" << endl;
        cout << "  5) mergeSort" << endl;
        cout << "  6) quickSort" << endl;
        cout << "  7) shellSort" << endl;
        cout << "Opcion: ";

        int opcionAlgoritmo;
        cin >> opcionAlgoritmo;

        if (opcionAlgoritmo < 1 || opcionAlgoritmo > 7) {
            cout << "Opcion invalida." << endl;
            continue;
        }

        cout << endl << "Prediccion: " << nombreAlgoritmo(opcionAlgoritmo)
             << " sobre el archivo " << tipoArchivo << " va a ser..." << endl;
        cout << "  1) Rapido (menos de 0.1 segundos)" << endl;
        cout << "  2) Lento  (0.1 segundos o mas)" << endl;
        cout << "Opcion: ";

        int prediccion;
        cin >> prediccion;
        cin.ignore();

        cout << "Por que? ";
        string razonPrediccion;
        getline(cin, razonPrediccion);

        if (!leerArchivo(nombreArchivo, datos)) {
            cout << "ERROR: no se pudo abrir " << nombreArchivo << endl;
            continue;
        }

        cout << endl << "Ordenando " << datos.size() << " registros..." << endl;

        auto inicio = chrono::high_resolution_clock::now();
        ordenar(datos, opcionAlgoritmo);
        auto fin = chrono::high_resolution_clock::now();
        double tiempo = chrono::duration<double>(fin - inicio).count();

        string resultadoReal;
        if (tiempo < 0.1) {
            resultadoReal = "Rapido";
        } else {
            resultadoReal = "Lento";
        }

        string textoPrediccion;
        if (prediccion == 1) {
            textoPrediccion = "Rapido";
        } else {
            textoPrediccion = "Lento";
        }

        string coincidio;
        if (textoPrediccion == resultadoReal) {
            coincidio = "SI coincidio con la prediccion";
        } else {
            coincidio = "NO coincidio con la prediccion";
        }

        stringstream reporte;
        reporte << "-------------------------------------------" << endl;
        reporte << "Algoritmo:        " << nombreAlgoritmo(opcionAlgoritmo) << endl;
        reporte << "Archivo:          " << nombreArchivo << " (" << tipoArchivo << ")" << endl;
        reporte << "Tamano de datos:  " << datos.size() << " registros" << endl;
        reporte << "Tiempo:           " << tiempo << " segundos" << endl;
        reporte << "Mejor caso:       " << mejorCaso(opcionAlgoritmo) << endl;
        reporte << "Peor caso:        " << peorCaso(opcionAlgoritmo) << endl;
        reporte << "Prediccion:       " << textoPrediccion << " - " << razonPrediccion << endl;
        reporte << "Resultado real:   " << resultadoReal << endl;
        reporte << "Comparacion:      " << coincidio << endl;
        reporte << "-------------------------------------------" << endl;

        cout << endl << reporte.str();

        cout << endl << "Primeros 5 registros ordenados:" << endl;
        mostrar(datos, 5);

        guardarArchivo("output608.txt", datos);
        cout << endl << "Datos ordenados guardados en output608.txt" << endl;

        ofstream bitacora("resultados608.txt", ios::app);
        bitacora << reporte.str();
        bitacora.close();
        cout << "Reporte agregado a resultados608.txt" << endl;
    }

    return 0;
}
