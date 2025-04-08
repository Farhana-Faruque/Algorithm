#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// BFS for finding augmenting path
bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    int V = rGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

// Ford-Fulkerson Algorithm using Edmonds-Karp (BFS)
int fordFulkerson(vector<vector<int>>& graph, int s, int t) {
    int V = graph.size();
    vector<vector<int>> rGraph = graph; // Residual graph
    vector<int> parent(V);
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        // Find minimum residual capacity in the augmenting path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Update residual capacities
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    ifstream infile("input.txt");
    int V, E;
    infile >> V >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    for (int i = 0; i < E; ++i) {
        int u, v, cap;
        infile >> u >> v >> cap;
        graph[u][v] = cap;
    }

    int s, t;
    infile >> s >> t;

    int maxFlow = fordFulkerson(graph, s, t);
    cout << "The maximum possible flow is " << maxFlow << endl;

    return 0;
}
