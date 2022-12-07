#include <math.h>
#include <stdlib.h>

int main() {
    int x[100][100], y[100][100], z[100][100];
    int i, j, k, n = 100, r;
    int kk, jj;
    int b = 50;
    for (jj = 0; jj < n; jj = jj + b) {
        for (kk = 0; kk < n; kk = kk + b) {
            for (i = 0; i < n; i = i + 1) {
                for (j = jj; j < ((jj + b > n) ? n : jj + b); j = j + 1) {
                    r = 0;
                    for (k = kk; k < ((kk + b > n) ? n : kk + b); k = k + 1) {
                        r = r + y[i][k] * z[k][j];
                    }
                    x[i][j] = x[i][j] + r;
                }
            }
        }
    }

    return 0;
}