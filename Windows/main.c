// ����������� ����������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
// ���������� � ���������� ����������
#include "matrix.h"
// ���������� ��� ������ � ��������
#include "input.h"

// ��������� ��� ������� ������
#define C_HELP "help"
#define C_DET "det"
#define C_POWER "pow"
#define C_RANG "rang"
#define C_EXIT "shutdown"
#define C_INVERSE "inverse"

// ������� ��� ������������� ����������
#define FC_EXIT "exit"

// ������� (���� ������������� ����������)
void helpShow(void);
int detStart(void);
int powerStart(void);
int rangStart(void);
int inverse(void);

// ���� �������
int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUSSIAN");
	// status - ����������� �����
	// space - ��� ����������� ����������� "~/"
	// command - ����� ������������
	int status = 1,
		space = 0;
	char* command = (char*)malloc(sizeof(char));
	// �������� �������������
	if (command == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}
	// �����������
	fprintf(stdout, "����������� ��� � Matrix\n");
	// ����
	do {
		// ~/
		fprintf(stdout, "~/ ");
		space = 0;
		// ���� �� ������������
		if (getCommand(command))
			space = 1;
		// ����������� �����
		// ������� ������ ����� ������
		if (space);
		// ������� ������ ������
		else if (strlen(command) == 0)
			fprintf(stdout, "\n");
		// ������� ������� ������
		else if (!strcmp(command, C_EXIT))
			status = 0;
		// ������� ������� ������
		else if (!strcmp(command, C_HELP))
			helpShow();
		// ������� ������� ���������� ������������
		else if (!strcmp(command, C_DET))
			detStart();
		// ������� ������� ���������� ������������ ������
		else if (!strcmp(command, C_POWER))
			powerStart();
		// ������� ������� ���������� ����� �������
		else if (!strcmp(command, C_RANG))
			rangStart();
		// ������� ������� ���������� �������� �������
		else if (!strcmp(command, C_INVERSE))
			inverse();
		// ������� ����������� �������
		else
			fprintf(stdout, "����������� ��������\n������� help, ����� ������� ������ ������\n");
	} while (status);
	// ���������� �� �������������
	fprintf(stdout, "������� �� ������������� ���������.\n");
	// ����������� ������
	free(command);
	// ��������� ���������
	return 0;
}


// ������� - ������
void helpShow(void) {
	fprintf(stdout, "������ ������: \n");
	fprintf(stdout, " -- %s\n", C_DET);
	fprintf(stdout, " -- %s\n", C_POWER);
	fprintf(stdout, " -- %s\n", C_RANG);
	fprintf(stdout, " -- %s\n", C_INVERSE);
	fprintf(stdout, " -- %s\n", C_EXIT);
}

// ������� - ���������� ������������
int detStart(void) {
	// amount - ������� �������
	// status - ���� ��� �����
	// matrix - ���� �������
	// data - ������ ����� ������������
	int amount = 0,
		status = 1;
	double** matrix;
	char* data = (char*)malloc(sizeof(char));
	// �������� �������������
	if (data == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}
	// ������ ���� �������
	do {
		// ������ ������ ���� �������
		fprintf(stdout, "������� ������� �������, ��� ���������� � ������������: ");
		// ������ ������
		getCommand(data);
		// ���� � ��� ��� ������� ������, �� ����������
		if (!strcmp(data, FC_EXIT))
			return 0;
		// ��������� �� ������������ ������� ������
		if (checkString(data, &amount))
			if (amount <= 0)
				fprintf(stdout, "������������ ������...\n");
			else
				status = 0;
		else
			fprintf(stdout, "����������� ������...\n");
	} while (status);

	// ������ ������ ��������� �������
	matrix = (double**)malloc(amount * sizeof(double*));
	// �������� �������������
	if (matrix == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}

	// ������ ������ ���� �������
	fprintf(stdout, "������� �������� �������:\n");
	// ������ �������
	// ���������� �� ���� �������
	for (int i = 0; i < amount; i++) {
		// ������ ������� ��� ������ ������
		matrix[i] = (double*)malloc(amount * sizeof(double));
		// �������� �������������
		if (matrix[i] == NULL) {
			fprintf(stdout, "��������� ������ ������������� ������\n");
			exit(-1);
		}
		// ��� ��������� �����
		fprintf(stdout, " ");
		// ������ ������
		int stat = getDetLine(data, matrix, i, amount);
		// ���� �� ������� ������� ������,
		if (stat == 2)
			return 0;
		// ��������� �� ������������
		else if (stat == 1 || stat == 3) {
			fprintf(stdout, "������������ ������...\n");
			i--;
		}
	}
	// ������� ������������ ������� � ������� ���
	fprintf(stdout, "������������ ������� �����: %.3lf\n", findDet(matrix, amount));
	// ����������� ������
	for (int i = 0; i < amount; i++)
		free(matrix[i]);
	free(matrix);
	free(data);
	// ��������� ������ ������������
	return 0;
}

// ������� - ������������ ������
int powerStart(void) {
	int fsizey = 0,
		fsizex = 0,
		ssizey = 0,
		ssizex = 0,
		status = 1;
	double** firstMatrix,
		** secondMatrix;
	char* data = (char*)malloc(sizeof(char));
	// �������� �������������
	if (data == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}

	do {
		fprintf(stdout, "������� ���������� ����� ������ �������: ");
		// ������ ������
		getCommand(data);
		// ���� � ��� ��� ������� ������, �� ����������
		if (!strcmp(data, FC_EXIT))
			return 0;
		// ��������� �� ������������ ������� ������
		checkString(data, &fsizey);

		if (fsizey > 0)
			status = 0;
		else
			fprintf(stdout, "������������ ������...\n");
	} while (status);

	status = 1;

	do {
		fprintf(stdout, "������� ���������� �������� ������ �������: ");
		// ������ ������
		getCommand(data);
		// ���� � ��� ��� ������� ������, �� ����������
		if (!strcmp(data, FC_EXIT))
			return 0;
		// ��������� �� ������������ ������� ������
		checkString(data, &fsizex);

		if (fsizex > 0)
			status = 0;
		else
			fprintf(stdout, "������������ ������...\n");
	} while (status);

	firstMatrix = (double**)malloc(fsizey * sizeof(double*));
	secondMatrix = (double**)malloc(ssizey * sizeof(double*));
	// �������� �������������
	if (firstMatrix == NULL || secondMatrix == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}

	for (int i = 0; i < fsizey; i++) {
		// ������ ������� ��� ������ ������
		firstMatrix[i] = (double*)malloc(fsizex * sizeof(double));
		// �������� �������������
		if (firstMatrix[i] == NULL) {
			fprintf(stdout, "��������� ������ ������������� ������\n");
			exit(-1);
		}
		// ��� ��������� �����
		printf(" ");
		// ������ ������
		int stat = getDetLine(data, firstMatrix, i, fsizex);
		// ���� �� ������� ������� ������,
		if (stat == 2)
			return 0;
		// ��������� �� ������������
		else if (stat == 1 || stat == 3) {
			fprintf(stdout, "������������ ������...\n");
			i--;
		}
	}

	// ������ �������

	status = 1;

	do {
		fprintf(stdout, "������� ���������� ����� ������ �������: ");
		// ������ ������
		getCommand(data);
		// ���� � ��� ��� ������� ������, �� ����������
		if (!strcmp(data, FC_EXIT))
			return 0;
		// ��������� �� ������������ ������� ������
		checkString(data, &ssizey);

		if (ssizey > 0)
			status = 0;
		else
			fprintf(stdout, "������������ ������...\n");
	} while (status);

	status = 1;

	do {
		fprintf(stdout, "������� ���������� �������� ������ �������: ");
		// ������ ������
		getCommand(data);
		// ���� � ��� ��� ������� ������, �� ����������
		if (!strcmp(data, FC_EXIT))
			return 0;
		// ��������� �� ������������ ������� ������
		checkString(data, &ssizex);

		if (ssizex > 0)
			status = 0;
		else
			fprintf(stdout, "������������ ������...\n");
	} while (status);

	fprintf(stdout, "������� �������� ������ �������:\n");

	for (int i = 0; i < ssizey; i++) {
		// ������ ������� ��� ������ ������
		secondMatrix[i] = (double*)malloc(ssizex * sizeof(double));
		if (secondMatrix[i] == NULL) {
			fprintf(stdout, "��������� ������ ������������� ������\n");
			exit(-1);
		}
		// ��� ��������� �����
		printf(" ");
		// ������ ������
		int stat = getDetLine(data, secondMatrix, i, ssizex);
		// ���� �� ������� ������� ������,
		if (stat == 2)
			return 0;
		// ��������� �� ������������
		else if (stat == 1 || stat == 3) {
			fprintf(stdout, "������������ ������...\n");
			i--;
		}
	}

	double** matrix = power(firstMatrix, fsizey, fsizex, secondMatrix, ssizey, ssizex);

	if (matrix) {
		fprintf(stdout, "��������� ������������:\n\n");
		for (int i = 0; i < fsizey; i++) {
			fprintf(stdout, "\t");
			for (int j = 0; j < ssizex; j++)
				fprintf(stdout, "%.3lf ", matrix[i][j]);
			fprintf(stdout, "\n");
		}
		fprintf(stdout, "\n");
	}

	for (int i = 0; i < fsizey; i++)
		free(firstMatrix[i]);
	free(firstMatrix);

	for (int i = 0; i < ssizey; i++)
		free(secondMatrix[i]);
	free(secondMatrix);

	free(data);
	return 0;
}
// ������� - ���� �������
int rangStart(void) {
	int amountY = 0,
		amountX = 0,
		status = 1;
	char* data = (char*)malloc(sizeof(char));
	double** matrix;
	if (data == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}

	do {
		fprintf(stdout, "������� ���������� ����� �������, ��� ���������� � �����: ");
		// ������ ������
		getCommand(data);
		// ���� � ��� ��� ������� ������, �� ����������
		if (!strcmp(data, FC_EXIT))
			return 0;
		// ��������� �� ������������ ������� ������
		if (checkString(data, &amountY))
			if (amountY > 0)
				status = 0;
			else
				fprintf(stdout, "������������ ������...\n");
		else
			fprintf(stdout, "������������ ������...\n");
	} while (status);

	status = 1;

	do {
		fprintf(stdout, "������� ���������� �������� �������, ��� ���������� � �����: ");
		// ������ ������
		getCommand(data);
		// ���� � ��� ��� ������� ������, �� ����������
		if (!strcmp(data, FC_EXIT))
			return 0;
		// ��������� �� ������������ ������� ������
		if (checkString(data, &amountX))
			if (amountX > 0)
				status = 0;
			else
				fprintf(stdout, "������������ ������...\n");
		else
			fprintf(stdout, "������������ ������...\n");
	} while (status);

	matrix = (double**)malloc(amountY * sizeof(double*));
	if (matrix == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}

	fprintf(stdout, "������� �������� �������:\n");
	for (int i = 0; i < amountY; i++) {
		// ������ ������� ��� ������ ������
		matrix[i] = (double*)malloc(amountX * sizeof(double));
		// �������� �������������
		if (matrix[i] == NULL) {
			fprintf(stdout, "��������� ������ ������������� ������\n");
			exit(-1);
		}
		// ��� ��������� �����
		fprintf(stdout, " ");
		// ������ ������
		int stat = getDetLine(data, matrix, i, amountX);
		// ���� �� ������� ������� ������,
		if (stat == 2)
			return 0;
		// ��������� �� ������������
		else if (stat == 1 || stat == 3) {
			fprintf(stdout, "������������ ������...\n");
			i--;
		}
	}

	int rang = findRang(matrix, amountY, amountX);
	fprintf(stdout, "���� ������� ����� %d\n", rang);

	for (int i = 0; i < amountY; i++)
		free(matrix[i]);
	free(matrix);
	free(data);
	return 0;
}

int inverse(void) {
	// amount - ������� �������
	// status - ���� ��� �����
	// matrix - ���� �������
	// data - ������ ����� ������������
	int amount = 0,
		status = 1;
	double det = 0.;
	double** matrix;
	char* data = (char*)malloc(sizeof(char));
	// �������� �������������
	if (data == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}
	// ������ ������� �������
	do {
		// ������ ������ ������� �������
		fprintf(stdout, "������� ������� �������, ��� ���������� �������� �� �������: ");
		// ������ ������
		getCommand(data);
		// ���� � ��� ��� ������� ������, �� ����������
		if (!strcmp(data, FC_EXIT))
			return 0;
		// ��������� �� ������������ ������� ������
		if (checkString(data, &amount)) {
			if (amount <= 1)
				fprintf(stdout, "������������ ������...\n");
			else
				status = 0;
		}
		else
			fprintf(stdout, "����������� ������...\n");
	} while (status);

	// ������ ������ ��������� �������
	matrix = (double**)malloc(amount * sizeof(double*));
	// �������� �������������
	if (matrix == NULL) {
		fprintf(stdout, "��������� ������ ������������� ������\n");
		exit(-1);
	}

	// ������ ������ ���� �������
	fprintf(stdout, "������� �������� �������:\n");
	// ������ �������
	// ���������� �� ���� �������
	for (int i = 0; i < amount; i++) {
		// ������ ������� ��� ������ ������
		matrix[i] = (double*)malloc(amount * sizeof(double));
		// �������� �������������
		if (matrix[i] == NULL) {
			fprintf(stdout, "��������� ������ ������������� ������\n");
			exit(-1);
		}
		// ��� ��������� �����
		printf(" ");
		// ������ ������
		int stat = getDetLine(data, matrix, i, amount);
		// ���� �� ������� ������� ������,
		if (stat == 2)
			return 0;
		// ��������� �� ������������
		else if (stat == 1 || stat == 3) {
			fprintf(stdout, "������������ ������...\n");
			i--;
		}
	}
	double** result = findInverse(matrix, amount, &det);
	if (det != 0.0) {
		if (result) {
			fprintf(stdout, "�������� �������:\n\n");
			for (int i = 0; i < amount; i++) {
				fprintf(stdout, "\t|   ");
				for (int j = 0; j < amount; j++)
					fprintf(stdout, "%7.3lf ", result[i][j]);
				fprintf(stdout, "\t|");
				if (i == amount / 2)
					fprintf(stdout, " * ( 1 / %4.3lf )\n", det);
				else
					fprintf(stdout, "\n");
			}
			fprintf(stdout, "\n");
		}
	}
	else
		fprintf(stdout, "��� ���� ������� �� ���������� ��������\n");

	for (int i = 0; i < amount; i++) {
		free(result[i]);
		free(matrix[i]);
	}
	free(result);
	free(matrix);

	free(data);

	return 0;
}