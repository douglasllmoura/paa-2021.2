/**
 * Implementation for the problem 6 - Cartões.
 *
 * @author Douglas Moura
 * @date 2022 fev 05
 *
 */
#include<stdio.h>
#include<algorithm>

using namespace std;


// bottom-up approach to solve the problem
long long bottom_up(int cards[], int n) {

    // creates two array to store the answer of each subproblem
    long long** table = new long long*[n];

    for (int i = 0; i < n; i++) {
        table[i] = new long long[2];
    }

    // update the first column with the max between cards[i] and cards[i + 1]
    for (int i = 0; i < n - 1; i++) {
        table[i][0] = max(cards[i], cards[i + 1]);
    }
    
    // initializes the control variables
    int i = 0;
    int step = 3;
    int m = n;
    int index = 0; // saves the current state

    // solves the problem and stores only the last answer
    while (m >= 0) {

        for (int j = step; j < n; j++) {
            long long aux1 = min(table[i + 1][index % 2], table[i + 2][index % 2]);
            long long aux2 = min(table[i + 1][index % 2], table[i][index % 2]);
                
            table[i][(index + 1) % 2] = max(cards[i] + aux1, cards[j] + aux2); // stores the subproblem answer

            i++;
        }
    
    // updates the variables to the next iteration  
    i = 0;
    step = step + 2;
    m = m - 2;
    index++;
    }

    return table[0][index % 2];    
}

int main () {

    int n; // number of cards

    while (scanf("%d", &n) != EOF) {

        int cards[n]; // sequence of cards

        for (int i = 0; i < n; i++) {
            scanf("%d", &cards[i]);
        }

        long long ans = bottom_up(cards, n);

        printf("%lld\n", ans);
    }

    return 0;
}
