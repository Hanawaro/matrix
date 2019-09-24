// Нахождение определителя для матрицы matrix size-ого порядка
double findOpedelitel(double **matrix, int size);
// Нахождения ранга матрицы matrix (sizeY x sizeX)
int findRang(double **matrix, int sizeY, int sizeX);
// Нахождение произведение двух матриц
double** power(double **firstMatrix,int firstSizeY, int firstSizeX, double **secondMatrix,int secondSizeY, int secondSizeX);