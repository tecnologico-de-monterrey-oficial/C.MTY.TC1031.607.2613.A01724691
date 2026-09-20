#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include "Registro.h"
#include "Ordenamientos.h"
using namespace std;

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
            cout << "Ejecuta el programa desde la carpeta Evidence1." << endl;
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

        guardarArchivo("out/output608.txt", datos);
        cout << endl << "Datos ordenados guardados en out/output608.txt" << endl;

        ofstream bitacora("out/resultados608.txt", ios::app);
        bitacora << reporte.str();
        bitacora.close();
        cout << "Reporte agregado a out/resultados608.txt" << endl;
    }

    return 0;
}
