/**
 * @file first.c
 * @author Pakhomov Mikhail
 * @brief Program for solving the square equation
 * @version 0.1
 * @date 2019-09-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <math.h>
#include "square.h"

/**
 * @brief The main() - entry point
 *
 * Execution of the program
 * starts here.
 * 
 * @return int Program exit status
 */
int main()
{
    printf("-----------------------------------------------\n");
    printf("This is a program for solving a square equation\n"
           "Created by Mikhail Pakhomov\n\n");

    double a = NAN, b = NAN, c = NAN, x1, x2;
    int nInput = 0, nRoots = 0;
    char inputYesNo = 'n';
    while (True)
    {
        printf("Please enter the parametres for\n"
               "a * x ^ 2 + b * x + c = 0\n");
        x1 = 0, x2 = 0;
        nInput = scanf("%lf %lf %lf", &a, &b, &c);
        if (nInput < 3)
        {
            printf("Input values isn't correct");
            break;
        }
        printf("\n");

        nRoots = solve_square_equation(a, b, c, &x1, &x2, False);
        switch (nRoots)
        {
        case 0:
            printf("No roots\n");
            break;
        case 1:
            printf("One root: \n");
            printf("x1 = %lf\n", x1);
            break;
        case 2:
            printf("Two roots: \n");
            printf("x1 = %lf\nx2 = %lf\n", x1, x2);
            break;
        case -2:
            printf("Two complex roots: \n");
            printf("x1 = %lf + i * %lf\nx2 = %lf - i * %lf\n", x1, x2, x1, x2);
            break;
        case NROOTS_INFINITY:
            printf("Any number is root\n");
            break;
        default:
            printf("ERROR : main() : count of roots=%d\n", nRoots);
            break;
        }

        printf("Try again? (y / n) \n");
        scanf("%s", &inputYesNo);
        if (inputYesNo == 'n')
            break;
    }

    printf("-----------------------------------------------\n");
    return 0;
}
