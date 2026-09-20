#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "Registro.h"
#include "Ordenamientos.h"
#include "Busqueda.h"
using namespace std;

void corridaOrdenamiento(vector<Registro> &datos, bool &ordenado) {
    cout << endl << "Elige el archivo a procesar:" << endl;
    cout << "  1) data/log607-1.txt  (desordenado)" << endl;
    cout << "  2) data/log607-2.txt  (casi ordenado)" << endl;
    cout << "Opcion: ";

    int opcionArchivo;
    cin >> opcionArchivo;

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
        return;
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
        return;
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
        cout << "Ejecuta el programa desde la carpeta Evidence1." << endl;
        return;
    }

    cout << endl << "Ordenando " << datos.size() << " registros..." << endl;

    auto inicio = chrono::high_resolution_clock::now();
    ordenar(datos, opcionAlgoritmo);
    auto fin = chrono::high_resolution_clock::now();
    double tiempo = chrono::duration<double>(fin - inicio).count();

    ordenado = true;

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

    string reporte = "";
    reporte += "-------------------------------------------\n";
    reporte += "Algoritmo:        " + nombreAlgoritmo(opcionAlgoritmo) + "\n";
    reporte += "Archivo:          " + nombreArchivo + " (" + tipoArchivo + ")\n";
    reporte += "Tamano de datos:  " + to_string(datos.size()) + " registros\n";
    reporte += "Tiempo:           " + to_string(tiempo) + " segundos\n";
    reporte += "Mejor caso:       " + mejorCaso(opcionAlgoritmo) + "\n";
    reporte += "Peor caso:        " + peorCaso(opcionAlgoritmo) + "\n";
    reporte += "Prediccion:       " + textoPrediccion + " - " + razonPrediccion + "\n";
    reporte += "Resultado real:   " + resultadoReal + "\n";
    reporte += "Comparacion:      " + coincidio + "\n";
    reporte += "-------------------------------------------\n";

    cout << endl << reporte;

    cout << endl << "Primeros 5 registros ordenados:" << endl;
    mostrar(datos, 5);

    guardarArchivo("out/output608.txt", datos);
    cout << endl << "Datos ordenados guardados en out/output608.txt" << endl;

    ofstream bitacora("out/resultados608.txt", ios::app);
    bitacora << reporte;
    bitacora.close();
    cout << "Reporte agregado a out/resultados608.txt" << endl;
}

void corridaBusqueda(vector<Registro> &datos, bool ordenado) {
    if (!ordenado) {
        cout << endl << "Primero ordena un archivo con la opcion 1." << endl;
        return;
    }

    cout << endl << "Formato: Mes Dia Anio HH:MM:SS   (ejemplo: Sep 08 2024 00:00:00)" << endl;
    cout << "Los limites no tienen que existir en el archivo." << endl;

    cout << endl << "Fecha y hora de inicio: ";
    string textoInicio;
    getline(cin, textoInicio);

    cout << "Fecha y hora de fin:    ";
    string textoFin;
    getline(cin, textoFin);

    long long llaveInicio = llaveDesdeTexto(textoInicio);
    long long llaveFin = llaveDesdeTexto(textoFin);

    if (llaveInicio == -1 || llaveFin == -1) {
        cout << endl << "ERROR: formato de fecha invalido." << endl;
        return;
    }

    if (llaveInicio > llaveFin) {
        cout << endl << "ERROR: la fecha de inicio es mayor que la de fin." << endl;
        return;
    }

    int desde = buscarInicio(datos, llaveInicio);
    int hasta = buscarFin(datos, llaveFin);
    int total = hasta - desde + 1;

    cout << endl << "-------------------------------------------" << endl;
    cout << "Rango:            [" << llaveInicio << ", " << llaveFin << "]" << endl;
    cout << "Tipo de rango:    cerrado, incluye ambos limites" << endl;
    cout << "Posicion inicio:  " << desde << endl;
    cout << "Posicion fin:     " << hasta << endl;
    cout << "Registros:        " << total << endl;
    cout << "-------------------------------------------" << endl;

    if (total <= 0) {
        cout << endl << "No hay registros en ese rango." << endl;
        ofstream vacio("out/range607.txt");
        vacio.close();
        cout << "Se genero out/range607.txt vacio." << endl;
        return;
    }

    vector<Registro> rango;
    for (int i = desde; i <= hasta; i++) {
        rango.push_back(datos[i]);
    }

    cout << endl << "Resultado:" << endl;
    if (total <= 20) {
        mostrar(rango, total);
    } else {
        mostrar(rango, 10);
        cout << "   ... (" << total - 20 << " registros intermedios) ..." << endl;
        for (int i = total - 10; i < total; i++) {
            cout << "   " << aTexto(rango[i]) << endl;
        }
    }

    guardarArchivo("out/range607.txt", rango);
    cout << endl << "Resultado guardado en out/range607.txt" << endl;
}

int main() {
    vector<Registro> datos;
    bool ordenado = false;

    while (true) {
        cout << endl;
        cout << "===== EVIDENCIA 1 - ANALIZADOR DE LOGS =====" << endl;
        cout << "  1) Ordenar un archivo" << endl;
        cout << "  2) Buscar por rango de fechas" << endl;
        cout << "  0) Salir" << endl;
        cout << "Opcion: ";

        string opcion;
        if (!getline(cin, opcion)) {
            break;
        }

        if (opcion == "0") {
            cout << "Adios." << endl;
            break;
        } else if (opcion == "1") {
            corridaOrdenamiento(datos, ordenado);
        } else if (opcion == "2") {
            corridaBusqueda(datos, ordenado);
        } else {
            cout << "Opcion invalida." << endl;
        }
    }

    return 0;
}
