#include <iostream>

using namespace std;

int compare_halves(int n) {
int count1 = 0;
int count2 = 0;
int half = sizeof(n) * 8 / 2;

for (int i = 0; i < half; i++) {
    if (n & (1 << i)) {
        count1++;
        
    }
}

for (int i = half; i < sizeof(n) * 8; i++) {
    if (n & (1 << i)) {
        count2++;
       
    }
}

if (count1 > count2) {
    cout << "1";
    return 1;
}
else if (count2 > count1) {
    cout << "2";
    return 2;
}
else {
    cout << "0";
    return 0;
}
}

int main() {
    // Get input from user.
    int n;
    cout << "Enter a number: ";
    cin >> n;

    // Compare the two halves.
    int result = compare_halves(n);

    return 0;
}
