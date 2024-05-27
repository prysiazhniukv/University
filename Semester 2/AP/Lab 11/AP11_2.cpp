#include <stdio.h>
#include <conio.h>
#include <string.h>

char* findPhoneNumber(const char* filename, const char* search_surname, const char* search_initials) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Не вдалося відкрити файл.\n");
        return NULL;
    }

    static char phone[15]; 
    char surname[50], initials[5];
    while (fscanf(file, "%s %s %s", surname, initials, phone) != EOF) {
        if (strcmp(surname, search_surname) == 0 && strcmp(initials, search_initials) == 0) {
            fclose(file);
            return phone;
        }
    }

    fclose(file);
    return NULL; 
}

int main() {
    char search_surname[50], search_initials[5];

    printf("Введіть прізвище студента: ");
    scanf("%49s", search_surname); 
    printf("Введіть ініціали студента: ");
    scanf("%4s", search_initials);

    char* phone = findPhoneNumber("PhoneNumbers", search_surname, search_initials);
    if (phone != NULL) {
        printf("Номер телефону: %s\n", phone);
    } else {
        printf("Студент не знайдений.\n");
    }

    _getch();
    return 0;
}
