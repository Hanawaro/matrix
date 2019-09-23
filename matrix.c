// Подключаем стандартные библиотке
#include <stdio.h>
#include <stdlib.h>
// Подключение заголовочных файлов matrix
#include "matrix.h"

// Возвращает определитель матрицы matrix
// Если результат -1 - то что-то пошло не так
double findOpedelitel(double **matrix, int size) {
	// Проверяем корректность порядка матрицы
	if (size < 1) 
		return -1;
	// Считаем ручками определитель матрицы 1-ого порядка
	else if (size == 1) 
		return matrix[0][0];
	// Считаем ручками определитель матрицы 2-ого порядка
	else if (size == 2) 
		return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
	// Считаем ручками определитель матрицы 3-ого порядка
	else if ( size == 3 ) 
		return matrix[0][0]*matrix[1][1]*matrix[2][2] + matrix[0][2]*matrix[1][0]*matrix[2][1] + matrix[0][1]*matrix[1][2]*matrix[2][0] -
			matrix[0][2]*matrix[1][1]*matrix[2][0] - matrix[0][1]*matrix[1][0]*matrix[2][2] - matrix[0][0]*matrix[1][2]*matrix[2][1];
	// Считаем рекурсией определитель матрицы n-ого порядка
	else {
		// opredelitel - само значение определителя
		// aI - номер строки минора
		// aJ - номер столбца минора
		double opredelitel = 0; 
		int aI = 0, aJ = 0;
		// Создаём матрицу меньшего порядка для минора 
		double **array = (double**)malloc( (size - 1) * sizeof(double*));
		// Проверяем дала ли система память под массив (матрицу)
		if ( array == NULL )
			return -1;
		// Перебираем столбцы и находим миноры для первых элементов ( i - номер столбца )
		for (int i = 0; i < size - 1; i++) {
			// Добавляем второе измерение для матрицы меньшего порядка
			array[i] = (double*)malloc((size - 1) * sizeof(double));
			// Проверяем дала ли система память под второе измерение массива (матрицы)
			if ( array[i] == NULL )
				return -1;
			// Перебираем строки ( j - номре строки)
			for (int j = 0; j < size - 1; j++)
				// обнуляем элементы
				array[i][j] = 0;
		}

		// ОСНОВНАЯ ЧАСТЬ КОДА
		
		// Перебираем элементы первой строки начальной матрицы (91, 02, ..., 0i)
		// Вычёркиваем первую строку
		for (int i = 0; i < size; i++) {
			// Перебираем строки начальной матрицы ( j - номер строки )
			for (int j = 1; j < size; j++) {
				// Перебираем элементы строк начальной матрицы по столбцам ( k - номер столбца )
				for (int k = 0; k < size; k++) {
					// Вычёркиваем столбец по вертикали
					if (i != k) {
						// Проверяем, чтобы не было переполнения
						if (aJ < size-1 && aI < size-1) {
							// Записываем jk-тый элемент в матрицу меньшего порядка aIaJ
							array[aI][aJ] = matrix[j][k];
							// Увеличиваем столбец для матрицы меньшего порядка (минора)
							aJ++;
						}
					}
				}
				// Увеличиваем строку для матрицы меньшего порядка (минора)
				aI++;
				// Обнуляем столбец для матрицы меньшего порядка (минора)
				aJ = 0;
			}
			// Возвращаемся на первый элемент матрицы меньшего порядка (минора)
			aI = 0;
			aJ = 0;
			// (-1)^(i+0) * findOpredelitel(минора)
			if ( i % 2 == 0 )
				opredelitel += matrix[0][i] * findOpedelitel(array, size - 1);
			else 
				opredelitel -= matrix[0][i] * findOpedelitel(array, size - 1);
		}
		// Освобождаем память
		for (int i = 0; i < size - 1; i++)
			free(array[i]);
		free(array);
		// Возвращаем значение
		return opredelitel;
	}
	// Что-то пошло не так
	return -1;
}

// Возвращает ранг матрицы matrix
// Если результат -1 - то что-то пошло не так
int findRand(int **matrix, int sizeY, int sizeX) {
	// Смотрим, корректные ли входные данные
    if (sizeY < 1 || sizeX < 0)
		return -1;
	// Если в матрице всего одна строка, считаем ранг ручками
	else if (sizeY == 1) {
		// flag - показывает, встретился ли нам хоть 1 НЕ нуль
        int flag = 1;
        for ( int i = 0; i < sizeX; i++)
            if ( matrix[sizeY - 1][i] != 0)
                flag = 0;
		// Если были одни лишь нули, то ранг равен 0
		if ( flag )
			return 0;
		else 
			// Иначе равен 1 
			return 1;
	} else {
		// Если матрица не с одной строкой, то
		// iteration - количество операций с одной строкой 
		// newI - индекс строки, с коротой работает наша "последняя" строка
		// lastLine - индекс строки, с которой мы работаем
		// vertical - индекс столбца, в котором мы пытаемся получить нуль в рабочей строке
        int iteration = 1, newI = 0, lastLine = 1, vertical = 0;
		// Проходимся по всем строкам, с которыми мы должны работать
		for (int i = 0; i < sizeY - 1; i++) {
			// Делаем нужное количество операций с рабочей строкой
			for (int j = 1; j <= iteration; j++) {
				// Запоминаем на что нужно умножить рабочую строку (forSecond) и
				// на что нужно умножить строку, которая работает с нашей рабочей строкой (forFirst)
                int forFirst = matrix[lastLine][vertical],
                    forSecond = matrix[newI][vertical];
				// Вычитаем эти 2 строки друг из друга и записываем результат в рабочую строку
                for (int k = 0; k < sizeX; k++) 
                    matrix[lastLine][k] = matrix[newI][k]*forFirst - matrix[lastLine][k]*forSecond; 
				// Увеличиваем индекс столбца (по ступенькам)
                vertical++;
				// Увеличиваем индекс строки, которая работает с нашей рабочей строкой
                newI++;
            }
			// Увеличиваем индекс рабочей строки
            lastLine++;
			// Увеличиваем количество итераций с рабочей строкой
            iteration++;
			// Обнуляем индексы столбца,в котором мы получаем нуль, и строки, которая работает с рабочей строкой
            vertical = 0;
            newI = 0;
		}
		// Смотрим, сколько строк с нулями
		// flag - показывает, встретился ли нам хоть 1 НЕ нуль
		// counter - считает количество нулевых строк
        int flag = 1, counter = 0;
		// Проходимся по строкам матрицы
        for ( int i = 0; i < sizeY; i++) {
			// Проходимся по столбцам матрицы
            for ( int k = 0; k < sizeX; k++) {
				// Если есть НЕ нуль, то убираем флаг
                if ( matrix[i][k] != 0 )
                    flag = 0;
            }
			// Если нулевая строка
            if ( flag ) 
				// Обновляем счётчик
                counter++;
			// Снова поднимаем флаг, для следующей строки
            flag = 1;
        }
		// Возвращаем ранг матрицы
        return (sizeY - counter);
	}
	// Что-то пошло не так
	return -1;
}

// Возвращает матрицу - результат произведения
// Если результат 0 - то что-то пошло не так
int** power(int **firstMatrix,int firstSizeY, int firstSizeX, int **secondMatrix,int secondSizeY, int secondSizeX) {
	// Смотрим, можно ли вообще найти произведение этих матриц
	if ( firstSizeX == secondSizeY) {
		// Создаём новую матрицу
		int **matrix = (int **) malloc(firstSizeY * sizeof(int*));
		// Проверяем, дала ли система память под новую матрицу
		if (matrix == NULL)
			return 0;
		// Создаём второе измерение матрицы
		for (int i = 0; i < firstSizeY; i++) {
			matrix[i] = (int *) malloc( secondSizeX * sizeof(int));
			// Смотрим, дала ли система память под второе измерение матрицы
			if (matrix[i] == NULL)
				return 0;
		}
		// Обнуляем матрицу
		for (int i = 0; i < firstSizeY; i++)
			for (int j = 0; j < secondSizeX; j++)
				matrix[i][j] = 0;
		// Проходимся по строкам первой матрицы
		for (int i = 0; i < firstSizeY; i++) 
			// Проходимся по столбцам матриц
			for (int j = 0; j < firstSizeX; j++) {
				// Сохраням [i][j] элемент 1 матрицы
				int tmp = firstMatrix[i][j];
				// Проходимся по второй матрице
				for (int k = 0; k < secondSizeX; k++) 
					matrix[i][k] += tmp * secondMatrix[j][k];
			}
		// Возвращаем указатель на новую матрицу
		return matrix;
	} else {
		// Возвращаем 0
		return 0;
	}
	// Возвращаем 0
	return 0;
}