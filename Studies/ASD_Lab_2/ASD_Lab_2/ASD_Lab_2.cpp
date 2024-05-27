#include <iostream>
#include <time.h>
using namespace std;

int is_prime(int n) {  // #Task 1.0
    if (n <= 1) {
        return 0;
    }

    for (int i = 2; i < (n / 2); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void sieveOfEratosthenes(int n) {  // #Task 1.0
    int isPrime[n + 1];
    for (int i = 0; i <= n; i++) {
        isPrime[i] = 1;
    }

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p] == 1) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = 0;
            }
        }
    }

    for (int p = 2; p <= n; p++) {
        if (isPrime[p]) {
            printf("%d ", p);
        }
    }
    printf("\n");
}

string printBinary(int d) {  // Task 2.0
    if (d == 0) {
        std::cout << "0"; // If input is 0
        return "0";
    }

    int binary[32]; // Because that's a maximum size of binary for int
    int index = 0;

    while (d > 0) {
        binary[index++] = d % 2;  // module by 2 represents this numbers binary so 19%2 = 1 and so on.
        d /= 2; // 19/=2=9, so 9 is a left over. and program repeats until it's 0
    }

    string binaryStr;
    for (int i = index - 1; i >= 0; i--) {
        binaryStr += std::to_string(binary[i]);
    }
    cout << binaryStr << endl;
    return binaryStr;
}

int compareHalves(int x) {
    int count = 0;
    string result = printBinary(int (x));
    int length = result.length();
    int middle = length / 2;
    string firstHalf = result.substr(0, middle);
    string secondHalf = result.substr(middle);
    int onesInFirstHalf = 0;
    int onesInSecondHalf = 0;
    for (char bit : firstHalf) {
        if (bit == '1') {
            onesInFirstHalf++;
        }
    }
    for (char bit : secondHalf) {
        if (bit == '1') {
            onesInSecondHalf++;
        }
    }

    if (onesInFirstHalf > onesInSecondHalf) {
        cout << "1";
    } else if (onesInSecondHalf > onesInFirstHalf) {
        cout << "2";
    } else {
        cout << "0";
    }
    return 0;
}

int countVisible17(int N) {
    if (N < 10) {
        return 0;
    }
    int lastTwoDigits = N % 100;

    if (lastTwoDigits == 17) {
        return 1 + countVisible17(N / 10);
    } else {
        return countVisible17(N / 10);
    }
}




int main()
{
    int a[100];
    int n = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for (int i = 0; i < n; i++)
    {
        if (is_prime(a[i]))
        {
            printf("%d is prime.\n", a[i]);
        }
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);

    start = clock();
    printf("Prime numbers in the range 2 to %d are:\n", n);
    sieveOfEratosthenes(n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);

    int d;
    std::cout << "Please type an integer that with 2 points; Examples: 10, 69 , 23, 88 " << std::endl;
    std::cin >> d;
    printBinary(d);


    int x;
    cout << "Enter a number for Task 3";
    cin >> x;

    int result = compareHalves(x);

    int N;
    std::cout << "Please type a natural number N: ";
    std::cin >> N;

    int count = countVisible17(N);
    std::cout << "Amount of times 17 fits into N " << N << " equals to " << count << std::endl;

    return 0;
}
