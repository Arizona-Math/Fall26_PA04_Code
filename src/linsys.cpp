#include "linsys.h"
#include <cmath>

void gauss_solve(int n, double* a, double* b)
{
    for (int k = 0; k < n - 1; ++k) {
        for (int i = k + 1; i < n; ++i) {
            double m = a[i*n+k] / a[k*n+k];
            a[i*n+k] = 0.0;
            for (int j = k + 1; j < n; ++j)
                a[i*n+j] -= m * a[k*n+j];
            b[i] -= m * b[k];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j)
            b[i] -= a[i*n+j] * b[j];
        b[i] /= a[i*n+i];
    }
}

void lu_factor(int n, double* a, int* p)
{
    for (int i = 0; i < n; ++i)
        p[i] = i;
    // TODO: select each pivot, exchange complete rows and p entries,
    // then store multipliers below the diagonal and update the trailing block.
    (void)a;  // Remove this placeholder when implementing the routine.
}

void forward_substitution(int n, const double* lu, const double* b, double* x)
{
    // TODO: traverse the rows in increasing order; L has unit diagonal.
    (void)n; (void)lu; (void)b; (void)x;
}

void back_substitution(int n, const double* lu, const double* b, double* x)
{
    // TODO: traverse the rows in decreasing order.
    (void)n; (void)lu; (void)b; (void)x;
}

void lu_solve(int n, const double* lu, const int* p, const double* b, double* x)
{
    // TODO: permute the right-hand side, then use the two triangular solves.
    (void)n; (void)lu; (void)p; (void)b; (void)x;
}
