// Нахождение определителя для матрицы matrix size-ого порядка
double findOpedelitel(double **matrix, int size);
// Нахождения ранга матрицы matrix (sizeY x sizeX)
int findRand(int **matrix, int sizeY, int sizeX);
// Нахождение произведение двух матриц
int** power(int **firstMatrix,int firstSizeY, int firstSizeX, int **secondMatrix,int secondSizeY, int secondSizeX);