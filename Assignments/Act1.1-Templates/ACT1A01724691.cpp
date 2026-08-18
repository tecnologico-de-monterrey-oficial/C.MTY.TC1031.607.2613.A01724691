#include <iostream>
#include <string>
#include "List.h"
using namespace std;

/*
int sum(int a, int b) {
    return a+b;
}

double sum(double a, double b) {
    return a+b;
}

string sum(string a, string b) {
    return a +b;
}
*/
template <typename T>

T sum(T a, T b) {
    return a + b;
}

int main() {
    string a = "hola";
    string b = " crayola";
    cout<<"Sum of "<<a<<" and "<<b<<" is: "<<sum(a,b)<<endl;
    int c = 5;
    int d = 10;
    cout<<"Sum of "<<c<<" and "<<d<<" is: "<<sum(c,d)<<endl;
    double e = 5.5;
    double f = 10.5;
    cout<<"Sum of "<<e<<" and "<<f<<" is: "<<sum(e,f)<<endl;

    List<int> listaInts;
    listaInts.insert(5);
    listaInts.insert(10);
    listaInts.insert(15);
    cout << "Lista de enteros:" << endl;
    listaInts.print();

    List<string> listaStrings;
    listaStrings.insert("Laptop");
    listaStrings.insert("bottle");
    cout << "Lista de strings:" << endl;
    listaStrings.print();

    return 0;
}
