/**
 * Implementation for the problem 3 - Viagem para BH.
 *
 * @author Douglas Moura
 * @date 2021 dez 02 
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
}

// perform the dijkstra's algorithm to find the minimum shortest path
int* dijkstra(vector <pair<int, int> > adj[], int n, int source, int dest) {

    int bus[n]; // distance vector for the bus travel
    int plane[n]; // distance vector the the plane travel

    priority_queue<pi, vector<pi>, greater<pi>> p0; // priority queue (bus)
    priority_queue<pi, vector<pi>, greater<pi>> p1; // priority queue (plane)

    // initialize arrays
    for (int i = 1; i < n; i++) {
        p0.push(make_pair(INT_MAX, i));
        p1.push(make_pair(INT_MAX, i));

        bus[i] = INT_MAX;
        plane[i] = INT_MAX;
    }

    // set the distance root as 0
    p0.push(make_pair(0, 0));
    bus[0] = 0;

    p1.push(make_pair(0, 0));
    plane[0] = 0;

    while (!p0.empty() && !p1.empty()) {

        // get the element of the most priority
        pair<int, int> top_0 = p0.top();
        pair<int, int> top_1 = p1.top();

        int i, type;
        if (top_0.first <= top_1.first) {
            i = top_0.second;
            p0.pop();
            type = 0;

        } else {
            i = top_1.second;
            p1.pop();
            type = 1;
        }

        // check each edge
        for (auto it = adj[i].begin(); it != adj[i].end(); it++) {

            int j = it->first;
            int weight = it->second;

            if (weight > 0 && type == 0) {

                // relax the edge
                if (bus[i] + weight < bus[j]) {
                    bus[j] = bus[i] + weight;        // update the distance
                    p0.push(make_pair(bus[j], j));   // add to the priority queue
                }

            } else if (weight < 0 && type == 1) {
                
                weight = -1 * weight;

                // relax the edge
                if (plane[i] + weight < plane[j]) {
                    plane[j] = plane[i] + weight;    // update the distance
                    p1.push(make_pair(plane[j], j)); // add to the priority queue
                }
            }
        }
    }

    if (bus[n-1] <= plane[n-1]) {
        printf("%d\n", bus[n-1]);
    } else {
        printf("%d\n", plane[n-1]);
    }
}

int main() {

    int n; // number of cities
    int m; // number of connections

    while (scanf("%d %d", &n, &m) != EOF) {

        // create a graph adjacency list
        vector<pair<int, int> > adj[n];
    
        // add edges
        for (int i = 0; i < m; i++) {
            
            int a, b, t, r;

            scanf("%d %d %d %d", &a, &b, &t, &r);

            // bus
            if (t == 0) {
                add_edge(adj, a-1, b-1, r);

            // plane            
            } else {
                add_edge(adj, a-1, b-1, -r);
            }
        }

        // run dijkstra to solve the problem
        dijkstra(adj, n, 0, n-1);
    }

    return 0;
}
