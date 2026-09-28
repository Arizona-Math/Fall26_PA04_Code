#include "linsys.h"
#include <iostream>

int main()
{
    // The two-row-exchange example in PA04 Written.
    double a[] = {0, 2, 1,  1, 1, 0,  2, 0, 1};
    double b[] = {7, 3, 5};
    double c[] = {3, 2, 3};
    double x[3] = {};
    int p[3];

    lu_factor(3, a, p);
    lu_solve(3, a, p, b, x);
    std::cout << "First solution (expected 1 2 3): ";
    for (int i = 0; i < 3; ++i)
        std::cout << x[i] << ' ';
    std::cout << '\n';

    lu_solve(3, a, p, c, x);  // Reuse the same factors.
    std::cout << "Second solution (expected 1 1 1): ";
    for (int i = 0; i < 3; ++i)
        std::cout << x[i] << ' ';
    std::cout << '\n';
}
