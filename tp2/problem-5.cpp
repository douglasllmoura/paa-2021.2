/**
 * Implementation for the problem 5 - Cortando canos.
 *
 * @author Douglas Moura
 * @date 2022 jan 25 
 *
 */
#include<stdio.h>
#include <algorithm> 

using namespace std;

// top-down approach to solve the problem
int top_down(int c[], int v[], int m[], int n, int size) {

    // base case
    if (size <= 0) {
        return 0;
    }

    // get the solution stored
    if (m[size] != -1) {
        return m[size];
    }

    int ans = 0;

    // find the size that maximizes the value
    for (int i = 0; i < n; i++) {
        
        // check the pipe size
        if (c[i] <= size) {
            ans = max(ans, v[i] + top_down(c, v, m, n, size - c[i]));
        }
    }
    
    m[size] = ans;

    return m[size];
}

// call the dynamic programing algorithm
int cut_pipe(int c[], int v[], int size, int n) {

    int m[size + 1]; // memoization list

    for (int i = 0; i < size + 1; i++) {
        m[i] = -1;
    }

    return top_down(c, v, m, n, size);
}

// bottom-up implementation
int bottom_up(int c[], int v[], int size, int n) {

    int m[size + 1];

    // list initialization
    for (int i = 0; i < size + 1; i++) {
        m[i] = 0;
    }

    // build solution by the smallest problem
    for (int i = 0; i < size + 1; i++) {

        for (int j = 0; j < n; j++) {

            if (c[j] <= i) {
                m[i] = max(m[i], m[i - c[j]] + v[j]);
            }
        }
    }

    return m[size];
}

int main() {

    int n; // number of pipe size
    int size; // size of pipe

    while (scanf("%d %d", &n, &size) != EOF) {

        int c[n]; // length of pipe i
        int v[n]; // value of pipe i

        // read each pipe size
        for (int i = 0; i < n; i++) {
            
            scanf("%d %d", &c[i], &v[i]);
        }

        int ans = cut_pipe(c, v, size, n);
 
        printf("%d\n", ans);
    }

    return 0;
}

