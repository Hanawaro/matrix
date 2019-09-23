#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

#define C_HELP "help"
#define C_OPREDELITEL "opredelitel"
#define C_POWER "power"
#define C_RANG "rang"
#define C_EXIT "shutdown"

#define FC_EXIT "exit"

int getCommand(char *string);
int checkString(char *string, int *number);
void helpShow(void);
int opredelitelStart(void);
int powerStart(void);
int rangStart(void);

int getOpredelitelLine(char * line);

int main(void) {
    int status = 1,
        space = 0;
    char *command = (char *) malloc(sizeof(char));
    fprintf(stdout, " Приветствую вас в matrix\n");
    do {
        fprintf(stdout, "~/ ");
        space = 0;
        int c;
        if ( getCommand(command) )
            space = 1;

        if ( space );
        else if ( strlen(command) == 0 )
            fprintf(stdout, "\n");
        else if (!strcmp(command, C_EXIT))
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
            fprintf(stdout, " Неизвестная комманда\nВведите help, чтобы увидеть список команд\n");
    } while (status);

    fprintf(stdout, " Спасибо за использование программы.\n");

    free(command);
    
    return 0;
}

int getCommand(char *string) {
    int N = 0;
    while ( (string[N] = getchar()) != EOF && string[N] != '\n' && string[N] != '\0') {
        N++;
        string = (char *) realloc(string, sizeof(char) * N);
    }
    if (string[N] == '\n' && N == 0) {
        string[N] = '\0';
        return 1;
    } else {
        string[N] = '\0';
        return 0;
    }
}

int checkString(char *string, int* number) {
    int N = 0,
        power = 1,
        num = 0,
        status = 0;
    while (string[N] != '\0') {
        if (string[N] >= '0' && string[N] <= '9') {
            *number += power*((int) (string[N] - '0'));
            power *= 10;
            status = 1;
        } else 
            break;
        N++;
    }
    if (status)
        return 1;
    else 
        return 0;
}

void helpShow(void) {
    fprintf(stdout, " Список команд: \n");
    fprintf(stdout, "  -- %s\n", C_OPREDELITEL);
    fprintf(stdout, "  -- %s\n", C_POWER);
    fprintf(stdout, "  -- %s\n", C_RANG);
    fprintf(stdout, "  -- %s\n", C_EXIT);
}

int opredelitelStart(void) {
    // Заменить int на double
    int amount = 0, status = 1;
    char *data = (char *) malloc(sizeof(char));
	int** matrix;
    
	fprintf(stdout, " Введите порядок матрицы, для нахождения её определителя: ");
	do {
        getCommand(data);
        if (!strcmp(data, FC_EXIT))
            return 0;
        if ( checkString(data, &amount) ) {
            if (amount <= 0)
                printf(" Некорректные данные...\n");
            else 
                status = 0;
        } else {
            printf(" Некорректые данные...\n");
        }
	} while (status);

	fprintf(stdout, " Введите элементы матрицы:\n");

	matrix = (int**)malloc(amount * sizeof(int*));

    // Сделать ввод чего угодно (нужна функция getLineOpredelitel() )
    do {
		status = 0;
		for (int i = 0; i < amount; i++) {
			matrix[i] = (int*)malloc(amount * sizeof(int));
            printf(" ");
			for (int j = 0; j < amount; j++)
				if (scanf("%d", &matrix[i][j]) != 1) {
					status = 1;
				}
		}
	} while (status);

	fprintf(stdout, " Определитель матрицы равен: %d\n", findOpedelitel(matrix, amount) );

	for (int i = 0; i < amount; i++)
		free(matrix[i]);
	free(matrix);
    free(data);

    int c;
    while ((c = getchar()) != '\n' && c != EOF && c != '\0') { }

    return 0;
}
int powerStart(void) {
    // Поиск произведения
    return 0;
}
int rangStart(void) {
    // Поиск ранга
    return 0;
}