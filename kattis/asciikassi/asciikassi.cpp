#include <string.h>

#include <iostream>
using namespace std;

void printFirstLast(uint32_t n) {
    cout << "+";
    for (int i = 0; i < n; i++) {
        cout << "-";
    }
    cout << "+" << endl;
}

void printMiddleLine(uint32_t n) {
    cout << "|";
    for (int i = 0; i < n; i++) {
        cout << " ";
    }
    cout << "|" << endl;
}
int main(void) {
    uint32_t n = 0;
    cin >> n;
    printFirstLast(n);
    for (int i = 0; i < n; i++) {
        printMiddleLine(n);
    }
    printFirstLast(n);
    return 0;
}