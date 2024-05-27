#include <iostream>
using namespace std;

void printBinary(int n) {
    if (n == 0) {
        return;
    }
    else {
        printBinary(n / 2);
        cout << n % 2;
    }
}

int main() {
    int n;
    cout << "Enter a decimal number: ";
    cin >> n;

    cout << "The binary representation of " << n << " is: ";
    printBinary(n);
    cout << endl;

    return 0;
}