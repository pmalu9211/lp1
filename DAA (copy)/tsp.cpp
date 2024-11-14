// TC O(2^N * N^2),

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <stack>

using namespace std;

const int N = 4;
const int INF = INT_MAX;

// Distance matrix
int dist[N][N] = {
    // 0  1   2   3
    {0, 10, 15, 20}, // 0
    {10, 0, 25, 25}, // 1
    {15, 25, 0, 30}, // 2
    {20, 25, 30, 0}, // 3
};
// 0 1 10

// Function to calculate the minimum outgoing edge from a given city
int findMinEdge(int city)
{
    int minEdge = INF;
    for (int j = 0; j < N; j++)
    {
        if (city != j && dist[city][j] < minEdge)
        {
            minEdge = dist[city][j];
        }
    }
    return minEdge;
}

// Function to calculate a lower bound for a given path
int calculateBound(const vector<int> &path, int currentCost)
{
    int bound = currentCost;

    for (int i = 0; i < N; i++)
    {
        // Skip cities that are already in the path
        if (find(path.begin(), path.end(), i) == path.end())
        {
            bound += findMinEdge(i);
        }
    }

    return bound;
}

// LC Branch and Bound to solve TSP
void tsp()
{
    stack<pair<vector<int>, int>> s; // Stack to store paths and their costs
    vector<int> bestPath;            // Best path found
    int bestCost = INF;              // Minimum cost found

    // Starting path (from city 0)
    vector<int> startPath = {0};
    int startCost = 0;

    s.push({startPath, startCost});

    while (!s.empty())
    {
        auto node = s.top(); // <{0},0>
        s.pop();

        vector<int> path = node.first;
        int currentCost = node.second;
        int currentBound = calculateBound(path, currentCost);

        if (currentBound >= bestCost)
            continue;

        // Check if path is a complete tour
        if (path.size() == N)
        {
            int lastCity = path.back();
            int totalCost = currentCost + dist[lastCity][0]; // Returning to the start city

            if (totalCost < bestCost)
            {
                bestCost = totalCost;
                bestPath = path;
            }
            continue;
        }

        // Expand node to include each possible next city
        for (int i = 0; i < N; i++)
        {
            // Skip cities that are already in the path
            if (find(path.begin(), path.end(), i) == path.end()) //{0,1,2,3}
            {

                vector<int> childPath = path;
                childPath.push_back(i);
                int childCost = currentCost + dist[path.back()][i];
                int childBound = calculateBound(childPath, childCost);

                if (childBound < bestCost)
                {
                    s.push({childPath, childCost});
                }
            }
        }
    }

    // Print the best path and cost
    cout << "Optimal Path: ";
    for (int city : bestPath)
    {
        cout << (char)('A' + city) << " ";
    }
    cout << "A" << endl; // Returning to the start city
    cout << "Minimum Cost: " << bestCost << endl;
}

int main()
{
    tsp();
    return 0;
}
