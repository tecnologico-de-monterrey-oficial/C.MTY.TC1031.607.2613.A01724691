#include <iostream>
using namespace std;

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int sumIterative(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

int sumRecursive(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sumRecursive(n - 1);
}

int sumFormula(int n) {
    return (n * (n + 1)) / 2;
}

int fibonacciIterative(int n) {
    if (n <= 2) {
        return 1;
    }
    int prev = 1;
    int curr = 1;
    for (int i = 3; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int fibonacciRecursive(int n) {
    if (n <= 2) {
        return 1;
    }
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int bacteriasIterative(int n) {
    double born = 3.78;
    double died = 2.34;
    int sum = 1;
    for (int i = 1; i <= n; i++) {
        int bacBorn = sum * born;
        int bacDied = sum * died;
        sum += bacBorn - bacDied;
    }
    return sum;
}

int bacteriasRecursive(int n) {
    double born = 3.78;
    double died = 2.34;
    if (n == 0) {
        return 1;
    }
    int sum = bacteriasRecursive(n - 1);
    int bacBorn = sum * born;
    int bacDied = sum * died;
    return sum + bacBorn - bacDied;
}

double investmentIterative(int months, double amount) {
    double rate = 0.1875;
    for (int i = 1; i <= months; i++) {
        amount += amount * rate;
    }
    return amount;
}

double investmentRecursive(int months, double amount) {
    double rate = 0.1875;
    if (months == 0) {
        return amount;
    }
    double total = investmentRecursive(months - 1, amount);
    return total + total * rate;
}

double powIterative(double n, int y) {
    double result = 1;
    for (int i = 1; i <= y; i++) {
        result *= n;
    }
    return result;
}

double powRecursive(double n, int y) {
    if (y == 0) {
        return 1;
    }
    return n * powRecursive(n, y - 1);
}

int main() {
    cout << "El factorial de 5 es: " << factorial(5) << endl;

    cout << "La suma iterativa de 5 es: " << sumIterative(5) << endl;
    cout << "La suma recursiva de 5 es: " << sumRecursive(5) << endl;
    cout << "La suma con formula de 5 es: " << sumFormula(5) << endl;

    cout << "La fibonacci iterativa de 8 es: " << fibonacciIterative(8) << endl;
    cout << "La fibonacci recursiva de 8 es: " << fibonacciRecursive(8) << endl;

    cout << "La bacteria iterativa de 5 es: " << bacteriasIterative(5) << endl;
    cout << "La bacteria recursiva de 5 es: " << bacteriasRecursive(5) << endl;

    cout << "La inversion iterativa de 1000 en 12 meses es: " << investmentIterative(12, 1000) << endl;
    cout << "La inversion recursiva de 1000 en 12 meses es: " << investmentRecursive(12, 1000) << endl;

    cout << "La potencia iterativa de 2^10 es: " << powIterative(2, 10) << endl;
    cout << "La potencia recursiva de 2^10 es: " << powRecursive(2, 10) << endl;

    return 0;
}
