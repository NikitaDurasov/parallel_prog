double target_func(double x);
double integrate_trap_step(double a, double b, double (*fun)(double));
double integrate_trap(double a, double b, double (*fun)(double), int N);
double partition(double a, double b, int p);
void print_results(double results[], int p, double I_0);
double average(double arr[], int lenght);
