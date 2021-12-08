/**
 * Implementation for the problem 1 - Chefe.
 *
 * @author Douglas Moura
 * @date 2021 dez 06 
 *
 */

#include<stdio.h>
#include<limits.h>
#include<vector>

#define WHITE 0
#define GRAY 1
#define BLACK 2
 
using namespace std;

// perform the recursive call in each neighbor
void visit (vector<int> adj[], int* color, int* age, int* answer, int next) {	
    
    color[next] = GRAY; // mark as visited
 
    for (auto it = adj[next].begin(); it != adj[next].end(); it++) {
        
        int j = *it;

        if (color[j] == WHITE) {
            
            // update the answer
            if (*answer > age[j]) *answer = age[j];

            visit(adj, color, age, answer, j);
        }
    }

    color[next] = BLACK; // mark as finished
}

// perform the DSF algorithm to find the shortest path
void dsf(vector<int> adj[], int* age, int n, int root) {

    int color[n];

	for (int i = 0; i < n; i++) {
        color[i] = WHITE;
    }

    int answer = INT_MAX;

    // make a recursive call
    visit(adj, color, age, &answer, root);

    // print the answer
    if (answer < INT_MAX) {
        printf("%d\n", answer);
    } else {
        printf("*\n");
    }
}

void swap(vector<int> adj[], int n, int a, int b) {
    
    // change de adjacency list
    swap(adj[a], adj[b]);

    // swap a and b
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < adj[i].size(); j++) {

            if (adj[i][j] == a) {
                adj[i][j] = b;

            } else if (adj[i][j] == b) {
                adj[i][j] = a;
            }
        }
    }
}


int main() {

    int n; // number of employees
    int m; // number of manager relationships
    int i; // number of instructions

    while (scanf("%d %d %d", &n, &m, &i) != EOF) {
    
        int age[n]; // age of employees

        // read ages
        for (int j = 0; j < n; j++) {
            scanf("%d", &age[j]);
        }

        int x; // manager
        int y; // managed

        vector<int> adj[n]; // create the graph adjacency list

        // read relationships
        for (int j = 0; j < m; j++) {
            scanf("%d %d", &x, &y);

            // add edge
            adj[y - 1].push_back(x - 1);
        }

        char instruction;
        int a;
        int b;

        // read instructions
        for (int j = 0; j < i; j++) {
            
            char line[100];
            scanf(" %[^\n]s\n", line);

            sscanf(line, "%c %d %d", &instruction, &a, &b);
           
            if (instruction == 'P') {
               
                // ask the manager's age
                dsf(adj, age, n, a - 1);

            } else {
                
                // swap a and b
                swap(adj, n, a - 1, b - 1);
            }
        }
    }

    return 0;
}
