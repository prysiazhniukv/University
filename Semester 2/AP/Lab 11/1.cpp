#include <stdio.h>
#include <string.h>

FILE *fin, *fout;
char name[2][20];

void Out(FILE* f);

void ChooseName() {
    printf("Enter name of file for write: ");
    fgets(name[0], sizeof(name[0]), stdin);
    name[0][strcspn(name[0], "\n")] = '\0';

    printf("Enter name of file for read: ");
    fgets(name[1], sizeof(name[1]), stdin);
    name[1][strcspn(name[1], "\n")] = '\0'; 
}

void CreateFile() {
    char answer;
    char s[100];
    fout = fopen(name[0], "w");
    if (fout == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    do {
        puts("Input string:"); 
        fgets(s, sizeof(s), stdin);
        fputs(s, fout);
        fputc('\n', fout);
        printf("Continue? [y/n]: ");
        answer = getchar();
    } while ((answer != 'n') && (answer != 'N'));
    fclose(fout);
}

void AddWord() {
    char sa[100], longestWord[100];
    fin = fopen(name[0], "r");
    fout = fopen(name[1], "w");
    if (fin == NULL || fout == NULL) {
        printf("Error opening files for reading/writing.\n");
        return;
    }

    while (fgets(sa, sizeof(sa), fin)) {
        int maxLen = 0;
        char *word = strtok(sa, " ,.-\n");

        while (word != NULL) {
            if ((int)strlen(word) > maxLen) {
                maxLen = strlen(word);
                strcpy(longestWord, word);
            }
            word = strtok(NULL, " ,.-\n");
        }

        if (maxLen > 0) {
            fprintf(fout, "%s %d\n", longestWord, maxLen);  
        }
    }

    fclose(fin);
    fclose(fout);
    fout = fopen(name[1], "r");
    Out(fout);
    fclose(fout);
}

void Out(FILE* f) {
    char s[100];
    while (fgets(s, 100, f)) {
        printf("%s", s);
    }
}

int main() {
    printf("Search longest word in strings from file\n");
    ChooseName();
    CreateFile();
    AddWord();
    return 0;
}
