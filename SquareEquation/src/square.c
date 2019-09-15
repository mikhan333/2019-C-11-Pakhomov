/**
 * @file square.c
 * @author Pakhomov Mikhail
 * @brief Functions of solving square equations
 * @version 0.1
 * @date 2019-09-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "square.h"

/**
 * @brief Solve equation a * x + b = 0
 * 
 * @param a First parameter
 * @param b Second parameter
 * @param x Pointer to a place with the root
 * @return int Number of roots
 */
int solve_linear_equation(double a, double b, double *x)
{
    assert(!isnan(a) && !isnan(b));
    assert(x != NULL);

    if (a == 0)
    {
        if (b == 0)
            return NROOTS_INFINITY;
        else // if (b != 0)
            return 0;
    }
    else // if (a != 0)
    {
        *x = -b / a;
        return 1;
    }
}

/**
 * @brief Solve equation a * x ^ 2 + b * x + c = 0
 * 
 * @param a First parameter
 * @param b Second parameter
 * @param c Third parameter
 * @param x1 Pointer to a place with the first root
 * @param x2 Pointer to a place with the second root
 * @param flag Flag indicating whether to calculate complex roots
 * @return int Number of roots
 */
int solve_square_equation(double a, double b, double c, double *x1, double *x2, int flag)
{
    assert(!isnan(a) && !isnan(b) && !isnan(c));
    assert(x1 != NULL && x2 != NULL);
    assert(x1 != x2);

    if (a == 0) 
    {
        return solve_linear_equation(b, c, x1);
    }
    else // if (a != 0)
    {
        if (c == 0) 
        {
            *x1 = 0;
            if (b == 0)
                return 1;
            else
                return 1 + solve_linear_equation(a, b, x2); // a != 0, b != 0
        }
        else // if (c != 0)
        {
            double D = b * b - 4 * a * c;
            if (D < -ZERO_EPSILON)
            {
                if (flag)
                {
                    double sqrt_D = sqrt(-D);
                    double denominator = 2 * a;
                    *x1 = -b / denominator;
                    *x2 = sqrt_D / denominator;
                    return -2; 
                }
                else // if (!flag)
                {
                    return 0;
                }
                
            }
            else if (fabs(D) <= ZERO_EPSILON)
            {
                *x1 = -b / 2 * a;
                return 1;
            }
            else // if (D > 0)
            {
                double sqrt_D = sqrt(D);
                double denominator = 2 * a;
                *x1 = (-b + sqrt_D) / denominator;
                *x2 = (-b - sqrt_D) / denominator;
                return 2; 
            }
        }
    }
}