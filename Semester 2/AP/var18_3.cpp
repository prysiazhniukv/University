//Владислав Присяжнюк, КІ-32, Середовище VS Code + g++ Compiler
#include <iostream>

double power_recursive(double x, int n) {
    if (n == 0) return 1;

    // Негативні n перетворюємо в позитивні
    if (n < 0) return 1 / power_recursive(x, -n);

    // рекурсивно множимо X на степінь n-1
    double half_power = power_recursive(x, n / 2);

    // якщо n кратне
    if (n % 2 == 0) {
        return half_power * half_power;
    } else { // якщо n не кратне
        return x * half_power * half_power;
    }
}

double power_iterative(double x, int n) {
    if (n == 0) return 1;

    // Для від'ємних степенів конвертувати їх у додатні і інвертувати результат в кінці
    bool is_negative = n < 0;
    n = abs(n);

    double result = 1;
    while (n > 0) {
        if (n % 2 == 1) {
            result *= x;
            n--; 
        }
        x *= x; 
        n /= 2; 
    }

    // Якщо оригінальна ступінь було негативною, інвертуємо
    return is_negative ? 1 / result : result;
}

int main() {
    double x;
    int n;
    std::cout << "Оберіть (X): ";
    std::cin >> x;
    std::cout << "Оберіть ступінь (n): ";
    std::cin >> n;

    std::cout << "Рекурсивний метод: " << x << "^" << n << " = " << power_recursive(x, n) << std::endl;
    std::cout << "Ітеративний метод: " << x << "^" << n << " = " << power_iterative(x, n) << std::endl;

    return 0;
}

