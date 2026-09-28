#ifndef LINSYS_H
#define LINSYS_H

// Matrices are n-by-n, stored by rows: entry (i,j) is a[i*n+j].
// Assume n >= 1, valid arrays, and nonsingular systems. No allocation here.

// Supplied baseline: elimination WITHOUT pivoting. Overwrites a and b;
// on return b is the solution. Requires nonzero pivots during elimination.
void gauss_solve(int n, double* a, double* b);

// Overwrite a with packed L and U: L below the diagonal, U on and above it.
// L has an implicit unit diagonal. Use partial pivoting (largest absolute
// entry in the active column). Initialize p, then exchange its entries.
// Convention: (P*A)[i,j] = A[p[i],j], so P*A = L*U. p uses zero-based indices.
void lu_factor(int n, double* a, int* p);

// Solve L*x=b using the strict lower triangle of lu and unit diagonal.
// Preserve lu, and preserve b unless x is the same array as b (allowed).
void forward_substitution(int n, const double* lu, const double* b, double* x);

// Solve U*x=b using the upper triangle of lu (nonzero diagonal).
// Preserve lu, and preserve b unless x is the same array as b (allowed).
void back_substitution(int n, const double* lu, const double* b, double* x);

// Solve A*x=b using an existing factorization. First put P*b in x, then
// call the two triangular solves in place. b and x must be distinct arrays.
// Do not change lu, p, or b, and do not factor again.
void lu_solve(int n, const double* lu, const int* p, const double* b, double* x);

#endif
