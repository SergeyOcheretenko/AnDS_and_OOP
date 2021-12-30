#include <stdio.h>

int main(void) {
  int n, m;
  scanf("%d", &n);
  scanf("%d", &m);
  int A[n][m];
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      scanf("%d", &A[i][j]);
    }
  }
  printf("\nYour matrix:\n");
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
  for(int k = 0; k < n; k++){
    int step = 2, swap, flag = 0, count = step;
    while(step <= m){
      flag = 0;
      for(int i = count - step; i < count; i++){
        for(int j = i; j > count - step; j--){
          if (A[k][j] < A[k][j - 1]){
            swap = A[k][j];
            A[k][j] = A[k][j - 1];
            A[k][j - 1] = swap;
          }        
        }
        if(i == m - 1){
          step *= 2;
          count = step;
          flag = 1;
          break;
        }
      }
      if (flag == 0){
        count += step;
      }
    }
    if (step != m * 2){
      for(int i = 0; i < m; i++){
        for(int j = i; j > 0; j--){
          if (A[k][j] < A[k][j - 1]){
            swap = A[k][j];
            A[k][j] = A[k][j - 1];
            A[k][j - 1] = swap;
          }
        }
      }
    }
  }
  printf("\nSorted matrix:\n");
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }
}
