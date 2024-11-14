/* Stages of Relaxation: By running V-1 relaxation steps, the algorithm ensures that all shortest paths of up to V-1 edges are correctly calculated. This dynamic programming aspect comes from the "optimal substructure" property, where shorter paths are built up to solve the longer paths. */
/*
 Overlapping Subproblems: Each vertex’s shortest path distance depends on previously computed shortest path values for neighboring vertices, which are updated repeatedly.
*/
/*
 Iterative Refinement: The algorithm refines solutions with each pass, aiming to minimize the distance to each vertex progressively, making it an example of a bottom-up dynamic programming approach.
*/

// Why 𝑉−1 Iterations?

/*
 If a vertex is reachable from the source, the shortest path to it would involve at most 𝑉−1 edges. Therefore, by performing 𝑉−1 iterations, we ensure that every vertex’s shortest path has been fully relaxed.
*/
/*
 By the 𝑉−1 iteration, all vertices that can be reached from the source will have the shortest possible distance calculated.
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
{
    // Step 1: Initialize distances from the source to all vertices as infinite
    V++;
    vector<int> distance(V, 1e8); // 𝑂(𝑉)
    distance[src] = 0;            // Can reach the starting node with zero distance

    // Step 2: Relax all edges |V| - 1 times
    //  𝑂((𝑉−1)⋅𝐸)
    for (int index = 0; index < V - 1; index++)
    {
        for (auto it : edges)
        {
            int src = it[0], dest = it[1], weight = it[2];
            if (distance[src] != 1e8 && distance[src] + weight < distance[dest])
            {
                distance[dest] = distance[src] + weight; // Minimizing the distance after each cycle
            }
        }
    }
    for (int index = 0; index < V - 1; index++)
    {
        for (auto it : edges)
        {
            int src = it[0], dest = it[1], weight = it[2];
            if (distance[src] != 1e8 && distance[src] + weight < distance[dest])
            {
                cout << "Negative cycle detected" << endl;
                return {-1}; // Minimizing the distance after each cycle
            }
        }
    }
    return distance;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<vector<int>> edges = {{1, 2, 6}, {2, 5, -1}, {5, 7, 3}, {3, 2, -2}, {3, 5, 1}, {6, 7, 3}, {4, 6, -1}, {4, 3, -2}, {1, 4, 5}};

    vector<int> answer = bellmanFord(7, edges, 1);

    for (auto it : answer)
        cout << it << " ";
    cout << endl;

    return 0;
}