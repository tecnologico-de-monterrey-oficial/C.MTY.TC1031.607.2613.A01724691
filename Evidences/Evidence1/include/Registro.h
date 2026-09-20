#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
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

long long llaveDesdeTexto(string texto) {
    Registro r;
    string horaCompleta;
    stringstream ss(texto);

    ss >> r.mes >> r.dia >> r.anio >> horaCompleta;
    if (ss.fail()) {
        return -1;
    }
    if (mesANumero(r.mes) == 0) {
        return -1;
    }
    if (r.dia < 1 || r.dia > 31) {
        return -1;
    }

    for (int i = 0; i < (int)horaCompleta.size(); i++) {
        if (horaCompleta[i] == ':') {
            horaCompleta[i] = ' ';
        }
    }
    stringstream sh(horaCompleta);
    sh >> r.hora >> r.minuto >> r.segundo;
    if (sh.fail()) {
        return -1;
    }

    return calcularLlave(r);
}

#endif
