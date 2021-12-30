#include "generate.h"
#include "draw.h"
#include "algo.h"


int** getOrientedDegrees(int** matrix)
{
	int** degrees = create2DArray(n, 2);
	for (int i = 0; i < n; i++)
	{
		degrees[i][0] = 0; degrees[i][1] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j]) degrees[i][0]++;
			if (matrix[j][i]) degrees[i][1]++;
		}
	}

	return degrees;
}


int orientedRegularDegree(int** degrees)
{
	int degree = degrees[0];
	for (int i = 1; i < n; i++)
	{
		if (degree != degrees[i][0] || degree != degrees[i][1])
			return -1;
	}
	return degree;
}


int* getNonOrientedDegrees(int** matrix)
{
	int* degrees = createArray(n);
	for (int i = 0; i < n; i++)
		degrees[i] = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j])
			{
				degrees[i]++;
				if (i == j) degrees[i]++;
			}
		}
	}

	return degrees;
}

int nonOrientedRegularDegree(int* degrees)
{
	int degree = degrees[0];
	for (int i = 1; i < n; i++)
	{
		if (degree != degrees[i])
			return -1;
	}
	return degree;
}

int** getAllPath2(int** matrix, int* pathesAmount, int chainsOnly)
{
	int max_pathes = n * n * n;
	*pathesAmount = 0;
	int** distances1 = multiply(matrix, matrix, n);
	int** res = create2DArray(max_pathes, 3);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (distances1[i][j])
			{
				for (int k = 0; k < n; k++)
				{
					if (matrix[i][k] && matrix[k][j]
						&& (chainsOnly && !(i == k && k == j))
						)
					{
						res[*pathesAmount][0] = i;
						res[*pathesAmount][1] = k;
						res[*pathesAmount][2] = j;
						(*pathesAmount)++;
					}
				}
			}
		}
	}
	return res;
}

int** getAllPath3(int** matrix, int* pathesAmount, int chainsOnly)
{
	int max_pathes = n * n * n * n;
	*pathesAmount = 0;
	int** distances1 = multiply(matrix, matrix, n);
	int** distances2 = multiply(distances1, matrix, n);
	int** res = create2DArray(max_pathes, 4);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (distances2[i][j])
			{
				for (int k = 0; k < n; k++)
				{
					if (matrix[i][k] && distances1[k][j])
					{
						for (int p = 0; p < n; p++)
						{
							if (matrix[k][p] && matrix[p][j]
								&& (chainsOnly
									&& !(i == k && k == p)
									&& !(k == p && p == j)
									)
								)
							{
								res[*pathesAmount][0] = i;
								res[*pathesAmount][1] = k;
								res[*pathesAmount][2] = p;
								res[*pathesAmount][3] = j;
								(*pathesAmount)++;
							}
						}
					}
				}
			}
		}
	}
	return res;
}


int** getAccessibilityMatrix(int** matrix)
{
	int** accessMatrix = create2DArray(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			accessMatrix[i][j] = 0;
	for (int i = 0; i < n; i++)
		accessMatrix[i][i] = 1;
	int** currentPower = create2DArray(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			currentPower[i][j] = matrix[i][j];
	for (int p = 0; p < n - 1; p++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				accessMatrix[i][j] = accessMatrix[i][j] | currentPower[i][j];
			}
		}
		currentPower = multiply(currentPower, matrix, n);
	}
	return accessMatrix;
}

int** getStrongConnectionMatrix(int** matrix)
{
	int** transponed = transpone(matrix, n);
	int** res = create2DArray(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res[i][j] = matrix[i][j] && transponed[i][j];
	return res;
}

int** getComponents(int** strongConnectionMatrix, int* componentsAmount)
{
	int** components = create2DArray(n + 1, n + 1);
	for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < n + 1; j++)
			components[i][j] = -1;

	int* banned = createArray(n);
	int bannedAmount = 0;
	*componentsAmount = 0;
	int ix;
	while (bannedAmount < n)
	{
		int firstNotBanned = -1;
		int isBanned;
		for (int i = 0; i < n; i++)
		{
			isBanned = 0;
			for (int j = 0; j < bannedAmount; j++)
			{
				if (banned[j] == i)
				{
					isBanned = 1;
					break;
				}
			}
			if (!isBanned)
			{
				firstNotBanned = i;
				break;
			}
		}
		ix = 0;
		for (int i = 0; i < n; i++)
		{
			if (strongConnectionMatrix[firstNotBanned][i])
			{
				components[*componentsAmount][ix] = i;
				ix++;
				banned[bannedAmount] = i;
				bannedAmount++;
			}
		}
		(*componentsAmount)++;
	}
	return components;
}

int** condense(int** strongConnectionComponents, int componentsAmount, int** accessMatrix)
{
	int** condensedMatrix = create2DArray(componentsAmount, componentsAmount);
	for (int i = 0; i < componentsAmount; i++)
		for (int j = 0; j < componentsAmount; j++)
			if (i == j) condensedMatrix[i][j] = 1;
			else condensedMatrix[i][j] = 0;


	int* colors = createArray(n);
	int ix;
	for (int i = 0; i < componentsAmount; i++)
	{
		ix = 0;
		for (int j = 0; ix != -1; j++)
		{
			ix = strongConnectionComponents[i][j];
			if (ix != -1)
				colors[ix] = i;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (accessMatrix[i][j] && colors[i] != colors[j])
				condensedMatrix[colors[i]][colors[j]] = 1;
	return condensedMatrix;
}


int** multiply(int** m1, int** m2)
{
	int** res = create2DArray(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			res[i][j] = 0;
			for (int k = 0; k < n; k++)
				res[i][j] = res[i][j] || m1[i][k] && m2[k][j];
		}
	return res;
}

int** transpone(int** m)
{
	int** res = create2DArray(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res[i][j] = m[j][i];
	return res;
}
