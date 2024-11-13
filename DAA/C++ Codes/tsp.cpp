#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int findMinEdge(const vector<vector<int>> &costMatrix, int city)
{
    int minCost = INT_MAX;
    for (int i = 0; i < costMatrix.size(); i++)
    {
        if (costMatrix[city][i] != 0 && costMatrix[city][i] <
                                            minCost)
        {
            minCost = costMatrix[city][i];
        }
    }
    return minCost;
}
int findSecondMinEdge(const vector<vector<int>> &costMatrix, int
                                                                 city)
{
    int firstMin = INT_MAX, secondMin = INT_MAX;
    for (int i = 0; i < costMatrix.size(); i++)
    {
        if (city == i)
            continue;
        if (costMatrix[city][i] <= firstMin)
        {
            secondMin = firstMin;
            firstMin = costMatrix[city][i];
        }
        else if (costMatrix[city][i] <= secondMin &&
                 costMatrix[city][i] != firstMin)
        {
            secondMin = costMatrix[city][i];
        }
    }
    return secondMin;
}

void TSPBranchAndBound(const vector<vector<int>> &costMatrix,
                       vector<bool> &visited, vector<int> &currPath, vector<int> &optimalPath, int &finalCost, int currBound, int currWeight, int level)
{
    int N = costMatrix.size();
    if (level == N)
    {
        int lastToFirst = costMatrix[currPath[level -
                                              1]][currPath[0]];
        if (lastToFirst != 0)
        {
            int currResult = currWeight + lastToFirst;
            if (currResult < finalCost)
            {
                finalCost = currResult;
                optimalPath = currPath;
            }
        }
        return;
    }
    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && costMatrix[currPath[level - 1]][i] != 0)
        {
            int tempBound = currBound;
            currWeight += costMatrix[currPath[level - 1]][i];
            currBound -= (findMinEdge(costMatrix, currPath[level -
                                                           1]) +
                          findMinEdge(costMatrix, i)) /
                         2;
            if (currBound + currWeight < finalCost)
            {
                currPath[level] = i;
                visited[i] = true;
                TSPBranchAndBound(costMatrix, visited, currPath,
                                  optimalPath, finalCost, currBound, currWeight, level + 1);
            }
            currWeight -= costMatrix[currPath[level - 1]][i];
            currBound = tempBound;
            visited[i] = false;
        }
    }
}
void solveTSP(const vector<vector<int>> &costMatrix)
{
    int N = costMatrix.size();
    vector<int> currPath(N);
    vector<int> optimalPath(N);
    vector<bool> visited(N, false);
    int currBound = 0;
    int finalCost = INT_MAX;
    for (int i = 0; i < N; i++)
    {
        currBound += (findMinEdge(costMatrix, i) +
                      findSecondMinEdge(costMatrix, i));
    }
    currBound = (currBound & 1) ? (currBound / 2 + 1) : (currBound / 2);
    visited[0] = true;
    currPath[0] = 0;
    TSPBranchAndBound(costMatrix, visited, currPath, optimalPath,
                      finalCost, currBound, 0, 1);
    cout << "Optimal path: ";
    for (int i = 0; i < N; i++)
    {
        cout << optimalPath[i] + 1 << " ";
    }
    cout << optimalPath[0] + 1 << endl;
    cout << "Minimum cost: " << finalCost << endl;
}
int main()
{
    int N;
    cout << "Cities: ";
    cin >> N;
    vector<vector<int>> costMatrix(N, vector<int>(N));
    cout << "Cost matrix:" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> costMatrix[i][j];
        }
    }
    solveTSP(costMatrix);
    return 0;
}