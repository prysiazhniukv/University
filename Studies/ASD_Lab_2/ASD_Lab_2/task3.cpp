#include <iostream>
using namespace std;

int compareHalves(int d) {

    int d_copy = d;
    int first = 0;
    int second = 0;

    for (int i = 0; i < 17; i++ ) {

        if (d_copy & 1) {
            first++;
        }
        d_copy >>= 1;
    }

    d_copy = d;
    d_copy >>= 16;

    for (int i = 0; i < 16; i++) {

        if (d_copy & 1) {
            second++;
        }
        d_copy >>= 1;
    }

    if (first > second) {
        cout << "1";
    } else if (second > first) {
        cout << "2";
    } else {
        cout << "0";
    }

    return 0;
}

int main() {
    int d;
    cin >> d;
    compareHalves(d);
    return 0;
}