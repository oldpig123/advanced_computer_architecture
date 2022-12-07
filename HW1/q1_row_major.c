#include <stdlib.h>

int main() {
    int x[5000][100];  // what we care about is number of ticks and miss rate,
                       // so it is not really necessarry to set initial value.
    int i, j;
    for (i = 0; i < 5000; i = i + 1) {
        for (j = 0; j < 100; j = j + 1) {
            x[i][j] = 2 * x[i][j];
        }
    }
    return 0;
}