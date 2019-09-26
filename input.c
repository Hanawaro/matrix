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
int getDetLine(char * line, double **matrix, int i, int amountOfElements) {
    // N - номер элемента матрицы i-ой строки
    // powerF - размер целой части, powerS - размер дробной части
    // firstPartOfNumber - целая часть, secondPartOfNumber - дробная часть
    // counter - номер элемента (вывод)
    // j - номер элемента (матрица)
    // point - точка в числе
    // sign - знак числа
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
        return 3;
    // Проверяем, нет ли команды выхода
    if (!strcmp(line, C_EXIT))
        return 2;
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
    // Проверяем корректность вывода
    if (counter < amountOfElements)
        return 1;
    else 
        return 0;
}

// Получить число number из строки пользователя
int checkString(char *string, int* number) {
    // N - для букв в строке string
    // power - размер числа
    // num - само число
    // status - флаг, на существование числа в строке
    // sign - знак числа
    int N = 0,
        power = 1,
        num = 0,
        status = 0,
        sign = 1;
    // Разбираем строку, пока нет конца строки (конец точно есть, т.к. строка приходит из getCommand())
    while (string[N] != '\0') {
        // Если есть цифра, то записываем в num
        if (string[N] >= '0' && string[N] <= '9') {
            num += power*((int) (string[N] - '0'));
            power *= 10;
            status = 1;
        // Проверка знака
        } else if (string[N] == '-')
            sign = -1;
        // Если другой символ - игнорим
        else
            break;
        // Увеличиваем индекс буквы строки
        N++;
    }
    // Переворачиваем число
    int tmp = num;
    power /= 10;
    num = 0;
    
    while (power != 0) {
        num += (tmp % 10)*power;
        tmp /= 10;
        power /= 10;
    }
    // Если число существует, то всё хорошо
    if (status) {
        *number = sign*num;
        return 1;
    } else 
        return 0;
}

// Получить число (double) number из строки пользователя
int checkStringDouble(char *string, double *number) {
    // N - индентификатор символа в строке
    // powerF - размер целой части, powerS - размер дробной части
    // firstPartaOfNumber - целая часть, secondPartOfNumber - дробная часть
    // point - флаг на точку
    // status - получено ли число
    // sign - знак
    int N = 0,
        powerF = 1,
        powerS = 1,
        point = 0,
        firstPartOfNumber = 0,
        secondPartOfNumber = 0,
        status = 0,
        sign = 1;
    // Читаем каждый элемент строки
    while (string[N] != '\0') {
        // Если цифра в целой части, то записываем в firstPartOfNumber
        if (string[N] >= '0' && string[N] <= '9' && !point) {
            firstPartOfNumber += powerF*((int) (string[N] - '0'));
            powerF *= 10;
            status = 1;
        // Если цифра в целой части, то записываем в firstPartOfNumber
        } else if (string[N] >= '0' && string[N] <= '9' && point) {
            secondPartOfNumber += powerS*((int) (string[N] - '0'));
            powerS *= 10;
        // Если точка, поднимаем флаг
        } else if (string[N] == '.')
            point = 1;
        // Если отрицательно, поднимаем флаг
        else if (string[N] == '-')
            sign = -1;
        // Игнорируем другие символы
        else
            break;
        // Увеличиваем индекс символа строки
        N++;
    }
    // Переворачиваем целую часть
    int tmp = firstPartOfNumber;
    powerF /= 10;
    firstPartOfNumber = 0;

    while (powerF != 0) {
        firstPartOfNumber += (tmp % 10)*powerF;
        tmp /= 10;
        powerF /= 10;
    }
    // Переворачиваем дробную часть
    tmp = secondPartOfNumber;
    powerF = powerS / 10;
    secondPartOfNumber = 0;

    while (powerF != 0) {
        secondPartOfNumber += (tmp % 10)*powerF;
        tmp /= 10;
        powerF /= 10;
    }
    // Если число существует, то всё хорошо
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