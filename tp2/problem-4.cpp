/**
 * Implementation for the problem 4 - Remendo.
 *
 * @author Douglas Moura
 * @date 2022 jan 25 
 *
 */
#include<stdio.h>
#include<algorithm>

using namespace std;

// computes the number of holes repaired and returns the next hole to be repaired 
int search(int holes[], int n, int begin, int type) {

    int next = begin + 1;

    for (int i = begin + 1; i < n; i++) {

        if (holes[i] - holes[begin] <= type) {
            next++;
        } else {
            break;
        }
    }
    
    return next;
}

// Top-down approach to solve the problem.
int top_down(int holes[], int dp[], int n, int begin, int end, int t1, int t2) {

    // case base
    if (begin == end) {
        return min(t1, t2);
    }

    // if all holes are repaired, then return 0
    if (begin > end) {
        return 0;
    }

    // if problem was computed, then return it
    if (dp[begin] != -1) {
        return dp[begin];
    }

    int aux1 = search(holes, n, begin, t1); // number of holes repaired with t1
    int aux2 = search(holes, n, begin, t2); // number of holes repaired with t2

    // gets the best solution and memorizes in dp[begin] 
    dp[begin] = min(t1 + top_down(holes, dp, n, aux1, end, t1, t2), t2 + top_down(holes, dp, n, aux2, end, t1, t2));

    return dp[begin];
}

int main() {

    int n;  // number of holes
    int c;  // wheel circumference
    int t1; // type 1
    int t2; // type 2

    while (scanf("%d %d %d %d", &n, &c, &t1, &t2) != EOF) {

        int holes[n];

        for (int i = 0; i < n; i++) {
            scanf("%d", &holes[i]);
        }

        // creates a vector to memorize computed solutions
        int dp[n];

        for (int i = 0; i < n; i++) {
            dp[i] = -1; // initializes all positions with -1
        }
        
        // solve the problem
        int ans = top_down(holes, dp, n, 0, n - 1, t1, t2);

        printf("%d\n", ans);
    }

    return 0;
}

