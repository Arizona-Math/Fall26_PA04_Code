# Math 589A — PA04 Code: a small linear-systems library

Implement Gaussian elimination with partial pivoting as an LU factorization,
then reuse the factors to solve linear systems. This is our introduction to
implementing numerical kernels in C++: ordinary loops, contiguous storage,
and a small library built with Make. Python remains useful for analysis and
verification; NumPy's efficient linear algebra also runs in compiled libraries.

The companion **PA04 Written** assignment uses Numbook Chapter 4 and
[AARG](https://marekrychlik.com/cgi-bin/gauss.cgi) to examine the row operations.
Get its fixed-layout PDF from Gradescope. Submit the two parts separately.
See Gradescope for the due date.

## Build and run

You need a C++17 compiler (GCC or Clang), Make, and an archiver (`ar`).
Python 3 is only needed for the optional `make submission` ZIP target.
Use Linux, macOS with command-line developer tools, or WSL on Windows.

```sh
make
./build/demo
make test
```

`make` builds `build/liblinsys.a`, a static library, and the demonstration
program. The starter **compiles**, but its TODO routines do not yet compute
the answers: the demo initially prints zeros and `make test` fails. After
completing the routines, the demo should print `1 2 3` and `1 1 1`, and the
public test should pass. You can select a compiler with `make CXX=clang++`.

## What is supplied; what to implement

`include/linsys.h` specifies the interface. `src/linsys.cpp` supplies a short,
working `gauss_solve` without pivoting as a starting point. Complete these
four functions in that same file:

1. `lu_factor`: partial-pivoted LU, stored in place, with a row permutation.
2. `forward_substitution`: solve with a unit lower-triangular matrix.
3. `back_substitution`: solve with an upper-triangular matrix.
4. `lu_solve`: form the permuted right-hand side and call the two solves.

Keep the function signatures and supplied baseline. Use loops for elimination
and substitution, and `std::abs` from `<cmath>` to compare pivot magnitudes.
Do not call an existing factorization or solver (Eigen, LAPACK, etc.) in these
routines. You may use such tools independently to check your results.

The required inputs are nonsingular square real matrices, with `n >= 1` and
valid arrays. The triangular solves have nonzero pivots. No rank detection,
singular-system interface, input-validation framework, classes, templates,
or allocation inside the numerical routines is required. Do not discard a
nonzero pivot because it is below an arbitrary absolute threshold. Keep the
arithmetic in `double`; do not enable `-ffast-math`.

## Storage and the permutation convention

An `n`-by-`n` matrix is a single array of `n*n` numbers. Entry `(i,j)` is
`a[i*n+j]`, using zero-based indices. For example,

```cpp
double a[] = {0, 2, 1,  1, 1, 0,  2, 0, 1};
```

stores the rows of the second matrix in PA04 Written.

`lu_factor` replaces this array with the entries of `L` below the diagonal
and the entries of `U` on and above it. The diagonal of `L` is implicitly one.
There is no separate array for `L`, `U`, or the permutation matrix `P`.
Initialize `p[i]=i`; whenever two rows are exchanged, exchange those entries
of `p` too. Our convention is

```text
(P*A)[i,j] = A[p[i],j],       P*A = L*U,       (P*b)[i] = b[p[i]].
```

At step `k`, choose a largest absolute entry in column `k` among rows `k`
through `n-1`. Either choice is accepted in a tie. Exchange the **whole**
rows, including the multipliers stored in earlier columns. Store the new
multipliers in column `k` and update the trailing block. No row normalization
is needed to obtain `U`.

`lu_solve` must preserve the factors and permutation so that another
right-hand side can use them. Its input `b` and output `x` are distinct arrays.
The two triangular routines must also work in place (`b` and `x` identical);
otherwise they preserve `b`. They always preserve the factor array.

## Check your work

- Compare the two small matrices in Written with AARG using matching pivot
  settings. Partial pivoting changes the factors of the first matrix.
- Reconstruct `L` and `U` in a test program and check `P*A = L*U`.
- Check `A*x = b` against the **original** matrix and right-hand side.
- Factor the second matrix once and solve for both right-hand sides in the
  demo. This detects permutation mistakes and accidental changes to the factors.
- Compare `gauss_solve` and pivoted LU on the small-pivot example in Written.
  Keep fresh copies because the baseline overwrites both inputs.
- Add at least one test of your own. The public test is a starting point;
  the grader also uses other sizes, signs, scales, and row exchanges.

The autograder checks factorization, pivot selection, both triangular solves,
solutions, reuse, and the stated storage contract (100 points total). There
is no speed contest or required Python wrapper in this assignment. Efficient
storage and reuse are the programming ideas to understand first.

## Submit

Upload **`linsys.cpp`** from `src/` to **PA04 Code**. Alternatively,

```sh
make submission
```

creates `build/pa04-submission.zip` containing that file for upload. The grader
compiles your implementation against the supplied header and its own driver;
do not put `main` in `linsys.cpp` or rely on changes to the header or Makefile.
Keep any helper functions in `linsys.cpp`.

Submit your completed PDF separately to **PA04 Written**. The written
reflection asks what you checked, including AI-assisted work if you used it.
You are responsible for understanding and verifying every submitted routine.
