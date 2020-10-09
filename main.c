#include <stdio.h>

int main() {
    printf("Enter x:\n");
    double x;
    scanf("%lf", &x);
    if (x >= 0 && x <= 8 || x >= 16){
        printf("x = %lf\n", x);
        printf("%lf", -3 * (x * x) / 5 + 9);
    }
    else if (x < -1){
        printf("x = %lf\n", x);
        printf("%lf", 15 * x - 2);
    }
    else {
        printf("x = %lf\n", x);
        printf("no value");
    }
    return 0;
}
