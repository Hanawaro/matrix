#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

#define C_HELP "help"
#define C_OPREDELITEL "opredelitel"
#define C_POWER "power"
#define C_RANG "rang"
#define C_EXIT "shutdown"

void getCommand(char *string);
void helpShow(void);
void opredelitelStart(void);
void powerStart(void);
void rangStart(void);

int main(void) {
    int status = 1;
    char *command = (char *) malloc(sizeof(char));
    printf("Приветствую вас в matrix\n");
    do {
        printf("~/ ");
        getCommand(command);

        if (!strcmp(command, C_EXIT))
            status = 0;
        else if (!strcmp(command, C_HELP))
            helpShow();
        else if (!strcmp(command, C_OPREDELITEL))
            opredelitelStart();
        else if (!strcmp(command, C_POWER))
            powerStart();
        else if (!strcmp(command, C_RANG))
            rangStart();
        else
            printf("Неизвестная комманда\nВведите help, чтобы увидеть список команд\n");

    } while (status);
    
    return 0;
}

void getCommand(char *string) {
    int N = 0;
    while ( (string[N] = getchar()) != EOF && string[N] != '\n' && string[N] != '\0') {
        N++;
        string = (char *) realloc(string, sizeof(char) * N);
    }
    string[N] = '\0';
}

void helpShow(void) {
    printf("Список команд: \n");
    printf(" -- %s\n", C_OPREDELITEL);
    printf(" -- %s\n", C_POWER);
    printf(" -- %s\n", C_RANG);
}
void opredelitelStart(void) {
    // Поиск определителя
}
void powerStart(void) {
    // Поиск произведения
}
void rangStart(void) {
    // Поиск ранга
}