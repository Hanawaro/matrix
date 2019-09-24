// Подключаем стандартные библиотке
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Подключение заголовочных файлов input
#include "input.h"
// Команда выхода из подпрограммы
#define C_EXIT "exit"

// Получить строку string от пользователя
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
// Получить данные для i-ой строки матрицы matrix
int getOpredelitelLine(char * line, double **matrix, int i, int amountOfElements) {
    int N = 0, 
        statusOfNumber = 0,
        powerF = 1,
        powerS = 1,
        firstPartOfNumber = 0,
        secondPartOfNumber = 0,
        counter = 0,
        point = 0,
        j = 0,
        sign = 1;
    // Получаем строку пользователя
    getCommand(line);
    if (strlen(line) == 0)
        return 4;
    // Проверяем, нет ли команды выхода
    if (!strcmp(line, C_EXIT))
        return 3;
    // Начинаем считывание
    while ( line[N] != '\0') {
        // Если цифра 0-9 и не было ещё точки, то добавляем к tmp элементу (до точки)
        if (line[N] >= '0' && line[N] <= '9' && !point) {
            firstPartOfNumber += powerF*((int) (line[N] - '0'));
            powerF *= 10;
            statusOfNumber = 1;
        // Если цифра 0-9 и точка уже была, то добавляем к tmp элементу (после точки) 
        } else if(line[N] >= '0' && line[N] <= '9' && point) {
            secondPartOfNumber += powerS*((int) (line[N] - '0'));
            powerS *= 10;
            statusOfNumber = 1;
        // Если точка, то поднимаем флаг
        } else if (line[N] == '.') {
            point = 1;
        // Если минус, то созраняем отрицательность
        } else if (line[N] == '-') {
            sign = -1;
        // Если пробел, то добавляем элемент в матрицу
        } else if (line[N] == ' ' && statusOfNumber) {
            // Переворачиваем число до точки
            int tmp = firstPartOfNumber;
            powerF /= 10;
            firstPartOfNumber = 0;

            while (powerF != 0) {
                firstPartOfNumber += (tmp % 10)*powerF;
                tmp /= 10;
                powerF /= 10;
            }
            // Переворачиваем число после точки
            tmp = secondPartOfNumber;
            powerF = powerS / 10;
            secondPartOfNumber = 0;

            while (powerF != 0) {
                secondPartOfNumber += (tmp % 10)*powerF;
                tmp /= 10;
                powerF /= 10;
            }
            // Записываем
            if (j < amountOfElements)
                matrix[i][j] = sign * ( (double) firstPartOfNumber + ((double) secondPartOfNumber / (double) powerS) );
            j++;
            // Всё обнуляем
            secondPartOfNumber = firstPartOfNumber =  point = statusOfNumber = 0;
            sign = powerF = powerS = 1;
            // Увеличиваем счётчик
            counter++;
        }
        // Смотрим следующий символ
        N++;
    }
    // Переворачиваем число до точки
    int tmp = firstPartOfNumber;
    powerF /= 10;
    firstPartOfNumber = 0;
        
    while (powerF != 0) {
        firstPartOfNumber += (tmp % 10)*powerF;
        tmp /= 10;
        powerF /= 10;
    }
    // Переворачиваем число после точки
    tmp = secondPartOfNumber;
    powerF = powerS / 10;
    secondPartOfNumber = 0;

    while (powerF != 0) {
        secondPartOfNumber += (tmp % 10)*powerF;
        tmp /= 10;
        powerF /= 10;
    }
    // Записываем
    if (j <= amountOfElements)
        matrix[i][j] = sign * ( (double) firstPartOfNumber + ((double) secondPartOfNumber / (double) powerS) );
    counter++;
    if (counter < amountOfElements)
        return 1;
    else 
        return 0;
}
// Получить число number из строки пользователя
int checkString(char *string, int* number) {
    int N = 0,
        power = 1,
        num = 0,
        status = 0,
        sign = 1;
    while (string[N] != '\0') {
        if (string[N] >= '0' && string[N] <= '9') {
            num += power*((int) (string[N] - '0'));
            power *= 10;
            status = 1;
        } else if (string[N] == '-')
            sign = -1;
        else
            break;
        N++;
    }

    int tmp = num;
    power /= 10;
    num = 0;
    
    while (power != 0) {
        num += (tmp % 10)*power;
        tmp /= 10;
        power /= 10;
    }

    *number = sign*num;
    
    if (status)
        return 1;
    else 
        return 0;
}
// Получить число (double) number из строки пользователя
int checkStringDouble(char *string, double *number) {
    int N = 0,
        powerF = 1,
        powerS = 1,
        point = 0,
        firstPartOfNumber = 0,
        secondPartOfNumber = 0,
        status = 0,
        sign = 1;

    while (string[N] != '\0') {
        if (string[N] >= '0' && string[N] <= '9' && !point) {
            firstPartOfNumber += powerF*((int) (string[N] - '0'));
            powerF *= 10;
            status = 1;
        } else if (string[N] >= '0' && string[N] <= '9' && point) {
            secondPartOfNumber += powerS*((int) (string[N] - '0'));
            powerS *= 10;
        } else if (string[N] == '.')
            point = 1;
        else if (string[N] == '-')
            sign = -1;
        else
            break;
        N++;
    }

    int tmp = firstPartOfNumber;
    powerF /= 10;
    firstPartOfNumber = 0;

    while (powerF != 0) {
        firstPartOfNumber += (tmp % 10)*powerF;
        tmp /= 10;
        powerF /= 10;
    }

    tmp = secondPartOfNumber;
    powerF = powerS / 10;
    secondPartOfNumber = 0;

    while (powerF != 0) {
        secondPartOfNumber += (tmp % 10)*powerF;
        tmp /= 10;
        powerF /= 10;
    }

    if (status) {
        *number = sign * ( (double) firstPartOfNumber + ((double) secondPartOfNumber / (double) powerS) );
        return 1;
    } else 
        return 0;
}
// Очистить буфер
void clearBufer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF && c != '\0') { }
}