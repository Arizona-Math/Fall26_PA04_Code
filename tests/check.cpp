#include "linsys.h"
#include <cmath>
#include <iostream>

int main()
{
    const double original[] = {0, 2, 1,  1, 1, 0,  2, 0, 1};
    double a[9];
    for (int i = 0; i < 9; ++i)
        a[i] = original[i];
    int p[3];
    lu_factor(3, a, p);
    int failures = 0;
    bool permutation = true;
    for (int i = 0; i < 3; ++i) {
        if (p[i] < 0 || p[i] >= 3)
            permutation = false;
        for (int j = 0; j < i; ++j)
            if (p[i] == p[j])
                permutation = false;
    }
    if (!permutation) {
        std::cerr << "p must be a permutation of 0,1,2\n";
        return 1;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            double product = 0.0;
            for (int k = 0; k < 3; ++k) {
                double l = i == k ? 1.0 : (i > k ? a[i*3+k] : 0.0);
                double u = k <= j ? a[k*3+j] : 0.0;
                product += l * u;
            }
            if (!std::isfinite(product) ||
                std::abs(product - original[p[i]*3+j]) > 1e-12)
                ++failures;
        }
    }
    double b[] = {7, 3, 5}, c[] = {3, 2, 3}, x[3] = {};
    lu_solve(3, a, p, b, x);
    for (int i = 0; i < 3; ++i)
        if (!std::isfinite(x[i]) || std::abs(x[i] - (i+1)) > 1e-12)
            ++failures;
    lu_solve(3, a, p, c, x);
    for (int i = 0; i < 3; ++i)
        if (!std::isfinite(x[i]) || std::abs(x[i] - 1.0) > 1e-12)
            ++failures;

    std::cout << "Factorization and two solves: "
              << (failures == 0 ? "PASS" : "FAIL") << '\n';
    return failures == 0 ? 0 : 1;
}
