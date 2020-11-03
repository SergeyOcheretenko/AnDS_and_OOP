#include <stdio.h>

int main() {
    printf("Enter x:\n");
    double x;
    scanf("%lf", &x);
    printf("x = %lf\n", x);
    if (x >= 0 && x <= 8 || x >= 16){
        printf("%lf", -3 * (x * x) / 5 + 9);
    }
    else if (x < -1){
        printf("%lf", 15 * x - 2);
    }
    else {
        printf("no value");
    }
    return 0;
}
