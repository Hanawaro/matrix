﻿/*
        Тип данных для строки*
    Длина строки включает в себя нуль-символ ("123\0" - 4)
    Включает саму строку
*/
typedef struct line string_t;

/*
        Создание строки
    Возвращает NULL, если не удалось создать строку*
    Иначе возращает указатель на строку*
*/ 
string_t* createline();

/*
        Удаление строки
    Возвращает 0, если строка* была удалена
*/ 
int deleteline(string_t *string);

/*
        Получение длины строки*
    Возвращает -1, если передан некорректный указатель на строку*
    Иначе возвращает длину строки
*/ 
int getlength(string_t *string);

/*
        Получение самой строки
    Возвращает NULL, если передан некорректные указатель на строку*
    Иначе возвращает саму строку ( она никак не связана со строкой* )
    
        НЕОБХОДИМО ОЧИЩАТЬ ПАМЯТЬ ПОСЛЕ ИСПОЛЬЗОВАНИЯ ФУНКЦИИ
*/ 
char* getstring(string_t *string);

/*
        Положить в строку* текстовую константу
    Возвращает -1, если передан некорректный указатель на строку*
    Возвращает -2, если не удалось создать подстроку строки*
    Возвращает 0, если всё прошло успешно
*/ 
int putline(string_t *string, const char * theLine);

/*
        Скопировать строки*
    Возвращает -1, если перодан некорректный указатель на string
    Возвращает -2, если передан некорректный указатель на theLine
    Возвращает -3, если не удалось создать подстроку строки string
    Возвращает 0, если всё прошло успешно
*/ 
int copystring(string_t *firstString, string_t *secondString);

/*
        Добавить в конец строки* текстовую константу
    Возвращает -1, если передан некорректный указатель на строку*
    Возвращает -2, если не удалось создать подстроку строки*
    Возвращает 0, если всё прошло успешно
*/ 
int addline(string_t *string, const char* theLine);

/*
        Добавить в конец строки* строку*
    Возвращает -1, если передан некорректный указатель на string
    Возвращает -2, если передан некорректный указатель на addongLine
    Возвращает -3, если не удалось создать подстроку string'а
    Возвращает 0, если всё прошло успешно
*/ 
int addstring(string_t *string, string_t *addingLine);

/*
        Добавляет символ в конец строки*
    Возвращает -1, если передан некорректный указатель на строку*
    Возвращает -2, если в качестве символа передан нуль символ 
    Возвращает -3, если не удалось создать подстроку строки*
    Возвращает 0, если всё прошло успешно
*/ 
int addchar(string_t *string, char c);

/*
        Сравнение строки* и текстовой константы
    Возвращает -1, если передан некорректный указатель на строку*
    Возвращает -2, если в строке* некорректный указатель на подстроку 
    Возвращает 1, если строки НЕ равны
    Возвращает 0, если строки равны
*/ 
int compareline(string_t *string, const char *line);

/*
        Сравнение строк*
    Возвращает -1, если передан некорректный указатель на string
    Возвращает -2, если в string некорректный указатель на подстроку 
    Возвращает -3, если передан некорректный указатель на compare
    Возвращает -4, если в compare некорректный указатель на подстроку 
    Возвращает 1, если строки* НЕ равны
    Возвращает 0, если строки* равны
*/ 
int comparestring(string_t *string, string_t *compare);

int clearstring(string_t *string);

/*
        Печатает строку*
*/ 
void printstring(string_t *string);


/*
        Получает строку из stdin
*/ 
void getcommand(string_t *line);

/*
        Читает 1 число с плавующей точкой из строки*
    Возвращает -1, если передан некорректный указатель на строку*
    Возвращает -2, длина строки равно нулю 
    Возвращает -3, если в строке не было ни одного числа
    Возвращает 1, если в строке содержится команда выхода
    Возвращает 0, если всё прошло успешно
*/ 
int readDouble(string_t *command, const char* exit, double *number);

/*
        Читает массив чисел с плавующей точкой из строки*
    Возвращает -1, если передан некорректный указатель на строку*
    Возвращает -2, длина строки равно нулю 
    Возвращает -3, если amount меньше либо равно нулю
    Возвращает -4, если количество чисел меньше чем amount
    Возвращает 2, если количество чисел больше чем amount
    Возвращает 1, если в строке содержится команда выхода
    Возвращает 0, если количество чисел равно amount
*/  
int readDoubles(string_t *command, const char* exit, double* numbers, int amount);