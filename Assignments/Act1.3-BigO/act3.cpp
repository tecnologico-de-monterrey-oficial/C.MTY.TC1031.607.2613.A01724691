#include <iostream>
#include <vector>
using namespace std;

int sumOddIterative(vector<int> &v) {
    int sum = 0;
    int n = v.size();
    for (int i = 0; i < n; i++) {
        if (v[i] % 2 != 0) {
            sum += v[i];
        }
    }
    return sum;
}

int sumOddRecursive(vector<int> &v, int i) {
    int n = v.size();
    if (i == n) {
        return 0;
    }
    if (v[i] % 2 != 0) {
        return v[i] + sumOddRecursive(v, i + 1);
    }
    return sumOddRecursive(v, i + 1);
}

int main() {
    vector<int> numeros = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    cout << "Suma de impares iterativa: " << sumOddIterative(numeros) << endl;
    cout << "Suma de impares recursiva: " << sumOddRecursive(numeros, 0) << endl;

    return 0;
}
