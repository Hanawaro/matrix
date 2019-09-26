// ���������� ����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ����������� ������������ ������ input
#include "input.h"
// ������� ������ �� ������������
#define C_EXIT "exit"

// �������� ������ string �� ������������
int getCommand(char* string) {
	int N = 0;
	while ((string[N] = getchar()) != EOF && string[N] != '\n' && string[N] != '\0') {
		N++;
		string = (char*)realloc(string, sizeof(char) * (N+1));
	}
	if (string[N] == '\n' && N == 0) {
		string[N] = '\0';
		return 1;
	}
	else {
		string[N] = '\0';
		return 0;
	}
}
// �������� ������ ��� i-�� ������ ������� matrix
int getDetLine(char* line, double** matrix, int i, int amountOfElements) {
	// N - ����� �������� ������� i-�� ������
	// powerF - ������ ����� �����, powerS - ������ ������� �����
	// firstPartOfNumber - ����� �����, secondPartOfNumber - ������� �����
	// counter - ����� �������� (�����)
	// j - ����� �������� (�������)
	// point - ����� � �����
	// sign - ���� �����
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
	// �������� ������ ������������
	getCommand(line);
	if (strlen(line) == 0)
		return 3;
	// ���������, ��� �� ������� ������
	if (!strcmp(line, C_EXIT))
		return 2;
	// �������� ����������
	while (line[N] != '\0') {
		// ���� ����� 0-9 � �� ���� ��� �����, �� ��������� � tmp �������� (�� �����)
		if (line[N] >= '0' && line[N] <= '9' && !point) {
			firstPartOfNumber += powerF * ((int)(line[N] - '0'));
			powerF *= 10;
			statusOfNumber = 1;
			// ���� ����� 0-9 � ����� ��� ����, �� ��������� � tmp �������� (����� �����) 
		}
		else if (line[N] >= '0' && line[N] <= '9' && point) {
			secondPartOfNumber += powerS * ((int)(line[N] - '0'));
			powerS *= 10;
			statusOfNumber = 1;
			// ���� �����, �� ��������� ����
		}
		else if (line[N] == '.') {
			point = 1;
			// ���� �����, �� ��������� ���������������
		}
		else if (line[N] == '-') {
			sign = -1;
			// ���� ������, �� ��������� ������� � �������
		}
		else if (line[N] == ' ' && statusOfNumber) {
			// �������������� ����� �� �����
			int tmp = firstPartOfNumber;
			powerF /= 10;
			firstPartOfNumber = 0;

			while (powerF != 0) {
				firstPartOfNumber += (tmp % 10) * powerF;
				tmp /= 10;
				powerF /= 10;
			}
			// �������������� ����� ����� �����
			tmp = secondPartOfNumber;
			powerF = powerS / 10;
			secondPartOfNumber = 0;

			while (powerF != 0) {
				secondPartOfNumber += (tmp % 10) * powerF;
				tmp /= 10;
				powerF /= 10;
			}
			// ����������
			if (j < amountOfElements)
				matrix[i][j] = sign * ((double)firstPartOfNumber + ((double)secondPartOfNumber / (double)powerS));
			j++;
			// �� ��������
			secondPartOfNumber = firstPartOfNumber = point = statusOfNumber = 0;
			sign = powerF = powerS = 1;
			// ����������� �������
			counter++;
		}
		// ������� ��������� ������
		N++;
	}
	// �������������� ����� �� �����
	int tmp = firstPartOfNumber;
	powerF /= 10;
	firstPartOfNumber = 0;

	while (powerF != 0) {
		firstPartOfNumber += (tmp % 10) * powerF;
		tmp /= 10;
		powerF /= 10;
	}
	// �������������� ����� ����� �����
	tmp = secondPartOfNumber;
	powerF = powerS / 10;
	secondPartOfNumber = 0;

	while (powerF != 0) {
		secondPartOfNumber += (tmp % 10) * powerF;
		tmp /= 10;
		powerF /= 10;
	}
	// ����������
	if (j <= amountOfElements)
		matrix[i][j] = sign * ((double)firstPartOfNumber + ((double)secondPartOfNumber / (double)powerS));
	counter++;
	// ��������� ������������ ������
	if (counter < amountOfElements)
		return 1;
	else
		return 0;
}

// �������� ����� number �� ������ ������������
int checkString(char* string, int* number) {
	// N - ��� ���� � ������ string
	// power - ������ �����
	// num - ���� �����
	// status - ����, �� ������������� ����� � ������
	// sign - ���� �����
	int N = 0,
		power = 1,
		num = 0,
		status = 0,
		sign = 1;
	// ��������� ������, ���� ��� ����� ������ (����� ����� ����, �.�. ������ �������� �� getCommand())
	while (string[N] != '\0') {
		// ���� ���� �����, �� ���������� � num
		if (string[N] >= '0' && string[N] <= '9') {
			num += power * ((int)(string[N] - '0'));
			power *= 10;
			status = 1;
			// �������� �����
		}
		else if (string[N] == '-')
			sign = -1;
		// ���� ������ ������ - �������
		else
			break;
		// ����������� ������ ����� ������
		N++;
	}
	// �������������� �����
	int tmp = num;
	power /= 10;
	num = 0;

	while (power != 0) {
		num += (tmp % 10) * power;
		tmp /= 10;
		power /= 10;
	}
	// ���� ����� ����������, �� �� ������
	if (status) {
		*number = sign * num;
		return 1;
	}
	else
		return 0;
}

// �������� ����� (double) number �� ������ ������������
int checkStringDouble(char* string, double* number) {
	// N - �������������� ������� � ������
	// powerF - ������ ����� �����, powerS - ������ ������� �����
	// firstPartaOfNumber - ����� �����, secondPartOfNumber - ������� �����
	// point - ���� �� �����
	// status - �������� �� �����
	// sign - ����
	int N = 0,
		powerF = 1,
		powerS = 1,
		point = 0,
		firstPartOfNumber = 0,
		secondPartOfNumber = 0,
		status = 0,
		sign = 1;
	// ������ ������ ������� ������
	while (string[N] != '\0') {
		// ���� ����� � ����� �����, �� ���������� � firstPartOfNumber
		if (string[N] >= '0' && string[N] <= '9' && !point) {
			firstPartOfNumber += powerF * ((int)(string[N] - '0'));
			powerF *= 10;
			status = 1;
			// ���� ����� � ����� �����, �� ���������� � firstPartOfNumber
		}
		else if (string[N] >= '0' && string[N] <= '9' && point) {
			secondPartOfNumber += powerS * ((int)(string[N] - '0'));
			powerS *= 10;
			// ���� �����, ��������� ����
		}
		else if (string[N] == '.')
			point = 1;
		// ���� ������������, ��������� ����
		else if (string[N] == '-')
			sign = -1;
		// ���������� ������ �������
		else
			break;
		// ����������� ������ ������� ������
		N++;
	}
	// �������������� ����� �����
	int tmp = firstPartOfNumber;
	powerF /= 10;
	firstPartOfNumber = 0;

	while (powerF != 0) {
		firstPartOfNumber += (tmp % 10) * powerF;
		tmp /= 10;
		powerF /= 10;
	}
	// �������������� ������� �����
	tmp = secondPartOfNumber;
	powerF = powerS / 10;
	secondPartOfNumber = 0;

	while (powerF != 0) {
		secondPartOfNumber += (tmp % 10) * powerF;
		tmp /= 10;
		powerF /= 10;
	}
	// ���� ����� ����������, �� �� ������
	if (status) {
		*number = sign * ((double)firstPartOfNumber + ((double)secondPartOfNumber / (double)powerS));
		return 1;
	}
	else
		return 0;
}
// �������� �����
void clearBufer(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF && c != '\0') {}
}