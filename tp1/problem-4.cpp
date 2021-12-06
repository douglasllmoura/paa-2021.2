/**
 * Implementation for the problem 4 - Final Mundial de 2008.
 *
 * @author Douglas Moura
 * @date 2021 dez 04 
 *
 */

#include<stdio.h>
#include<limits.h>

using namespace std;

// perform the floyd warshall's algorithm to find the minimum shortest path
int* floyd_warshall(int** w, int n, int c, int* o, int* d, int* t, int t_max) {

    int dist[n][n];
    
    // copy the distance matrix
    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < n; j++) {
            dist[i][j] = w[i][j];
        }
    }

    int *cost = new int[c];
    
    // compute the distance for each k city
    for (int k = 0; k <= t_max; k++) {

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                // check the min distance
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != INT_MAX
                        && dist[i][k] != INT_MAX)) {

                    dist[i][j] = dist[i][k] + dist[k][j]; // update the distance
                }
            }
        }

        // check each query and the number of cities
        for (int l = 0; l < c; l++) {
                
            if (k < t[l]) {
                cost[l] = dist[o[l]][d[l]];
                
            } else if (k == 0) {
                cost[l] = w[o[l]][d[l]];
            }
        }
    }

    return cost;    
}
 
int main() {

    int n; // number of cities
    int m; // number of connections

    int k = 0; // number of instance

    while (scanf("%d %d", &n, &m) != EOF) {

        // number of instance
        printf("Instancia %d\n", ++k);

        // create a graph adjacency matrix
        int **adj;

        adj = new int *[n];

        // initialize the matrix
        for (int i = 0; i < n; i++) {    
            adj[i] = new int[n];
        
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    adj[i][j] = INT_MAX;
                } else {
                    adj[i][j] = 0;
                }
            }
        }

        int u, v, w;

        // add edges
        for (int i = 0; i < m; i++) {
    
            scanf("%d %d %d", &u, &v, &w);
            
            // graph can be multiple edges
            if (adj[u - 1][v - 1] > w) {
                adj[u - 1][v - 1] = w;
            }
        }

        int c; // number of queries
        scanf("%d", &c);

        int *origin = new int[c];
        int *destiny = new int[c];
        int *cities = new int[c];

        int t_max = 0;

        // do each query
        for (int i = 0; i < c; i++) {

            int o, d, t;

            scanf("%d %d %d", &o, &d, &t);

            origin[i] = o - 1;  // add in origin vector
            destiny[i] = d - 1; // add in destiny vector
            cities[i] = t;      // add in t vector

            if (t > t_max) t_max = t;
        }

        // run floyd warshall to solve the problem
        int* cost = floyd_warshall(adj, n, c, origin, destiny, cities, t_max);

        // print solution
        for (int l = 0; l < c; l++) {
        
            if (cost[l] < INT_MAX) {
                printf("%d\n", cost[l]);
            } else {
                printf("%d\n", -1);
            }
        }

        printf("\n");
    }

    return 0;
}
