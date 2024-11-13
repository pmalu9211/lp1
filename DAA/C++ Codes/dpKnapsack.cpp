#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int knapsack(int capacity, vector<int> &profit, vector<int> &weight, vector<int> &includedItems)
{
    int n = weight.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    // Fill dp table
    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= capacity; w++)
        {
            if (weight[i - 1] <= w)
            {
                dp[i][w] = max(dp[i - 1][w], profit[i - 1] + dp[i - 1][w - weight[i - 1]]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    // Track which items are included
    int w = capacity;
    for (int i = n; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            includedItems[i - 1] = 1;
            w -= weight[i - 1];
        }
        else
        {
            includedItems[i - 1] = 0;
        }
    }
    return dp[n][capacity];
}
int main()
{
    int capacity = 8;
    vector<int> profit = {2, 3, 4, 5};
    vector<int> weight = {3, 4, 5, 6};
    vector<int> includedItems(profit.size(), 0);
    int maxProfit = knapsack(capacity, profit, weight,includedItems);

    for (int i = 0; i < weight.size(); i++)
    {
        cout << profit[i] << " " << weight[i] << "\n";
    }
    cout << "\n";
    for (int i = 0; i < includedItems.size(); i++)
    {
        cout << includedItems[i] << " ";
    }
    cout << "\nOutput: " << maxProfit << endl;
    return 0;
}