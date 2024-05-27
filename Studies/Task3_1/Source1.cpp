#include <iostream>

using namespace std;

int compareHalves(int d) {

    int num_bits = int(n.bit_length());

    int left_half = n >> (num_bits // 2);
        int right_half = n & ((1 << (num_bits // 2)) - 1);

            int left_count = bin(left_half).count('1');
    int right_count = bin(right_half).count('1');

    if (left_count > right_count) {
        return 1;
    } elif(left_count < right_count) {
        return -1;
    }
    else {
        return 0;
    }
}

int main() {
    int d;
    cout << "Enter a number: ";
    cin >> d;

    int result = checkHalves(d);

    if (result == 1) {
        cout << "1" << endl;
    } elif(result == -1) {
        cout << "2" << endl;
    }
    else {
        cout << "0" << endl;
    }

    return 0;
}
