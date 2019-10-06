#define ZERO_EPSILON 1e-10

int solve_linear_equation(double a, double b, double *x);

int solve_square_equation(double a, double b, double c, double *x1, double *x2, int flag);

enum TypeRoots
{
    COMPLEX_ROOTS = -1,
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INFINITY_ROOTS = 1000,
};

enum Bool
{
    False,
    True,
};
