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
        ceils *= (i + cos((double) i));
        floors = pow(4, i) - i;
        result += ceils / floors;
        counter += i + 5;
    }
    printf("Result:\n%lf\n", result);
    printf("Counter: %d", counter);
    return 0;
}
