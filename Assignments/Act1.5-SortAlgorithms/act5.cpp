#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void print(vector<int> &v) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    vector<int> numeros;
    for (int i = 0; i < 12; i++) {
        numeros.push_back(rand() % 100);
    }

    cout << "Vector: ";
    print(numeros);

    return 0;
}
