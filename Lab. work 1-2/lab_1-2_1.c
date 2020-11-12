#include <stdio.h>
#include <math.h>

int main(){
    printf("Enter n:\n");
    int n;
    int counter = 0;
    double ceils = 1, floors, result = 0;
    scanf("%d", &n);
    printf("Your n:\n%d\n", n);
    for (int i = 1; i <= n; i += 1){
        for (int j = 1; j <= i; j += 1){
            ceils *= (j + cos((double) j));
            counter += 3;
        }
        floors = pow(4, i) - i;
        result += ceils / floors;
        ceils = 1;
        counter += i + 2;
    }
    printf("Result:\n%lf\n", result);
    printf("Counter: %d", counter);
    return 0;
}
