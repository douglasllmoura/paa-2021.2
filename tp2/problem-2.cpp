/**
 * Implementation for the problem 1 - Pontes de São Petersburgo.
 *
 * @author Douglas Moura
 * @date 2022 jan 29 
 *
 */

#include<stdio.h>
#include<algorithm> 

using namespace std;

// bottom-up implemantation to solve the problem
int bottom_up(int degree[], int r, int k) {

    // create list
    int m[k + 1];

    for (int i = 0; i <= k; i++) {
        m[i] = 0;
    }

    m[0] = 1;

    // solve by smallest problem
    for (int i = 0; i < r; i++) {
        for (int j = k; j >= degree[i]; j--) {

            if (m[j - degree[i]] != 0) {
                m[j] = 1;
            }
        }
    }

    return m[k];
}

int main() {

    int r; // number of regions
    int k; // number of bridges 

    while (scanf("%d %d", &r, &k) != EOF) {

        int degree[r]; // storage the vertex degree

        for (int i = 0; i < r; i++) {
            degree[i] = 0;
        }

        int a; // first city
        int b; // second city

        // read bridges
        for (int i = 0; i < k; i++) {
            scanf("%d %d", &a, &b);

            degree[a - 1] ++;
            degree[b - 1] ++;
        }

        // solve the problem
        int ans = bottom_up(degree, r, k);

        // print solution
        if (ans != 0) {
            printf("S\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}
