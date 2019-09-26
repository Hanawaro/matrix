// ���������� ����������� ���������
#include <stdio.h>
#include <stdlib.h>
//#include <locale.h>
// ����������� ������������ ������ matrix
#include "matrix.h"

// ���������� ������������ ������� matrix
// ���� ��������� -1 - �� ���-�� ����� �� ���
double findDet(double** matrix, int size) {
	// ��������� ������������ ������� �������
	if (size < 1)
		return -1;
	// ������� ������� ������������ ������� 1-��� �������
	else if (size == 1)
		return matrix[0][0];
	// ������� ������� ������������ ������� 2-��� �������
	else if (size == 2)
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	// ������� ������� ������������ ������� 3-��� �������
	else if (size == 3)
		return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][2] * matrix[1][0] * matrix[2][1] + matrix[0][1] * matrix[1][2] * matrix[2][0] -
		matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1];
	// ������� ��������� ������������ ������� n-��� �������
	else {
		// opredelitel - ���� �������� ������������
		// aI - ����� ������ ������
		// aJ - ����� ������� ������
		double opredelitel = 0;
		int aI = 0, aJ = 0;
		// ������ ������� �������� ������� ��� ������ 
		double** array = (double**)malloc((size - 1) * sizeof(double*));
		// ��������� ���� �� ������� ������ ��� ������ (�������)
		if (array == NULL)
			return -1;
		// ���������� ������� � ������� ������ ��� ������ ��������� ( i - ����� ������� )
		for (int i = 0; i < size - 1; i++) {
			// ��������� ������ ��������� ��� ������� �������� �������
			array[i] = (double*)malloc((size - 1) * sizeof(double));
			// ��������� ���� �� ������� ������ ��� ������ ��������� ������� (�������)
			if (array[i] == NULL)
				return -1;
			// ���������� ������ ( j - ����� ������)
			for (int j = 0; j < size - 1; j++)
				// �������� ��������
				array[i][j] = 0;
		}

		// �������� ����� ����

		// ���������� �������� ������ ������ ��������� ������� (91, 02, ..., 0i)
		// ����������� ������ ������
		for (int i = 0; i < size; i++) {
			// ���������� ������ ��������� ������� ( j - ����� ������ )
			for (int j = 1; j < size; j++) {
				// ���������� �������� ����� ��������� ������� �� �������� ( k - ����� ������� )
				for (int k = 0; k < size; k++) {
					// ����������� ������� �� ���������
					if (i != k) {
						// ���������, ����� �� ���� ������������
						if (aJ < size - 1 && aI < size - 1) {
							// ���������� jk-��� ������� � ������� �������� ������� aIaJ
							array[aI][aJ] = matrix[j][k];
							// ����������� ������� ��� ������� �������� ������� (������)
							aJ++;
						}
					}
				}
				// ����������� ������ ��� ������� �������� ������� (������)
				aI++;
				// �������� ������� ��� ������� �������� ������� (������)
				aJ = 0;
			}
			// ������������ �� ������ ������� ������� �������� ������� (������)
			aI = 0;
			aJ = 0;
			// (-1)^(i+0) * findDet(������)
			if (i % 2 == 0)
				opredelitel += matrix[0][i] * findDet(array, size - 1);
			else
				opredelitel -= matrix[0][i] * findDet(array, size - 1);
		}
		// ����������� ������
		for (int i = 0; i < size - 1; i++)
			free(array[i]);
		free(array);
		// ���������� ��������
		return opredelitel;
	}
	// ���-�� ����� �� ���
	return -1;
}

// ���������� ���� ������� matrix
// ���� ��������� -1 - �� ���-�� ����� �� ���
int findRang(double** matrix, int sizeY, int sizeX) {
	// �������, ���������� �� ������� ������
	if (sizeY <= 0 || sizeX <= 0)
		return -1;
	// ���� � ������� ����� ���� ������, ������� ���� �������
	else if (sizeY == 1) {
		// flag - ����������, ���������� �� ��� ���� 1 �� ����
		int flag = 1;
		for (int i = 0; i < sizeX; i++)
			if (matrix[sizeY - 1][i] != 0.0)
				flag = 0;
		// ���� ���� ���� ���� ����, �� ���� ����� 0
		if (flag)
			return 0;
		else
			// ����� ����� 1 
			return 1;
	}
	else {
		// ���� ������� �� � ����� �������, ��
		// iteration - ���������� �������� � ����� ������� 
		// newI - ������ ������, � ������� �������� ���� "���������" ������
		// lastLine - ������ ������, � ������� �� ��������
		// vertical - ������ �������, � ������� �� �������� �������� ���� � ������� ������
		int iteration = 1, newI = 0, lastLine = 1, vertical = 0;
		// ���������� �� ���� �������, � �������� �� ������ ��������
		for (int i = 0; i < sizeY - 1; i++) {
			// ������ ������ ���������� �������� � ������� �������
			for (int j = 1; j <= iteration; j++) {
				// ���������� �� ��� ����� �������� ������� ������ (forSecond) �
				// �� ��� ����� �������� ������, ������� �������� � ����� ������� ������� (forFirst)
				double forFirst = matrix[lastLine][vertical],
					forSecond = matrix[newI][vertical];
				// �������� ��� 2 ������ ���� �� ����� � ���������� ��������� � ������� ������
				for (int k = 0; k < sizeX; k++)
					matrix[lastLine][k] = matrix[newI][k] * forFirst - matrix[lastLine][k] * forSecond;
				// ����������� ������ ������� (�� ����������)
				vertical++;
				// ����������� ������ ������, ������� �������� � ����� ������� �������
				newI++;
			}
			// ����������� ������ ������� ������
			lastLine++;
			// ����������� ���������� �������� � ������� �������
			iteration++;
			// �������� ������� �������,� ������� �� �������� ����, � ������, ������� �������� � ������� �������
			vertical = 0;
			newI = 0;
		}
		// �������, ������� ����� � ������
		// flag - ����������, ���������� �� ��� ���� 1 �� ����
		// counter - ������� ���������� ������� �����
		int flag = 1, counter = 0;
		// ���������� �� ������� �������
		for (int i = 0; i < sizeY; i++) {
			// ���������� �� �������� �������
			for (int k = 0; k < sizeX; k++) {
				// ���� ���� �� ����, �� ������� ����
				if (matrix[i][k] != 0.0)
					flag = 0;
			}
			// ���� ������� ������
			if (flag)
				// ��������� �������
				counter++;
			// ����� ��������� ����, ��� ��������� ������
			flag = 1;
		}
		// ���������� ���� �������
		return (sizeY - counter);
	}
	// ���-�� ����� �� ���
	return -1;
}

// ���������� ������� - ��������� ������������
// ���� ��������� 0 - �� ���-�� ����� �� ���
double** power(double** firstMatrix, int firstSizeY, int firstSizeX, double** secondMatrix, int secondSizeY, int secondSizeX) {
	// �������, ����� �� ������ ����� ������������ ���� ������
	if (firstSizeX == secondSizeY) {
		// ������ ����� �������
		double** matrix = (double**)malloc(firstSizeY * sizeof(double*));
		// ���������, ���� �� ������� ������ ��� ����� �������
		if (matrix == NULL)
			return 0;
		// ������ ������ ��������� �������
		for (int i = 0; i < firstSizeY; i++) {
			matrix[i] = (double*)malloc(secondSizeX * sizeof(double));
			// �������, ���� �� ������� ������ ��� ������ ��������� �������
			if (matrix[i] == NULL)
				return 0;
		}
		// �������� �������
		for (int i = 0; i < firstSizeY; i++)
			for (int j = 0; j < secondSizeX; j++)
				matrix[i][j] = 0.0;
		// ���������� �� ������� ������ �������
		for (int i = 0; i < firstSizeY; i++)
			// ���������� �� �������� ������
			for (int j = 0; j < firstSizeX; j++) {
				// �������� [i][j] ������� 1 �������
				double tmp = firstMatrix[i][j];
				// ���������� �� ������ �������
				for (int k = 0; k < secondSizeX; k++)
					matrix[i][k] += tmp * secondMatrix[j][k];
			}
		// ���������� ��������� �� ����� �������
		return matrix;
	}
	else {
		// ���������� 0
		return 0;
	}
	// ���������� 0
	return 0;
}
// ���������� �������� �������
double** findInverse(double** matrix, int amount, double* det) {
	//setlocale(LC_ALL, "RUSSIAN");
	// tmpI - ������ ������
	// tmpJ - ������� ������
	// status - ��� ������, ����� �������� ������ �� ��������� ������
	// tmp - �����
	// result - �������� �������
	int tmpI = 0,
		tmpJ = 0,
		status = 0;
	double** tmp = (double**)malloc((amount - 1) * sizeof(double*));
	double** result = (double**)malloc(amount * sizeof(double*));
	if (tmp == NULL || result == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}
	// ��������� ������ ��������� ��� �������� �������
	for (int i = 0; i < amount; i++) {
		result[i] = (double*)malloc(amount * sizeof(double));
		if (result[i] == NULL) {
			fprintf(stdout, "��������� ������ ������������� ������\n");
			exit(-1);
		}
	}
	// ��������� ������ ��������� ��� ������
	for (int i = 0; i < (amount - 1); i++) {
		tmp[i] = (double*)malloc((amount - 1) * sizeof(double));
		if (tmp[i] == NULL) {
			fprintf(stdout, "��������� ������ ������������� ������\n");
			exit(-1);
		}
	}
	// ������������ �������
	*det = findDet(matrix, amount);
	// ���� ����������� ����� ����, �� �������� �� ����������
	if (*det == 0.0)
		return NULL;
	// ������� ��������
	else {
		for (int i = 0; i < amount; i++) {
			for (int j = 0; j < amount; j++) {
				for (int k = 0; k < amount; k++) {
					for (int l = 0; l < amount; l++) {
						if (i != k && j != l) {
							// ���������� �����
							tmp[tmpI][tmpJ] = matrix[k][l];
							// ����������� �������
							tmpJ++;
							status = 1;
						}
					}
					// ����������� ������, �������� �������
					if (status) {
						tmpJ = 0;
						tmpI++;
						status = 0;
					}
				}
				// ������������ � (0, 0) ������
				tmpI = 0;
				tmpJ = 0;
				// ������� �������������� ����������
				if ((i + j) % 2 == 0)
					result[j][i] = findDet(tmp, amount - 1);
				else
					result[j][i] = -findDet(tmp, amount - 1);
			}
		}
	}
	// ����������� ������ � ���������� ���������
	for (int i = 0; i < (amount - 1); i++)
		free(tmp[i]);
	free(tmp);
	return result;
}