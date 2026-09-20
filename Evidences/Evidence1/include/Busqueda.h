#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <vector>
#include "Registro.h"
using namespace std;

int buscarInicio(vector<Registro> &v, long long llave) {
    int bajo = 0;
    int alto = v.size() - 1;
    int resultado = v.size();

    while (bajo <= alto) {
        int medio = (bajo + alto) / 2;

        if (v[medio].llave >= llave) {
            resultado = medio;
            alto = medio - 1;
        } else {
            bajo = medio + 1;
        }
    }

    return resultado;
}

int buscarFin(vector<Registro> &v, long long llave) {
    int bajo = 0;
    int alto = v.size() - 1;
    int resultado = -1;

    while (bajo <= alto) {
        int medio = (bajo + alto) / 2;

        if (v[medio].llave <= llave) {
            resultado = medio;
            bajo = medio + 1;
        } else {
            alto = medio - 1;
        }
    }

    return resultado;
}

#endif
