//Довести, що для будь-якого трикутника ABC виконується нерівність: cosA + cosB + cosC <=3/2.
#include <iostream>
#include <cmath>
#define M_PI           3.14159265358979323846
#define RATIO 1.5
#define CHECK_IF_TRIANGLE(a, b, c) { \
    if ((a + b > c) && (b + c > a) && (a + c > b)) { \
        std::cout << "Passed as a Triangle" << std::endl; \
    } else { \
        std::cout << "Not passed as a Triangle" << std::endl; \
        return 1; \
} \
}

#define CHECK_THEOREM(a, b, c) { \
    double result = cos(a) + cos(b) + cos(c); \
    CHECK_IF_TRIANGLE(a, b, c) \
    if (result <= RATIO) { \
        std::cout << "The theorem is true! (result=" << result << ")" << std::endl; \
    } else { \
        std::cout << "The theorem is false! (result=" << result << ")" << std::endl; \
    } \
}

int main() {
    double a, b, c;
    std::cout << "Please input values for a, b, c" << std::endl;
    std::cin >> a >> b >> c;
    
    CHECK_THEOREM(a, b, c);

};

