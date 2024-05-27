//Владислав Присяжнюк, КІ-32, Середовище VS Code + g++ Compiler
//Масив слів відсортувати за алфавітом (слова вводяться з клавіатури).
#include <iostream>
#include <vector>
#include <string>

void bubbleSort(std::vector<std::string>& words) { // Простенький алгоритм сортування bubblesort
    bool swapped; // Якщо елементи більше не сортируються в середині циклу то програма закінчюється.
    do {
        swapped = false;
        for (size_t i = 0; i < words.size() - 1; i++) {
            if (words[i] > words[i + 1]) {
                std::swap(words[i], words[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

int main() {
    std::vector<std::string> words; //Масив слів
    std::string word;
    std::cout << "Введіть слова (для завершення введіть 'end'): ";
    
    while (std::cin >> word) {
        if (word == "end") { // Для закінчення набору слів слід написати слово 'end'
            break;
        }
        words.push_back(word);
    }

    bubbleSort(words);

    std::cout << "Слова в алфавітному порядку:" << std::endl;
    for (const auto& w : words) { // Вивод відстортированих слів.
        std::cout << w << std::endl;
    }

    return 0;
}
