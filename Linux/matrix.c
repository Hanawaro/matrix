#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int findDet(double **matrix, int size, double *result) {
	if (matrix == NULL)
		return -1;
	if (size < 1) 
		return -2;
	if (result == NULL)
		return -3;
	if (size == 1) {
		*result = matrix[0][0];
		return 0;
	} else if (size == 2) {
		*result = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
		return 0;
	} else if ( size == 3 ) {
		for (int i = 0; i < size; i++)
			if (matrix[i] == NULL)
				return -1;
		*result = matrix[0][0]*matrix[1][1]*matrix[2][2] + matrix[0][2]*matrix[1][0]*matrix[2][1] + matrix[0][1]*matrix[1][2]*matrix[2][0] -
			matrix[0][2]*matrix[1][1]*matrix[2][0] - matrix[0][1]*matrix[1][0]*matrix[2][2] - matrix[0][0]*matrix[1][2]*matrix[2][1];
		return 0;
	} else {
		for (int i = 0; i < size; i++)
			if (matrix[i] == NULL)
				return -1;
		double opredelitel = 0; 
		int aI = 0, aJ = 0;
		double **array = (double**)malloc( (size - 1) * sizeof(double*));
		if (array == NULL)
			return -4;
		for (int i = 0; i < size - 1; i++) {
			array[i] = (double*)malloc((size - 1) * sizeof(double));
			if ( array[i] == NULL )
				return -4;
			for (int j = 0; j < size - 1; j++)
				array[i][j] = 0;
		}

		for (int i = 0; i < size; i++) {
			for (int j = 1; j < size; j++) {
				for (int k = 0; k < size; k++) {
					if (i != k) {
						if (aJ < size-1 && aI < size-1) {
							array[aI][aJ] = matrix[j][k];
							aJ++;
						}
					}
				}
				aI++;
				aJ = 0;
			}
			aI = 0;
			aJ = 0;
			double det;
			findDet(array, size - 1, &det);
			if ( i % 2 == 0 )
				*result += matrix[0][i] * det;
			else 
				*result -= matrix[0][i] * det;
		}
		for (int i = 0; i < size - 1; i++)
			free(array[i]);
		free(array);
		return 0;
	}
	return -5;
}

int findRang(double **matrix, int sizeY, int sizeX, int *rang) {
	if (matrix == NULL)
		return -1;
    if (sizeY <= 0 || sizeX <= 0)
		return -2;
	else if (sizeY == 1) {
		for (int i = 0; i < sizeY; i++)
			if (matrix[i] == NULL)
				return -1;
        int flag = 1;
        for ( int i = 0; i < sizeX; i++)
            if ( matrix[sizeY - 1][i] != 0.0)
                flag = 0;
		if (flag) {
			*rang = 0;
			return 0;
		} else {
			*rang = 1;
			return 0;
		}
	} else {
        int iteration = 1, newI = 0, lastLine = 1, vertical = 0;
		for (int i = 0; i < sizeY - 1; i++) {
			for (int j = 1; j <= iteration; j++) {
                double forFirst = matrix[lastLine][vertical],
                       forSecond = matrix[newI][vertical];
                for (int k = 0; k < sizeX; k++)
                    matrix[lastLine][k] = matrix[newI][k]*forFirst - matrix[lastLine][k]*forSecond; 
                vertical++;
                newI++;
			}
            lastLine++;
            iteration++;
            vertical = 0;
            newI = 0;
		}

        int flag = 1, counter = 0;
        for ( int i = 0; i < sizeY; i++) {
            for ( int k = 0; k < sizeX; k++) {
                if ( matrix[i][k] != 0.0 )
                    flag = 0;
            }
            if (flag) 
                counter++;
            flag = 1;
        }
		*rang = sizeY - counter;
        return 0;
	}
	return -3;
}

int power(double **firstMatrix,int firstSizeY, int firstSizeX, double **secondMatrix,int secondSizeY, int secondSizeX, double ***result) {
	if (firstMatrix == NULL || secondMatrix == NULL)
		return -1;
	if ( firstSizeX == secondSizeY && firstSizeY > 0 && firstSizeX > 0 && secondSizeY > 0 && secondSizeX > 0) {
		for (int i = 0; i < firstSizeY; i++)
			if (firstMatrix[i] == NULL)
				return -1;
		for (int i = 0; i < secondSizeY; i++)
			if (secondMatrix[i] == NULL)
				return -1;
		*result = (double **) malloc(firstSizeY * sizeof(double*));
		if (*result == NULL)
			return -3;
		for (int i = 0; i < firstSizeY; i++) {
			(*result)[i] = (double *) malloc( secondSizeX * sizeof(double));
			if ((*result)[i] == NULL)
				return -3;
		}
		for (int i = 0; i < firstSizeY; i++)
			for (int j = 0; j < secondSizeX; j++)
				(*result)[i][j] = 0.;
		
		for (int i = 0; i < firstSizeY; i++) 
			for (int j = 0; j < firstSizeX; j++) {
				double tmp = firstMatrix[i][j];
				for (int k = 0; k < secondSizeX; k++) 
					(*result)[i][k] += tmp * secondMatrix[j][k];
			}
		return 0;
	} else 
		return -2;
	return -4;
}

int findInverse(double **matrix, int amount, double *det, double ***result) {
	if (amount <= 1)
		return -1;
	int tmpI = 0,
		tmpJ = 0,
		status = 0;
	double **tmp = (double **) malloc((amount-1)*sizeof(double *));
	*result = (double **) malloc(amount*sizeof(double *));
	if (tmp == NULL || result == NULL)
        return -2;
	for (int i = 0; i < amount; i++) {
		(*result)[i] = (double *) malloc(amount*sizeof(double));
		if ((*result)[i] == NULL)
        	return -2;
	}
	for (int i = 0; i < (amount - 1); i++) {
		tmp[i] = (double *) malloc((amount-1)*sizeof(double));
		if (tmp[i] == NULL)
        	return -2;
	}
	int flag = findDet(matrix, amount, det);
	if (flag == -3)
		return -2;
	else if (flag == -4)
		return -4;
	if (*det == 0.0)
		return -3;
	else {
		for (int i = 0; i < amount; i++) {
			for (int j = 0; j < amount; j++) {
				for (int k = 0; k < amount; k++) {
					for(int l = 0; l < amount; l++) {
						if ( i != k && j != l) {
							tmp[tmpI][tmpJ] = matrix[k][l];
							tmpJ++;
							status = 1;
						}
					}
					if (status) {
						tmpJ = 0;
						tmpI++;
						status = 0;
					}
				}
				tmpI = 0;
				tmpJ = 0;
				double detTMP;
				findDet(tmp, amount-1, &detTMP);
				if ((i+j)%2 == 0)
					(*result)[j][i] = detTMP;
				else
					(*result)[j][i] = -detTMP;
			}
		}
	}
	for (int i = 0; i < (amount - 1); i++)
		free(tmp[i]);
	free(tmp);
	return 0;
}