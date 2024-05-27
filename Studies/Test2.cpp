#include <iostream>

int main() {
	int n, b;
	std::cout << "Type a number";
	std::cin >> n;



}

void printBinary() {
	while (n > 0) {
		b = n % 2;
		std::cout << b;
		n /= 2;
	}
}