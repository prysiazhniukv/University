#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void countSort(std::vector<T>& arr, unsigned long long& setOps) {
    if (arr.empty()) return; // Перевірка на пустий масив

    T min_val = *std::min_element(arr.begin(), arr.end()); // Пошук мінімального та максимального значення
    T max_val = *std::max_element(arr.begin(), arr.end());
    setOps += 2 * (arr.size() - 1);

    int range = max_val - min_val + 1; // Визначення діапазону

    std::vector<int> count(range, 0); // Створення масиву для підрахунку кількості кожного елементу
    std::vector<T> output(arr.size()); // Створення вихідного масиву

    for (T num : arr) {
        count[num - min_val]++; // num - min_val - індекс елементу в масиві count
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1]; // count[i] - кількість елементів, які менші або рівні i
    }

    for (int i = arr.size() - 1; i >= 0; i--) { // Заповнення вихідного масиву
        output[count[arr[i] - min_val] - 1] = arr[i]; // count[arr[i] - min_val] - позиція елементу в вихідному масиві
        setOps++;
        count[arr[i] - min_val]--; // Зменшення кількості елементів, які менші або рівні arr[i]
    }

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != output[i]) { // Перевірка на зміну елементів
            arr[i] = output[i]; // Заміна елементів
            setOps++;
        }
    }
}
