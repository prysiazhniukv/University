#include <iostream>
#include <string>

std::string getNextWord(std::string& str) {
    size_t pos = str.find(' ');
    if (pos == std::string::npos) {
        std::string word = str;
        str.clear();
        return word;
    }
    std::string word = str.substr(0, pos);
    str.erase(0, pos + 1);
    return word;
}

std::string cipher(const std::string& base, std::string userSentence) {
    std::string output;
    std::string baseCopy = base;
    std::string word;

    while (!userSentence.empty()) {
        for (int i = 0; i < 2; i++) {
            if (baseCopy.empty()) {
                baseCopy = base;
            }
            word = getNextWord(baseCopy);
            output += word + " ";
        }
        if (!userSentence.empty()) {
            word = getNextWord(userSentence);
            output += word + " ";
        }
    }

    return output;
}

int main() {
    std::string user_sentence;
    std::string BASE = "THE LONDON IS THE CAPITAL OF THE GREAT BRITAIN";
    std::string OUTPUT;

    std::cout << "Enter the sentence: ";
    std::getline(std::cin, user_sentence);

    std::cout << "BASE: " << BASE << std::endl;
    std::cout << "User Sentence: " << user_sentence << std::endl;

    OUTPUT = cipher(BASE, user_sentence);
    std::cout << "Output: " << OUTPUT << std::endl;

    return 0;
}
