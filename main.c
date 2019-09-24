// Стандартные библиотеки
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Библиотека с матричными операциями
#include "matrix.h"
// Библиотека для работы с инпутами
#include "input.h"

// Константы для главных команд
#define C_HELP "help"
#define C_OPREDELITEL "det"
#define C_POWER "pow"
#define C_RANG "rang"
#define C_EXIT "shutdown"

// Команды для подконсольных приложений
#define FC_EXIT "exit"

// Функции (сами подконсольные приложения)
void helpShow(void);
int opredelitelStart(void);
int powerStart(void);
int rangStart(void);

// Мейн функция
int main(void) {
    // status - индификатор ввода
    // space - для нормального отображения "~/"
    // command - инпут пользователя
    int status = 1,
        space = 0;
    char *command = (char *) malloc(sizeof(char));
    // Приветствие
    fprintf(stdout, "Приветствую вас в Matrix\n");
    // Ввод
    do {
        // ~/
        fprintf(stdout, "\e[0;32m~/ \033[0m");
        space = 0;
        // Ввод от пользователя
        if ( getCommand(command) )
            space = 1;
        // Расшифровка ввода
        // Введена просто новая строка
        if ( space );
        // Введена пустая строка
        else if ( strlen(command) == 0 )
            fprintf(stdout, "\n");
        // Введена команды выхода
        else if (!strcmp(command, C_EXIT))
            status = 0;
        // Введена команды помощи
        else if (!strcmp(command, C_HELP))
            helpShow();
        // Введена команда нахождения определителя
        else if (!strcmp(command, C_OPREDELITEL))
            opredelitelStart();
        // Введена команда нахождения произведения матриц
        else if (!strcmp(command, C_POWER))
            powerStart();
        // Введена команда нахождения ранга матрицы
        else if (!strcmp(command, C_RANG))
            rangStart();
        // Введена неизвестная команда
        else
            fprintf(stdout, "Неизвестная комманда\nВведите help, чтобы увидеть список команд\n");
    } while (status);
    // Освобождаем память
    free(command);
    // Завершаем программу
    return 0;
}

// ФУНКЦИЯ - помощь
void helpShow(void) {
    fprintf(stdout, "Список команд: \n");
    fprintf(stdout, " -- %s\n", C_OPREDELITEL);
    fprintf(stdout, " -- %s\n", C_POWER);
    fprintf(stdout, " -- %s\n", C_RANG);
    fprintf(stdout, " -- %s\n", C_EXIT);
}

// ФУНКЦИЯ - нахождение определителя
int opredelitelStart(void) {
    // amount - порядок матрицы
    // status - флаг для ввода
    // matrix - сама матрица
    // data - строка ввода пользователя
    int amount = 0, 
        status = 1;
    double** matrix;
    char *data = (char *) malloc(sizeof(char));
    // Читаем ранг матрицы
	do {
        // Просим ввести ранг матрицы
	    fprintf(stdout, "Введите порядок матрицы, для нахождения её определителя: ");
        // Читаем стркоу
        getCommand(data);
        // Если в ней нет команды выхода, то продолжаем
        if (!strcmp(data, FC_EXIT))
            return 0;
        // Проверяем на корректность входные данные
        if ( checkString(data, &amount) ) {
            if (amount <= 0)
                printf("Некорректные данные...\n");
            else 
                status = 0;
        } else 
            printf("Некорректые данные...\n");
	} while (status);

    // Создаём первое измерение матрицы
	matrix = (double**)malloc(amount * sizeof(double*));
    // Освобождаем память для строки
    free(data);
    // И создаём новую строку пользователя
    data = (char *) malloc(sizeof(char));

    // Просим ввести саму матрицу
	fprintf(stdout, "Введите элементы матрицы:\n");
    // Читаем матрицу
    // Проходиммя по всем строкам
	for (int i = 0; i < amount; i++) {
        // Создаём столбцы для каждой строки
		matrix[i] = (double*)malloc(amount * sizeof(double));
        // Для красивого ввода
        printf(" ");
        // Читаем данные
        int stat = getOpredelitelLine(data, matrix, i, amount);
        // Если не введена команда выхода,
        if (stat == 3) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 4) {
            printf("Некорректные данные...\n");
            i--;
        }
	}
    // Находим определитель матрицы и выводим его
	fprintf(stdout, "Определитель матрицы равен: %.3lf\n", findOpedelitel(matrix, amount) );
    // Освобождаем память
	for (int i = 0; i < amount; i++)
		free(matrix[i]);
	free(matrix);
    free(data);
    // Завершаем работу подпрограммы
    return 0;
}

// ФУНКЦИЯ - произведение матриц
int powerStart(void) {
    int fsizey = 0, 
        fsizex = 0, 
        ssizey = 0, 
        ssizex = 0, 
        status = 1;
    double **firstMatrix = (double**) malloc( fsizey * sizeof(double *));
    double **secondMatrix = (double**) malloc( ssizey * sizeof(double *));
    char *data = (char *) malloc(sizeof(char));
    
    if ( firstMatrix == NULL || secondMatrix == NULL ) {
        printf("Что-то пошло не так\n");
        return -1;
    }

    do {
        printf("Введите количество строк первой матрицы: ");
        // Читаем стркоу
        getCommand(data);
        // Если в ней нет команды выхода, то продолжаем
        if (!strcmp(data, FC_EXIT))
            return 0;
        // Проверяем на корректность входные данные
        checkString(data, &fsizey);

        if (fsizey > 0)
            status = 0;
        else
            printf("Некорректные данные...\n");
    } while (status);

    status = 1;
    free(data);
    data = (char *) malloc(sizeof(char));

    do {
        printf("Введите количество столбцов первой матрицы: ");
        // Читаем стркоу
        getCommand(data);
        // Если в ней нет команды выхода, то продолжаем
        if (!strcmp(data, FC_EXIT))
            return 0;
        // Проверяем на корректность входные данные
        checkString(data, &fsizex);

        if (fsizex > 0)
            status = 0;
        else
            printf("Некорректные данные...\n");
    } while (status);

    for (int i = 0; i < fsizey; i++) {
        // Создаём столбцы для каждой строки
		firstMatrix[i] = (double*)malloc(fsizex * sizeof(double));
        // Для красивого ввода
        printf(" ");
        // Читаем данные
        int stat = getOpredelitelLine(data, firstMatrix, i, fsizex);
        // Если не введена команда выхода,
        if (stat == 3) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 4) {
            printf("Некорректные данные...\n");
            i--;
        }
	}

    // вторая матрица

    status = 1;
    free(data);
    data = (char *) malloc(sizeof(char));

    do {
        printf("Введите количество строк второй матрицы: ");
        // Читаем стркоу
        getCommand(data);
        // Если в ней нет команды выхода, то продолжаем
        if (!strcmp(data, FC_EXIT))
            return 0;
        // Проверяем на корректность входные данные
        checkString(data, &ssizey);

        if (ssizey > 0)
            status = 0;
        else
            printf("Некорректные данные...\n");
    } while (status);

    status = 1;
    free(data);
    data = (char *) malloc(sizeof(char));
    
    do {
        printf("Введите количество столбцов второй матрицы: ");
        // Читаем стркоу
        getCommand(data);
        // Если в ней нет команды выхода, то продолжаем
        if (!strcmp(data, FC_EXIT))
            return 0;
        // Проверяем на корректность входные данные
        checkString(data, &ssizex);

        if (ssizex > 0)
            status = 0;
        else
            printf("Некорректные данные...\n");
    } while (status);

    printf("Введите элементы второй матрицы:\n");

    for (int i = 0; i < ssizey; i++) {
        // Создаём столбцы для каждой строки
		secondMatrix[i] = (double*)malloc(ssizex * sizeof(double));
        // Для красивого ввода
        printf(" ");
        // Читаем данные
        int stat = getOpredelitelLine(data, secondMatrix, i, ssizex);
        // Если не введена команда выхода,
        if (stat == 3) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 4) {
            printf("Некорректные данные...\n");
            i--;
        }
	}

    double **matrix = power(firstMatrix, fsizey, fsizex, secondMatrix, ssizey, ssizex);
    
    if (matrix) {
        printf("Результат произведения:\n\n");
        for ( int i = 0; i < fsizey; i++ ) {
            printf("\t");
            for ( int j = 0; j < ssizex; j++ )
                printf("%.3lf ", matrix[i][j]); 
            printf("\n");
        }
        printf("\nСпасибо за использование программы.\n");
    } else 
        printf("Некорректные размеры матриц\n");

    for (int i = 0; i < fsizey; i++)
        free(firstMatrix[i]);
    free(firstMatrix);

    for (int i = 0; i < ssizey; i++)
        free(secondMatrix[i]);
    free(secondMatrix);

    free(data);
    return 0;
}
// ФУНКЦИЯ - ранг матрицы
int rangStart(void) {
    int amountY = 0,
        amountX = 0, 
        status = 1;
    char *data = (char *) malloc(sizeof(char));
	double** matrix;

	do {
        printf("Введите количество строк матрицы, для нахождения её ранга: ");
		// Читаем стркоу
        getCommand(data);
        // Если в ней нет команды выхода, то продолжаем
        if (!strcmp(data, FC_EXIT))
            return 0;
        // Проверяем на корректность входные данные
        if ( checkString(data, &amountY) ) 
            if (amountY > 0)
                status = 0;
            else
                printf("Некорректные данные...\n");
        else
            printf("Некорректные данные...\n");
	} while (status);

    status = 1;
    free(data);
    data = (char *) malloc(sizeof(char));

    do {
        printf("Введите количество столбцов матрицы, для нахождения её ранга: ");
		// Читаем стркоу
        getCommand(data);
        // Если в ней нет команды выхода, то продолжаем
        if (!strcmp(data, FC_EXIT))
            return 0;
        // Проверяем на корректность входные данные
        if ( checkString(data, &amountX) )
            if (amountX > 0)
                status = 0;
            else
                printf("Некорректные данные...\n");
        else
            printf("Некорректные данные...\n");
	} while (status);

    free(data);
    data = (char *) malloc(sizeof(char));
    matrix = (double **) malloc(amountY * sizeof(double *));
    
    printf("Введите элементы матрицы:\n");
	for (int i = 0; i < amountY; i++) {
        // Создаём столбцы для каждой строки
		matrix[i] = (double*)malloc(amountX * sizeof(double));
        // Для красивого ввода
        printf(" ");
        // Читаем данные
        int stat = getOpredelitelLine(data, matrix, i, amountX);
        // Если не введена команда выхода,
        if (stat == 3) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 4) {
            printf("Некорректные данные...\n");
            i--;
        }
	}

    int rang = findRang(matrix, amountY, amountX);
    printf("Ранг матрицы равен %d\n", rang);

    for (int i = 0; i < amountY; i++)
		free(matrix[i]);
	free(matrix);
    free(data);
	return 0;
}