#include <iostream>
#include <string>
using namespace std;

char sequentialSearch(string &s, int &comparaciones) {
    int n = s.size();
    comparaciones = 0;
    for (int i = 0; i + 1 < n; i += 2) {
        comparaciones++;
        if (s[i] != s[i + 1]) {
            return s[i];
        }
    }
    return s[n - 1];
}

char binarySearch(string &s, int &comparaciones) {
    int n = s.size();
    int low = 0;
    int high = n / 2 - 1;
    int pos = n - 1;
    comparaciones = 0;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (s[2 * mid] == s[2 * mid + 1]) {
            comparaciones++;
            low = mid + 1;
        } else {
            pos = 2 * mid;
            high = mid - 1;
        }
    }
    return s[pos];
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int compSec, compBin;
        char letraSec = sequentialSearch(s, compSec);
        char letraBin = binarySearch(s, compBin);
        cout << letraSec << " " << compSec << " " << letraBin << " " << compBin << endl;
    }
    return 0;
}
