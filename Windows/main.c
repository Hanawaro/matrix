#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "string.h"
#include "matrix.h"

#define PROGRAME_EXIT "shutdown"
#define PROGRAME_HELP "help"
#define PROGRAME_DETERMINANT "det"
#define PROGRAME_POWER "pow"
#define PROGRAME_RANG "rang"
#define PROGRAME_INVERSE "inverse"
#define COMMAND_EXIT "exit"

void do_exit(void);
void do_help(void);
int do_det(void);
int do_pow(void);
int do_rang(void);
int do_inverse(void);
void do_unknown(void);

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUSSIAN");
    int workStatus = 1;
    string_t *command = createline();
    do {
        fprintf(stdout, "~/ ");
        getcommand(command);

        if (!compareline(command, "\0")) {
            fprintf(stdout, "\n");
        } else if (!compareline(command, "\n")) {
            do_unknown();
        } else if (!compareline(command, PROGRAME_EXIT)) {
            do_exit();
            workStatus = 0;
        } else if (!compareline(command, PROGRAME_HELP)) {
            do_help();
        } else if (!compareline(command, PROGRAME_DETERMINANT)) {
            do_det();
        } else if (!compareline(command, PROGRAME_POWER)) {
            do_pow();
        } else if (!compareline(command, PROGRAME_RANG)) {
            do_rang();
        } else if (!compareline(command, PROGRAME_INVERSE)) {
            do_inverse();
        } else {
            do_unknown();
        }

        clearstring(command);
    } while (workStatus);

    deleteline(command);
    return 0;
}

void do_exit(void) {
    fprintf(stdout, "Спасибо за использование программы.\n");
}

void do_help(void) {
    fprintf(stdout, "Сейчас вам доступны следующие команды: \n");
    fprintf(stdout, " -- %s\n", PROGRAME_HELP);
    fprintf(stdout, " -- %s\n", PROGRAME_DETERMINANT);
    fprintf(stdout, " -- %s\n", PROGRAME_POWER);
    fprintf(stdout, " -- %s\n", PROGRAME_RANG);
    fprintf(stdout, " -- %s\n", PROGRAME_INVERSE);
    fprintf(stdout, " -- %s\n", PROGRAME_EXIT);

}
int do_det(void){
    string_t *data = createline();
    int inputStatus = 1;
    double sizeYX = 0.,
           result = 0.;
    double **matrix;
    do {
        fprintf(stdout, "Введите порядок матрицы: ");
        getcommand(data);
        int flag = readDouble(data, COMMAND_EXIT, &sizeYX);
        clearstring(data);
        if (flag == 0 && (int) sizeYX >= 1)
            inputStatus = 0;
        else if (flag == 1)
            return 0;
        else 
            fprintf(stdout, "Некорректные данные...\n");
    } while (inputStatus);

    matrix = (double**) malloc(sizeYX * sizeof(double*));
    for (int i = 0; i < sizeYX; i++)
        matrix[i] = (double*) malloc(sizeYX * sizeof(double));

    fprintf(stdout, "Введите элементы матрицы: \n");
    for (int i = 0; i < sizeYX; i++) {
        fprintf(stdout, " ");
            getcommand(data);
            int flag = readDoubles(data, COMMAND_EXIT, matrix[i], sizeYX);
            clearstring(data);
            if (flag == 1)
                return 0;
            else if (flag < 0) {
                i--;
                fprintf(stdout, "Некорректные данные...\n");
            } 
    }

    deleteline(data);

    int flag = findDet(matrix, (int) sizeYX, &result);
    if (flag == -4 || flag == -5)
        fprintf(stdout, "Непредвиденная ошибка\n");
    else
        fprintf(stdout, "Определитель матрицы равен %.3lf\n", result);

    for (int i = 0; i < sizeYX; i++)
        free(matrix[i]);
    free(matrix);
    return 0;
}

int do_pow(void) {
    string_t *data = createline();
    int inputStatus = 1;
    double firstSizeY = 0.,
           firstSizeX = 0.,
           secondSizeY = 0.,
           secondSizeX = 0.;
    double **firstMatrix, **secondMatrix, **resultMatrix;
    do {
        fprintf(stdout, "Введите количество строк первой матрицы: ");
        getcommand(data);
        int flag = readDouble(data, COMMAND_EXIT, &firstSizeY);
        clearstring(data);
        if (flag == 0 && (int) firstSizeY >= 1)
            inputStatus = 0;
        else if (flag == 1)
            return 0;
        else 
            fprintf(stdout, "Некорректные данные...\n");
    } while (inputStatus);
    inputStatus = 1;
    do {
        fprintf(stdout, "Введите количество столбцов первой матрицы: ");
        getcommand(data);
        int flag = readDouble(data, COMMAND_EXIT, &firstSizeX);
        clearstring(data);
        if (flag == 0 && (int) firstSizeX >= 1)
            inputStatus = 0;
        else if (flag == 1)
            return 0;
        else 
            fprintf(stdout, "Некорректные данные...\n");
    } while (inputStatus);

    firstMatrix = (double**) malloc(firstSizeY * sizeof(double*));
    for (int i = 0; i < firstSizeY; i++)
        firstMatrix[i] = (double*) malloc(firstSizeX * sizeof(double));

    fprintf(stdout, "Введите элементы первой матрицы: \n");
    for (int i = 0; i < firstSizeY; i++) {
        fprintf(stdout, " ");
            getcommand(data);
            int flag = readDoubles(data, COMMAND_EXIT, firstMatrix[i], firstSizeX);
            clearstring(data);
            if (flag == 1)
                return 0;
            else if (flag < 0) {
                i--;
                fprintf(stdout, "Некорректные данные...\n");
            } 
    }

    inputStatus = 1;
    do {
        fprintf(stdout, "Введите количество строк второй матрицы: ");
        getcommand(data);
        int flag = readDouble(data, COMMAND_EXIT, &secondSizeY);
        clearstring(data);
        if (flag == 0 && (int) secondSizeY >= 1)
            inputStatus = 0;
        else if (flag == 1)
            return 0;
        else 
            fprintf(stdout, "Некорректные данные...\n");
    } while (inputStatus);
    inputStatus = 1;
    do {
        fprintf(stdout, "Введите количество столбцов второй матрицы: ");
        getcommand(data);
        int flag = readDouble(data, COMMAND_EXIT, &secondSizeX);
        clearstring(data);
        if (flag == 0 && (int) secondSizeX >= 1)
            inputStatus = 0;
        else if (flag == 1)
            return 0;
        else 
            fprintf(stdout, "Некорректные данные...\n");
    } while (inputStatus);

    secondMatrix = (double**) malloc(secondSizeY * sizeof(double*));
    for (int i = 0; i < secondSizeY; i++)
        secondMatrix[i] = (double*) malloc(secondSizeX * sizeof(double));

    fprintf(stdout, "Введите элементы второй матрицы: \n");
    for (int i = 0; i < secondSizeY; i++) {
        fprintf(stdout, " ");
            getcommand(data);
            int flag = readDoubles(data, COMMAND_EXIT, secondMatrix[i], secondSizeX);
            clearstring(data);
            if (flag == 1)
                return 0;
            else if (flag < 0) {
                i--;
                fprintf(stdout, "Некорректные данные...\n");
            } 
    }

    deleteline(data);

    int flag = power(firstMatrix, (int) firstSizeY, (int) firstSizeX, secondMatrix, (int) secondSizeY, (int) secondSizeX, &resultMatrix);
    if (flag == -4 || flag == -5)
        fprintf(stdout, "Непредвиденная ошибка\n");
    else {
        fprintf(stdout, "Результат произведения: \n");
        for (int i = 0; i < firstSizeY; i++) {
            fprintf(stdout, " ");
            for (int j = 0; j < secondSizeX; j++)
                fprintf(stdout, "%.3lf ", resultMatrix[i][j]);
            fprintf(stdout, "\n");
        }
    }
    
    for (int i = 0; i < firstSizeY; i++)
        free(firstMatrix[i]);
    free(firstMatrix);
    for (int i = 0; i < secondSizeY; i++)
        free(secondMatrix[i]);
    free(secondMatrix);
    for (int i = 0; i < firstSizeY; i++)
        free(resultMatrix[i]);
    free(resultMatrix);

    return 0;
}

int do_rang(void) {
    string_t *data = createline();
    int inputStatus = 1,
        result = 0;
    double sizeY = 0.,
           sizeX = 0.;
    double **matrix;
    do {
        fprintf(stdout, "Введите количество строк матрицы: ");
        getcommand(data);
        int flag = readDouble(data, COMMAND_EXIT, &sizeY);
        clearstring(data);
        if (flag == 0 && (int) sizeY >= 1)
            inputStatus = 0;
        else if (flag == 1)
            return 0;
        else 
            fprintf(stdout, "Некорректные данные...\n");
    } while (inputStatus);
    inputStatus = 1;
    do {
        fprintf(stdout, "Введите количество столбцов матрицы: ");
        getcommand(data);
        int flag = readDouble(data, COMMAND_EXIT, &sizeX);
        clearstring(data);
        if (flag == 0 && (int) sizeX >= 1)
            inputStatus = 0;
        else if (flag == 1)
            return 0;
        else 
            fprintf(stdout, "Некорректные данные...\n");
    } while (inputStatus);

    matrix = (double**) malloc(sizeY * sizeof(double*));
    for (int i = 0; i < sizeY; i++)
        matrix[i] = (double*) malloc(sizeX * sizeof(double));

    fprintf(stdout, "Введите элементы первой матрицы: \n");
    for (int i = 0; i < sizeY; i++) {
        fprintf(stdout, " ");
            getcommand(data);
            int flag = readDoubles(data, COMMAND_EXIT, matrix[i], sizeX);
            clearstring(data);
            if (flag == 1)
                return 0;
            else if (flag < 0) {
                i--;
                fprintf(stdout, "Некорректные данные...\n");
            } 
    }

    deleteline(data);

    int flag = findRang(matrix, (int) sizeY, (int) sizeX, &result);
    if (flag == -3)
        fprintf(stdout, "Непредвиденная ошибка\n");
    else
        fprintf(stdout, "Ранг матрицы равен %d\n", result);

    for (int i = 0; i < sizeY; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}

int do_inverse(void) {
    string_t *data = createline();
    int inputStatus = 1;
    double sizeYX = 0.,
           det = 0.;
    double **matrix, **resultMatrix;
    do {
        fprintf(stdout, "Введите порядок матрицы: ");
        getcommand(data);
        int flag = readDouble(data, COMMAND_EXIT, &sizeYX);
        clearstring(data);
        if (flag == 0 && (int) sizeYX >= 1)
            inputStatus = 0;
        else if (flag == 1)
            return 0;
        else 
            fprintf(stdout, "Некорректные данные...\n");
    } while (inputStatus);

    matrix = (double**) malloc(sizeYX * sizeof(double*));
    for (int i = 0; i < sizeYX; i++)
        matrix[i] = (double*) malloc(sizeYX * sizeof(double));

    fprintf(stdout, "Введите элементы матрицы: \n");
    for (int i = 0; i < sizeYX; i++) {
        fprintf(stdout, " ");
            getcommand(data);
            int flag = readDoubles(data, COMMAND_EXIT, matrix[i], sizeYX);
            clearstring(data);
            if (flag == 1)
                return 0;
            else if (flag < 0) {
                i--;
                fprintf(stdout, "Некорректные данные...\n");
            } 
    }

    deleteline(data);

    int flag = findInverse(matrix, sizeYX, &det, &resultMatrix);
    if (flag == -2 || flag == -4)
        fprintf(stdout, "Непредвиденная ошибка\n");
    else if (flag == -3)
        fprintf(stdout, "Невозможно найти обратную матрицу к данной");
    else {
        fprintf(stdout, "Обратная матрица: ");
        fprintf(stdout, "Обратная матрица:\n\n");
            for ( int i = 0; i < sizeYX; i++ ) {
                fprintf(stdout, "\t|   ");
                for ( int j = 0; j < sizeYX; j++ )
                    fprintf(stdout, "%7.3lf ", resultMatrix[i][j]); 
                fprintf(stdout, "\t|");
                if ( i == (int) sizeYX / 2)
                    fprintf(stdout, " * ( 1 / %4.3lf )\n", det);
                else
                    fprintf(stdout, "\n");
            }
            fprintf(stdout, "\n");
    }

    for (int i = 0; i < sizeYX; i++)
        free(matrix[i]);
    free(matrix);
    for (int i = 0; i < sizeYX; i++)
        free(resultMatrix[i]);
    free(resultMatrix);

    return 0;
}

void do_unknown(void) {
    fprintf(stdout, "Неизвестная команда\n");
    fprintf(stdout, "Чтобы просмотреть список команд, введите help\n");
}