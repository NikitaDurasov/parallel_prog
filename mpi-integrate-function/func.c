#include "func.h"
#include <stdio.h>

double target_func(double x) {
    return 4. * (1 / (1 + x*x));
}

double integrate_trap_step(double a, double b, double (*fun)(double)) {
    double y_a = fun(a), y_b = fun(b);
    double temp = ( y_a + y_b ) / 2 * ( b - a );
    return temp;
}

double integrate_trap(double a, double b, double (*fun)(double), int N) {
    double dx = ( b - a ) / N;
    double result = 0;

    for (int i = 0; i < N; i++) {
        result += integrate_trap_step(a + i * dx, a + (i + 1) * dx, fun);
    }
    return result;
}

double partition(double a, double b, int p) {
    double dx = ( b - a ) / p;
    return dx;
}

void print_results(double results[], int len, double I_0) {
    double sum = 0;
    for (int i = 0; i < len; i++) {
        printf("process number: %d - %f\n", i, results[i]);
        sum += results[i];
    }
    printf("sum of parts of integrals: %f\n", sum);
    printf("Sum calculated by 0 process: %f\n", I_0);
}
double average(double arr[], int lenght) {
    double sum = 0;
    for (int i = 0 ; i < lenght; i++) {
        sum += arr[i];
    }
    return sum / lenght;
}


    



