#include <stdlib.h>

double k(int seed)
{
	return 1.0
		- ((seed / 10) % 10) * 0.01
		- (seed % 10) * 0.005
		- 0.15;
}

int** create2DArray(int rows, int cols)
{
	int** array = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++)
		array[i] = (int*)malloc(cols * sizeof(int));
	return array;
}

int** createArray(int size)
{
	int* array = (int*)malloc(size * sizeof(int));
	return array;
}

int** createSymmetricMatrix(int** original, int vertices)
{
	int** matrix = create2DArray(vertices, vertices);
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			matrix[i][j] = matrix[j][i] = original[i][j];
		}
	}
	return matrix;
}

int** createMatrix(int vertices, int seed, double k)
{
	srand(seed);
	int** matrix = create2DArray(vertices, vertices);
	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < vertices; j++)
			matrix[i][j] = (double)k * ((double)rand() / (double)RAND_MAX * 2) > 1.0 ? 1 : 0;
    for ( int i = 0; i < 11; i++ )
        for ( int j = 0; j < 11; j++ )
            matrix[i][j] = round ( matrix[i][j] * ((double)rand() / (double)RAND_MAX * 2) * 100 );
    for ( int i = 0; i < 11; i++ ) {
        for ( int j = 0; j < 11; j++ ) {
            int first = matrix[i][j] != matrix[j][i];
            int second = matrix[i][j] == matrix[j][i] && matrix[i][j] == 1;
            if ( j > i ) second *= ( matrix[i][j] > 0 );
            matrix[i][j] *= first + second;
        }
    }
	return createSymmetricMatrix(matrix, vertices);
}


