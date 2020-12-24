#include <stdio.h>

int main(){
    int n, index;
    printf("Enter n:\n");
    scanf("%d", &n);
    double array[n];
    double X, ceils, floors, result;
    printf("Enter X:\n");
    scanf("%lf", &X);
    printf("\nYour n:\n%d\nYour X:\n%lf\n\n", n, X);
    for (int i = 0; i < n; i++){
      ceils = 1;
      index = 1;
      floors = 1;
      if (i != 0){
        for(int j = 0; j < 2 * i; j++){
          ceils *= X;
        }
      }
      for (int j = 1; j <= 2 * i; j++){
        floors *= j;
        if (j <= i){
          index *= -1;
        }
      }
      array[i] = index * ceils / floors;
    }
    printf("Your array:\n");
    for(int i = 0; i < n; i++){
      printf("%lf ", array[i]);
    }
    return 0;
}
