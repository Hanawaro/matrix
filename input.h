// Получить строку string от пользователя
int getCommand(char *string);
// Получить данные для i-ой строки матрицы matrix
int getOpredelitelLine(char * line, double **matrix, int i, int amountOfElements);
// Получить число number из строки пользователя
int checkString(char *string, int *number);
// Получить число (double) number из строки пользователя
int checkStringDouble(char *string, double *number);
// Очистить буфер
void clearBufer(void);