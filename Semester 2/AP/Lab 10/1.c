#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_distinct_letters(const char *word) {
    int count[256] = {0};
    int distinct = 0;
    while (*word) {
        if (isalpha(*word) && count[(unsigned char)*word] == 0) {
            count[(unsigned char)*word]++;
            distinct++;
        }
        word++;
    }
    return distinct;
}

void remove_words(char *str) {
    char result[1000] = "";
    char *word = strtok(str, " ");
    while (word != NULL) {
        if (count_distinct_letters(word) > 2) {
            strcat(result, word);
            strcat(result, " ");
        }
        word = strtok(NULL, " ");
    }
    strcpy(str, result);
}

int main() {
    int n;

    printf("Please type the amount of strings you want:\n");
    scanf("%d", &n);
    getchar(); //
    char strings[n][100];

    printf("Type the strings:\n");
    for (int i = 0; i < n; i++) {
        fgets(strings[i], 100, stdin);
        strings[i][strcspn(strings[i], "\n")] = '\0';
    }

    printf("The strings after removing words that have no more than 2 different letters:\n");
    for (int i = 0; i < n; i++) {
        remove_words(strings[i]);
        printf("%s\n", strings[i]);
    }

    return 0;
}
