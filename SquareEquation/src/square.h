#define False 0
#define True 1
#define NROOTS_INFINITY 1000
//TODO: add another function to estimate zero of double
#define ZERO_EPSILON 1e-10

int solve_linear_equation(double a, double b, double *x);

//TODO: return struct instead double x1 and x2 - for adding imaginary and real part
int solve_square_equation(double a, double b, double c, double *x1, double *x2, int flag);

//FIXME: fix enum and add everywhere correct return values
enum TypeRoots {
    ONE_ROOT,
    TWO_ROOTS,
    INFINITY_ROOTS,
    COMPLEX_ROOTS,
    ZERO_ROOTS,
};
