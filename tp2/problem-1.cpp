/**
 * Implementation for the problem 1 - Apagando e Ganhando.
 *
 * @author Douglas Moura
 * @date 2022 jan 29 
 *
 */

#include<stdio.h>
#include<stack>

using namespace std;

// algorithm to solve the problem
void solve (int number[], int n, int d) {

    stack<int> stack;

    stack.push(number[0]); // stack the first number

    for (int i = 1; i < n; i++) {
        
        // check if stack is empty and top <= number[i]
        while (!stack.empty() && stack.top() < number[i]) {

            // check the number of digits to be deleted
            if (d > 0) {
                stack.pop(); // remove digit from the stack
                d--;
            } else {
                break;
            }
        }

        stack.push(number[i]); // add digit into the stack
    }

    // remove repeated
    while (d > 0 && !stack.empty()) {
        stack.pop();
        d--;
    }

    // build final solution
    std::stack<int> aux;

    // pop until stack is empty
    while (!stack.empty()) {
        aux.push(stack.top());
        stack.pop();
    }

    // pop the auxiliary stack
    while (!aux.empty()) {
        printf("%d", aux.top());
        aux.pop();
    }

    printf("\n");
}

int main () {

    int n; // number of digits
    int d; // number of digits to be deleted

    while (1) {

        scanf("%d %d", &n, &d);

        if (n == 0 && d == 0) {
            break;
        }

        int number[n];

        // read input
        for (int i = 0; i < n; i++) {
            scanf("%1d", &number[i]);
        }

        // solve the problem
        solve(number, n, d);
    }

    return 0;
}
