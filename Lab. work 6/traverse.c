#include <windows.h>
#include <conio.h>
#include "generate.h"
#include "draw.h"
#include "traverse.h"

int** dfs(HWND* hWnd, int* visited, int** matrix, int power)
{
	waitAndRedraw(hWnd);
	int** traverseTree = create2DArray(power, power);
	for (int i = 0; i < power; i++)
		for (int j = 0; j < power; j++)
			traverseTree[i][j] = 0;
     visited[0] = 1;

    int from, to, weight;
    for ( int p = 0; p < 10; p++ ) {
        from = -1;
        to = -1;
        weight = INT_MAX;
        for ( int i = 0; i < 11; i++ ) {
            if ( visited[i] )
                for ( int j = 0; j < 11; j++ ) {
                    if ( i != j && matrix[i][j] && !visited[j] && matrix[i][j] < weight ) {
                        from = i;
                        to = j;
                        weight = matrix[i][j];
                    }
                }
        }
        if ( from != -1 && to != -1 ) {
            waitAndRedraw(hWnd);
            traverseTree[from][to] = weight;
            traverseTree[to][from] = traverseTree[from][to];
            visited[to] = 1;
        }
    }
	return traverseTree;
}
