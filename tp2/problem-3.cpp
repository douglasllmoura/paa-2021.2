/**
 * Implementation for the problem 3 - ônibus.
 *
 * @author Douglas Moura
 * @date 2022 feb 02
 *
 */

#include<stdio.h>

typedef signed long long int lli;

using namespace std;


// Multiplies two matrices and store the result in ans[][2]
void multiply(lli mat1[2][2], lli mat2[2][2], lli ans[2][2]) {

    lli temp[2][2] = {{0}}; // store the temporary result

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {

            for (int k = 0; k < 2; k++) {
                temp[i][j] += (mat1[i][k] % 1000000 * mat2[k][j] % 1000000) % 1000000;
            }
        }
    }

    // store the final result in ans[2][2]
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ans[i][j] = temp[i][j] % 1000000;
        }
    }
}

// Computes the matrix m raised to the power of n 
void power(lli mat[2][2], lli n, lli ans[2][2]) {

    if (n > 0) {
        if (n % 2 == 0) {
            multiply(mat, mat, mat);
            power(mat, n/2, ans); // call again for n/2

        } else {
            multiply(ans, mat, ans);
            power(mat, n - 1, ans); // call again for n - 1
        }
    }
}

int main() {

    lli n; // total length
    lli k; // number of colors of the micro-buses 
    lli l; // number of colors of the buses

    while (scanf("%llu %llu %llu", &n, &k, &l) != EOF) {

        lli mat1  [2][2] = {{0, l % 1000000}, {1, k % 1000000}}; 
        lli mat2  [2][2] = {{1, k % 1000000}, {0, 0}};

        lli identity [2][2] = {{1, 0}, {0, 1}}; // identity matrix

        power(mat1, n/5, identity); // raises the matrix to power n/5 

        multiply(mat2, identity, mat1); // multiplies the result for ans

        printf("%06llu\n", mat1[0][0] % 1000000);
    }

    return 0;
}
