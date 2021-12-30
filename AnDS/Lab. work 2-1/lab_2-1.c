#include <stdio.h>
#include <math.h>

// Function 1
float f1(int number, float x){
    float const_calc(int n){
        return (2 * n - 1) * (2 * n - 1) * x * x / ((4 * n * n + 2 * n));
    }
    float fact_const(int n){
        if (n <= 0){
            return 1;
        } else {
            return const_calc(n) * fact_const(n - 1);
        }
    }
    if (number <= 0){
        return 0;
    }
    return x * fact_const(number - 1) + f1(number - 1, x);
}

// Function 2
float f2(int number, float x){
    float const_calc(int n){
        return (2 * n - 1) * (2 * n - 1) * x * x / ((4 * n * n + 2 * n));
    }
    float fact_const(int n){
        if (n <= 0){
            return 1;
        } else {
            return const_calc(n) * fact_const(n - 1);
        }
    }

    float result = 0;

    void calculate_result(int n){
        if (n >= 1){
            result += x * fact_const(n - 1);
            calculate_result(n - 1);
        }
    }
    calculate_result(number);
    return result;
}

// Function 3
float f3(int number, float x){
    float const_calc(int n){
        return (2 * n - 1) * (2 * n - 1) * x * x / ((4 * n * n + 2 * n));
    }
    float fact_const(int n){
        if (n <= 0){
            return 1;
        } else {
            return const_calc(n) * fact_const(n - 1);
        }
    }
    if (number <= 0){
       return 0;
    }

    float elem = x;
    void calculate_elem(int n){
        if (n >= 1){
            elem *= const_calc(n);
            calculate_elem(n - 1);
        }
    }

    calculate_elem(number - 1);
    /*
        But easier float elem = x * fact_const(number - 1);
        The calculate_elem function is designed to show that elements can be found with a recursive descent
    */
   
   return elem + f3(number - 1, x);
}

int main(void){
    int n;
    float x;
    
    /*
    for input from the console

    scanf("%d %f", &n, &x);
    printf("%f\n", f1(n, x));
    printf("%f\n", f2(n, x));
    printf("%f\n", f3(n, x));
    */

    printf("Tests for x = 0.9:\n\n");

    printf("Amount for 1 number:\n");
    printf("Function 1: %lf\n", f1(1, 0.9)); // 0.5
    printf("Function 2: %lf\n", f2(1, 0.9)); // 0.5
    printf("Function 3: %lf\n", f3(1, 0.9)); // 0.5

    printf("\nAmount for 2 numbers:\n");
    printf("Function 1: %lf\n", f1(2, 0.9)); // 1.0215
    printf("Function 2: %lf\n", f2(2, 0.9)); // 1.0215
    printf("Function 3: %lf\n", f3(2, 0.9)); // 1.0215

    printf("\nAmount for 3 numbers:\n");
    printf("Function 1: %lf\n", f1(3, 0.9)); // 1.065787
    printf("Function 2: %lf\n", f2(3, 0.9)); // 1.065787
    printf("Function 3: %lf\n", f3(3, 0.9)); // 1.065787

    printf("\nAmount for 4 numbers:\n");
    printf("Function 1: %lf\n", f1(4, 0.9)); // 1.087139
    printf("Function 2: %lf\n", f2(4, 0.9)); // 1.087139
    printf("Function 3: %lf\n", f3(4, 0.9)); // 1.087139

    printf("\nAmount for 5 numbers:\n");
    printf("Function 1: %lf\n", f1(5, 0.9)); // 1.09891
    printf("Function 2: %lf\n", f2(5, 0.9)); // 1.09891
    printf("Function 3: %lf\n", f3(5, 0.9)); // 1.09891

    printf("\nAmount for 6 numbers:\n");
    printf("Function 1: %lf\n", f1(6, 0.9)); // 1.10593
    printf("Function 2: %lf\n", f2(6, 0.9)); // 1.10593
    printf("Function 3: %lf\n", f3(6, 0.9)); // 1.10593

    printf("\nAmount for 7 numbers:\n");
    printf("Function 1: %lf\n", f1(7, 0.9)); // 1.110341
    printf("Function 2: %lf\n", f2(7, 0.9)); // 1.110341
    printf("Function 3: %lf\n", f3(7, 0.9)); // 1.110341

    printf("\nAmount for 8 numbers:\n");
    printf("Function 1: %lf\n", f1(8, 0.9)); // 1.113217
    printf("Function 2: %lf\n", f2(8, 0.9)); // 1.113217
    printf("Function 3: %lf\n", f3(8, 0.9)); // 1.113217

    printf("\nAmount for 9 numbers:\n");
    printf("Function 1: %lf\n", f1(9, 0.9)); // 1.115143
    printf("Function 2: %lf\n", f2(9, 0.9)); // 1.115143
    printf("Function 3: %lf\n", f3(9, 0.9)); // 1.115143

    printf("\nAmount for 10 numbers:\n");
    printf("Function 1: %lf\n", f1(10, 0.9)); // 1.116462
    printf("Function 2: %lf\n", f2(10, 0.9)); // 1.116462
    printf("Function 3: %lf\n", f3(10, 0.9)); // 1.116462

    printf("\nTests for -1 < x < 1:\n");
    printf("Result for x = -0.9: %lf\n", f1(5, -0.9));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.9));

    printf("Result for x = -0.8: %lf\n", f1(5, -0.8));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.8));

    printf("Result for x = -0.7: %lf\n", f1(5, -0.7));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.7));

    printf("Result for x = -0.6: %lf\n", f1(5, -0.6));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.6));
    
    printf("Result for x = -0.5: %lf\n", f1(5, -0.5));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.5));
    
    printf("Result for x = -0.4: %lf\n", f1(5, -0.4));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.4));
    
    printf("Result for x = -0.3: %lf\n", f1(5, -0.3));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.3));
    
    printf("Result for x = -0.2: %lf\n", f1(5, -0.2));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.2));
    
    printf("Result for x = -0.1: %lf\n", f1(5, -0.1));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(-0.1));
    
    printf("Result for x = 0: %lf\n", f1(5, 0));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0));
    
    printf("Result for x = 0.1: %lf\n", f1(5, 0.1));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.1));
    
    printf("Result for x = 0.2: %lf\n", f1(5, 0.2));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.2));
    
    printf("Result for x = 0.3: %lf\n", f1(5, 0.3));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.3));
    
    printf("Result for x = 0.4: %lf\n", f1(5, 0.4));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.4));
    
    printf("Result for x = 0.5: %lf\n", f1(5, 0.5));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.5));
    
    printf("Result for x = 0.6: %lf\n", f1(5, 0.6));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.6));
    
    printf("Result for x = 0.7: %lf\n", f1(5, 0.7));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.7));
    
    printf("Result for x = 0.8: %lf\n", f1(5, 0.8));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.8));
    
    printf("Result for x = 0.9: %lf\n", f1(5, 0.9));
    printf("Result for x = -0.9 with asin: %lf\n\n", asin(0.9));
    
    return 0;
}
