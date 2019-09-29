#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

typedef struct line {
    char * data;
    int length;
} string_t;


string_t* createline() {
    string_t *string = (string_t *) malloc(sizeof(string_t));
    if (string) {
        string->length = 1;
        string->data=(char *) malloc(sizeof(char));
        if (string->data)   
            string->data[0] = '\0';
        else
            return NULL;
        return string;
    } else
        return NULL;
}

int deleteline(string_t *string) {
    if (string != NULL) {
        free(string->data);
        free(string);
    }
    return 0;
}

int getlength(string_t *string) {
    if (string != NULL)
        return string->length;
    else
        return -1;
}

char* getstring(string_t *string) {
    if (string == NULL)
        return NULL;
    char* line = (char *) malloc(string->length * sizeof(char));
    if (line == NULL)
        return NULL;
    for (int i = 0; i < string->length; i++)
        line[i] = string->data[i];
    return line;
}

int putline(string_t *string, const char *theLine) {
    if (string == NULL)
        return -1;
    clearstring(string);
    string->length = strlen(theLine);
    string->data = (char *) realloc(string->data, string->length * sizeof(char));
    if (string->data == NULL)
        return -2;
    for (int i = 0; i < string->length; i++)
        string->data[i] = theLine[i];
    return 0;
}

int copystring(string_t *firstString, string_t *secondString) {
    if (firstString == NULL)
        return -1;
    if (secondString == NULL)
        return -2;
    firstString->length = secondString->length;
    firstString->data = (char *) realloc(firstString->data, firstString->length * sizeof(char));
    if (firstString->data == NULL)
        return -3;
    for (int i = 0; i < firstString->length; i++)
        firstString->data[i] = secondString->data[i];
    return 0;
}

int addline(string_t *string, const char* theLine) {
    if (string == NULL)
        return -1;
    if (strlen(theLine) == 0)
        return 0;
    int tmp = string->length - 1;
    string->length += strlen(theLine);
    string->data = (char *) realloc(string->data, string->length * sizeof(char));
    if (string->data == NULL)
        return -2;
    for (int i = tmp; i < string->length; i++)
        string->data[i] = theLine[i - tmp];
    return 0;
}

int addstring(string_t *string, string_t *addingLine) {
    if (string == NULL)
        return -1;
    if (addingLine == NULL)
        return -2;
    if(getlength(addingLine) == 1)
        return 0;
    int tmp = string->length - 1;
    string->length += addingLine->length - 1;
    string->data = (char *) realloc(string->data, string->length * sizeof(char));
    if (string->data == NULL)
        return -3;
    for (int i = tmp; i < string->length; i++)
        string->data[i] = addingLine->data[i - tmp];
    return 0;
}

int addchar(string_t *string, char c) {
    if (string == NULL)
        return -1;
    if (c == '\0')
        return -2;
    if (string->length == 0) {
        string->data = (char *) realloc(string->data, (string->length + 2)* sizeof(char));
        if (string->data == NULL)
            return -3;
        string->data[string->length ] = c;
        string->data[string->length + 1] = '\0';
        string->length += 2;
    } else {
        string->data = (char *) realloc(string->data, (string->length + 1)* sizeof(char));
        if (string->data == NULL)
            return -3;
        string->data[string->length - 1] = c;
        string->data[string->length] = '\0';
        string->length++;
    }
    return 0;
}

int compareline(string_t *string, const char *line) {
    if (string == NULL)
        return -1;
    if (string->data == NULL)
        return -2;
    if (!strcmp(string->data, line))
        return 0;
    else
        return 1;
}

int comparestring(string_t *string, string_t *compare) {
    if (string == NULL)
        return -1;
    if (string->data == NULL)
        return -2;
    if (compare == NULL)
        return -1;
    if (compare->data == NULL)
        return -2;
    if (!strcmp(string->data, compare->data))
        return 0;
    else
        return 1;
}

int clearstring(string_t *string) {
    string->data = (char *) realloc(string->data, sizeof(char));
    string->data[0] = '\0';
    string->length = 0;
}

void printstring(string_t *string) {
    if (string != NULL)
        printf("%s | %d\n", string->data, string->length);
}

void getcommand(string_t *line) {
    char c;
    int statusInput = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        addchar(line, c);
        statusInput = 1;
    }
    if (c == '\n' && statusInput == 0)
        addchar(line, c);
}

double inverse(long long value, long long mantissa, long long power, int sign) {
    long long tmp = 0;
    power /= 10;
    while (value != 0) {
        tmp += value%10 * power;
        value /= 10;
        power /= 10;
    }
    return sign * (double) tmp / (double) mantissa;
}

int readDouble(string_t *command, const char* exit, double *number) {
    if (command == NULL)
        return -1;
    if (command->length == 0)
        return -2;
    if (!strcmp(command->data, exit)) {
        return 1;
    }
    int statusInput = 0,
        statusPoint = 0,
        statusSign = 1;
    long long mantissa = 1,
              value = 0,
              power = 1;

    for (int i = 0; i < command->length; i++) {
        if (command->data[i] == ' ' || command->data[i] == '\t')
            break;
        else if (command->data[i] >= '0' && command->data[i] <= '9') {
            if (statusPoint == 1)
                mantissa *= 10;
            value += (command->data[i] - '0') * power;
            power *= 10;
            statusInput = 1;
        } else if (command->data[i] == '.' || command->data[i] == ',')
            statusPoint = 1;
        else if (command->data[i] == '-' && statusInput == 0)
            statusSign = -1;
    }

    if (statusInput) {
        *number = inverse(value, mantissa, power, statusSign); 
        return 0;
    } else
        return -3;
}

int readDoubles(string_t *command, const char* exit,double* numbers, int amount) {
    if (command == NULL)
        return -1;
    if (command->length == 0)
        return -2;
    if (amount <= 0)
        return -3;
    if (!strcmp(command->data, exit)) {
        return 1;
    }
    int statusInput = 0,
        statusPoint = 0,
        statusSign = 1,
        counter = 0;
    long long mantissa = 1,
              value = 0,
              power = 1;
    for (int i = 0; i < command->length; i++) {
        if (command->data[i] == '-' && statusInput == 0)
            statusSign = -1;
        else if (command->data[i] >= '0' && command->data[i] <= '9') {
            if (statusPoint == 1)
                mantissa *= 10;
            value += (command->data[i] - '0') * power;
            power *= 10;
            statusInput = 1;
        } else if (command->data[i] == ' ' || command->data[i] == '\t') {
            if (statusInput && counter < amount) {
                numbers[counter] = inverse(value, mantissa, power, statusSign);
                counter++;
            }
            statusInput = statusPoint = 0;
            statusSign = 1;
            value = 0;
            power = mantissa = 1;
        } else if (command->data[i] == '.' || command->data[i] == ',')
            statusPoint = 1;
    }
    if (statusInput && counter < amount) {
        numbers[counter] = inverse(value, mantissa, power, statusSign);
        counter++;
    }
    if (counter < amount)
        return -4;
    else if (counter == amount)
        return 0;
    else 
        return 2;
}