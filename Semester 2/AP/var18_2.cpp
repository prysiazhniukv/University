//Владислав Присяжнюк, КІ-32, Середовище VS Code + g++ Compiler
// Дано рядок, в якому слова розділені одним пропуском.Треба підрахувати, скільки в кожному слові букв, які збігаються з його першою буквою.
#include <iostream>
#include <string>

// Функція для підрахунку кількості букв у слові, що збігаються з першою буквою.
int countLetter(const std::string& word) {
    if (word.empty()) return 0;

    char firstLetter = word[0]; // Перша літера слова.
    int count = 0;

    // Рахуємо скільки разів перша літера зустрічається в слові.
    for (char c : word) {
        if (c == firstLetter || 
            (c >= 'A' && c <= 'Z' && firstLetter >= 'a' && firstLetter <= 'z' && c == firstLetter - 32) || 
            (c >= 'a' && c <= 'z' && firstLetter >= 'A' && firstLetter <= 'Z' && c == firstLetter + 32)) {
            count++;
        }
    }

    return count;
}

int main() {
    std::string input;
    std::cout << "Введіть рядок: ";
    getline(std::cin, input);
    input += " "; // Додаємо пробел в кінець щоб останне слово зарахувалось.

    std::string word = "";

    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] != ' ') {
            word += input[i]; // Будуємо слово.
        } else if (!word.empty()) {
            // Коли слово закінчено, рахуємо збіги і виводимо результат.
            int matches = countLetter(word);
            std::cout << "Слово: '" << word << "', Кількість збігів: " << (matches - 1) << std::endl;
            word = ""; // Скидаємо слово для наступного слова.
        }
    }

    return 0;
}
