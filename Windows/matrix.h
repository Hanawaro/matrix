// ���������� ������������ ��� ������� matrix size-��� �������
double findDet(double** matrix, int size);
// ���������� ����� ������� matrix (sizeY x sizeX)
int findRang(double** matrix, int sizeY, int sizeX);
// ���������� ������������ ���� ������
double** power(double** firstMatrix, int firstSizeY, int firstSizeX, double** secondMatrix, int secondSizeY, int secondSizeX);
// ���������� �������� �������
double** findInverse(double** matrix, int amount, double* det);
// �������� �������
double** invrs(double** matrix, int amount);