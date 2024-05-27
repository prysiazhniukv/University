#include <iostream>

void printBinary(int d) {
    if (d == 0) {
        std::cout << "0";
        return;
    }

    int binary[32];
    int index = 0;

    while (d > 0) {
        binary[index++] = d % 2;
        d /= 2;
    }

    for (int i = index - 1; i >= 0; i--) {
        std::cout << binary[i];
    }
}


int main()
{
    int d;
    std::cout << "Please type an integer that with 2 points; Examples: 10, 69 , 23, 88 " << std::endl;
    std::cin >> d;
    std::cout << d;
    printBinary(d);
    return 0;

}
