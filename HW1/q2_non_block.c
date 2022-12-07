#include <math.h>
#include <stdlib.h>

int main() {
    int x[100][100], y[100][100], z[100][100];
    int i, j, k, n = 100, r;
    for (i = 0; i < n; i = i + 1) {
        for (j = 0; j < n; j = j + 1) {
            r = 0;
            for (k = 0; k < n; k = k + 1) {
                r = r + y[i][k] * z[k][j];
            }
            x[i][j] = r;
        }
    }
    return 0;
}