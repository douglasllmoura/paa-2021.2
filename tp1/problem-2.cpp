/**
 * Implementation for the problem 2 - Novo Campus.
 *
 * @author Douglas Moura
 * @date 2021 nov 30 
 *
 */

#include<stdio.h>
#include<limits.h>
#include<vector>
#include<queue>
 
using namespace std;


typedef pair<int, int> pi;

// add a new edge between two vertices
void add_edge(vector <pair<int, int> > adj[], int v1, int v2, int weight) {
    adj[v1].push_back(make_pair(v2, weight));
    adj[v2].push_back(make_pair(v1, weight));
}

// perform the prim's algorithm to find a minimum spanning tree
int* mst_prim(vector <pair<int, int> > adj[], int n) {
    
    priority_queue<pi, vector<pi>, greater<pi>> pq; // priority queue
    int* key = new int[n];                          // key values
    bool visited[n];                                // store if vertex as visited

    // initialize arrays
    for (int i = 1; i < n; i++) {
        pq.push(make_pair(INT_MAX, i));
        key[i] = INT_MAX;
        visited[i] = false;
    }

    // set the key root as 0
    pq.push(make_pair(0, 0));
    key[0] = 0;
    
    for (int v = 0; v < 2 * n; v++) {
        
        // get the element of the most priority
        pair<int, int> top = pq.top();
        pq.pop();

        int i = top.second;
        visited[i] = true; // mark as visited

        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {

            int j = it->first;
            int weight = it->second;

            // check if the queue contains j
            if (!visited[j] && weight < key[j]) {
                key[j] = weight;                  // update cost
                pq.push(make_pair(key[j], j));    // add to the priority queue
            }
        }
    }

   return key;
}

// build the solution problem
int check_mst(int* costs, int n) {

    int total = 0;

    // ignore the root
    for (int i = 1; i < n; i++) {
        if (costs[i] == INT_MAX) {
            return -1;
        } else {
            total += costs[i];
        }
    }

    return total;
}

int main() {

    int n; // number of builds
    int m; // number of ways

    while (scanf("%d %d", &n, &m) != EOF) {
    
        // create a graph adjacency list
        vector<pair<int, int> > adj[n];
    
        // add edges
        for (int i = 0; i < m; i++) {
            int u, v, w;

            scanf("%d %d %d", &u, &v, &w);

            add_edge(adj, u-1, v-1, w);
        }

        // compute the minimum spanning tree
        int *costs = mst_prim(adj, n);

        // compute the cost
        int total = check_mst(costs, n);

        // check and print the solution
        if (total != -1) {
            printf("%d\n", total);
        } else {
            printf("impossivel\n");
        }
    }

    return 0;
}
