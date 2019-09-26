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
#define C_DET "det"
#define C_POWER "pow"
#define C_RANG "rang"
#define C_EXIT "shutdown"
#define C_INVERSE "inverse"

// Команды для подконсольных приложений
#define FC_EXIT "exit"

// Функции (сами подконсольные приложения)
void helpShow(void);
int detStart(void);
int powerStart(void);
int rangStart(void);
int inverse(void);

// Мейн функция
int main(void) {
    // status - индификатор ввода
    // space - для нормального отображения "~/"
    // command - инпут пользователя
    int status = 1,
        space = 0;
    char *command = (char *) malloc(sizeof(char));
    // Проверка аллоцирования
    if (command == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }
    // Приветствие
    fprintf(stdout, "Приветствую вас в Matrix\n");
    // Ввод
    do {
        // ~/
        fprintf(stdout, "\e[0;32m~/ \033[0m");
        space = 0;
        // Ввод от пользователя
        if (getCommand(command))
            space = 1;
        // Расшифровка ввода
        // Введена просто новая строка
        if (space);
        // Введена пустая строка
        else if (strlen(command) == 0)
            fprintf(stdout, "\n");
        // Введена команды выхода
        else if (!strcmp(command, C_EXIT))
            status = 0;
        // Введена команды помощи
        else if (!strcmp(command, C_HELP))
            helpShow();
        // Введена команда нахождения определителя
        else if (!strcmp(command, C_DET))
            detStart();
        // Введена команда нахождения произведения матриц
        else if (!strcmp(command, C_POWER))
            powerStart();
        // Введена команда нахождения ранга матрицы
        else if (!strcmp(command, C_RANG))
            rangStart();
        // Введена команда нахождения обратной матрицы
        else if (!strcmp(command, C_INVERSE))
            inverse();
        // Введена неизвестная команда
        else
            fprintf(stdout, "Неизвестная комманда\nВведите help, чтобы увидеть список команд\n");
    } while (status);
    // Благодарим за использование
    fprintf(stdout, "Спасибо за использование программы.\n");
    // Освобождаем память
    free(command);
    // Завершаем программу
    return 0;
}

// ФУНКЦИЯ - помощь
void helpShow(void) {
    fprintf(stdout, "Список команд: \n");
    fprintf(stdout, " -- %s\n", C_DET);
    fprintf(stdout, " -- %s\n", C_POWER);
    fprintf(stdout, " -- %s\n", C_RANG);
    fprintf(stdout, " -- %s\n", C_INVERSE);
    fprintf(stdout, " -- %s\n", C_EXIT);
}

// ФУНКЦИЯ - нахождение определителя
int detStart(void) {
    // amount - порядок матрицы
    // status - флаг для ввода
    // matrix - сама матрица
    // data - строка ввода пользователя
    int amount = 0, 
        status = 1;
    double** matrix;
    char *data = (char *) malloc(sizeof(char));
    // Проверка аллоцирования
    if (data == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }
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
        if ( checkString(data, &amount) ) 
            if (amount <= 0)
                fprintf(stdout, "Некорректные данные...\n");
            else 
                status = 0;
        else 
            fprintf(stdout, "Некорректые данные...\n");
	} while (status);

    // Создаём первое измерение матрицы
	matrix = (double**)malloc(amount * sizeof(double*));
    // Проверка аллоцирования
    if (matrix == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }

    // Просим ввести саму матрицу
	fprintf(stdout, "Введите элементы матрицы:\n");
    // Читаем матрицу
    // Проходиммя по всем строкам
	for (int i = 0; i < amount; i++) {
        // Создаём столбцы для каждой строки
		matrix[i] = (double*)malloc(amount * sizeof(double));
        // Проверка аллоцирования
        if (matrix[i] == NULL) {
            fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
            exit(-1);
        }
        // Для красивого ввода
        fprintf(stdout, " ");
        // Читаем данные
        int stat = getDetLine(data, matrix, i, amount);
        // Если не введена команда выхода,
        if (stat == 2) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 3) {
            fprintf(stdout, "Некорректные данные...\n");
            i--;
        }
	}
    // Находим определитель матрицы и выводим его
	fprintf(stdout, "Определитель матрицы равен: %.3lf\n", findDet(matrix, amount) );
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
    double **firstMatrix,
           **secondMatrix;
    char *data = (char *) malloc(sizeof(char));
    // Проверка аллоцирования
    if (data == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }

    do {
        fprintf(stdout, "Введите количество строк первой матрицы: ");
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
            fprintf(stdout, "Некорректные данные...\n");
    } while (status);

    status = 1;

    do {
        fprintf(stdout, "Введите количество столбцов первой матрицы: ");
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
            fprintf(stdout, "Некорректные данные...\n");
    } while (status);

    firstMatrix = (double**) malloc( fsizey * sizeof(double *));
    secondMatrix = (double**) malloc( ssizey * sizeof(double *));
    // Проверка аллоцирования
    if (firstMatrix == NULL || secondMatrix == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }

    for (int i = 0; i < fsizey; i++) {
        // Создаём столбцы для каждой строки
		firstMatrix[i] = (double*)malloc(fsizex * sizeof(double));
        // Проверка аллоцирования
        if (firstMatrix[i] == NULL) {
            fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
            exit(-1);
        }
        // Для красивого ввода
        printf(" ");
        // Читаем данные
        int stat = getDetLine(data, firstMatrix, i, fsizex);
        // Если не введена команда выхода,
        if (stat == 2) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 3) {
            fprintf(stdout, "Некорректные данные...\n");
            i--;
        }
	}

    // вторая матрица

    status = 1;

    do {
        fprintf(stdout, "Введите количество строк второй матрицы: ");
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
            fprintf(stdout, "Некорректные данные...\n");
    } while (status);

    status = 1;
    
    do {
        fprintf(stdout, "Введите количество столбцов второй матрицы: ");
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
            fprintf(stdout, "Некорректные данные...\n");
    } while (status);

    fprintf(stdout, "Введите элементы второй матрицы:\n");

    for (int i = 0; i < ssizey; i++) {
        // Создаём столбцы для каждой строки
		secondMatrix[i] = (double*)malloc(ssizex * sizeof(double));
        if (secondMatrix[i] == NULL) {
            fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
            exit(-1);
        }
        // Для красивого ввода
        printf(" ");
        // Читаем данные
        int stat = getDetLine(data, secondMatrix, i, ssizex);
        // Если не введена команда выхода,
        if (stat == 2) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 3) {
            fprintf(stdout, "Некорректные данные...\n");
            i--;
        }
	}

    double **matrix = power(firstMatrix, fsizey, fsizex, secondMatrix, ssizey, ssizex);
    
    if (matrix) {
        fprintf(stdout, "Результат произведения:\n\n");
        for ( int i = 0; i < fsizey; i++ ) {
            fprintf(stdout, "\t");
            for ( int j = 0; j < ssizex; j++ )
                fprintf(stdout, "%.3lf ", matrix[i][j]); 
            fprintf(stdout, "\n");
        }
        fprintf(stdout, "\n");
    }

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
    if (data == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }

	do {
        fprintf(stdout, "Введите количество строк матрицы, для нахождения её ранга: ");
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
                fprintf(stdout, "Некорректные данные...\n");
        else
            fprintf(stdout, "Некорректные данные...\n");
	} while (status);

    status = 1;

    do {
        fprintf(stdout, "Введите количество столбцов матрицы, для нахождения её ранга: ");
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
                fprintf(stdout, "Некорректные данные...\n");
        else
            fprintf(stdout, "Некорректные данные...\n");
	} while (status);

    matrix = (double**)malloc(amountY * sizeof(double*));
    if (matrix == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }
    
    fprintf(stdout, "Введите элементы матрицы:\n");
	for (int i = 0; i < amountY; i++) {
        // Создаём столбцы для каждой строки
		matrix[i] = (double*)malloc(amountX * sizeof(double));
        // Проверка аллоцирования
        if (matrix[i] == NULL) {
            fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
            exit(-1);
        }
        // Для красивого ввода
        fprintf(stdout, " ");
        // Читаем данные
        int stat = getDetLine(data, matrix, i, amountX);
        // Если не введена команда выхода,
        if (stat == 2) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 3) {
            fprintf(stdout, "Некорректные данные...\n");
            i--;
        }
	}

    int rang = findRang(matrix, amountY, amountX);
    fprintf(stdout, "Ранг матрицы равен %d\n", rang);

    for (int i = 0; i < amountY; i++)
		free(matrix[i]);
	free(matrix);
    free(data);
	return 0;
}

int inverse(void) {
    // amount - порядок матрицы
    // status - флаг для ввода
    // matrix - сама матрица
    // data - строка ввода пользователя
    int amount = 0, 
        status = 1;
    double det = 0.;
    double** matrix;
    char *data = (char *) malloc(sizeof(char));
    // Проверка аллоцирования
    if (data == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }
    // Читаем порядок матрицы
	do {
        // Просим ввести порядок матрицы
	    fprintf(stdout, "Введите порядок матрицы, для нахождения обратной ей матрицы: ");
        // Читаем стркоу
        getCommand(data);
        // Если в ней нет команды выхода, то продолжаем
        if (!strcmp(data, FC_EXIT))
            return 0;
        // Проверяем на корректность входные данные
        if ( checkString(data, &amount) ) {
            if (amount <= 1)
                fprintf(stdout, "Некорректные данные...\n");
            else 
                status = 0;
        } else 
            fprintf(stdout, "Некорректые данные...\n");
	} while (status);

    // Создаём первое измерение матрицы
	matrix = (double**)malloc(amount * sizeof(double*));
    // Проверка аллоцирования
    if (matrix == NULL) {
        fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
        exit(-1);
    }

    // Просим ввести саму матрицу
	fprintf(stdout, "Введите элементы матрицы:\n");
    // Читаем матрицу
    // Проходиммя по всем строкам
	for (int i = 0; i < amount; i++) {
        // Создаём столбцы для каждой строки
		matrix[i] = (double*)malloc(amount * sizeof(double));
        // Проверка аллоцирования
        if (matrix[i] == NULL) {
            fprintf(stdout, "Произошла ошибка аллоцирования памяти\n");
            exit(-1);
        }
        // Для красивого ввода
        printf(" ");
        // Читаем данные
        int stat = getDetLine(data, matrix, i, amount);
        // Если не введена команда выхода,
        if (stat == 2) 
            return 0;
        // Проверяем на корректность
        else if (stat == 1 || stat == 3) {
            fprintf(stdout, "Некорректные данные...\n");
            i--;
        }
	}
    double **result = findInverse(matrix, amount, &det);
    if (det != 0.0) {
        if (result) {
            fprintf(stdout, "Обратная матрица:\n\n");
            for ( int i = 0; i < amount; i++ ) {
                fprintf(stdout, "\t|   ");
                for ( int j = 0; j < amount; j++ )
                    fprintf(stdout, "%7.3lf ", result[i][j]); 
                fprintf(stdout, "\t|");
                if ( i == amount / 2)
                    fprintf(stdout, " * ( 1 / %4.3lf )\n", det);
                else
                    fprintf(stdout, "\n");
            }
            fprintf(stdout, "\n");
        }
    } else 
       fprintf(stdout, "Для этой матрицы не существует обратной\n");

    for (int i = 0; i < amount; i++) {
        free(result[i]);
        free(matrix[i]);
    }
    free(result);
    free(matrix);

    free(data);

    return 0;
}