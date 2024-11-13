#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// A structure to represent an item with weight and value
struct Item
{
    int weight;
    int value;
    double ratio;
    // Constructor
    Item(int w, int v) : weight(w), value(v)
    {
        ratio = (double)value / weight;
    }
};

// Function to calculate the maximum value we can get
double knapsackGreedy(int capacity, const vector<int> &weights, const vector<int> &values)
{
    int n = weights.size();
    vector<Item> items;

    // Create a list of items from weights and values arrays

    for (int i = 0; i < n; ++i)
    {
        items.push_back(Item(weights[i], values[i]));
    }

    // Print the table
    cout << "SR.NO Weight Profit P/W" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << setw(5) << i + 1 << setw(8) << weights[i] << setw(8) << values[i] << setw(8) << fixed << setprecision(2) << items[i].ratio << endl;
    }

    // Sort items by value-to-weight ratio in descending order
    sort(items.begin(), items.end(), [](Item a, Item b)
         { return a.ratio > b.ratio; });

    double totalValue = 0.0; // Total value in the knapsack
    int currentWeight = 0;   // Current weight in the
    for (int i = 0; i < n; ++i)
    {
        if (currentWeight + items[i].weight <= capacity)
        {
            // If the item can be fully added
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        }
        else
        {
            // If the item cannot be fully added, take the fractional part
            int remainingWeight = capacity - currentWeight;
            totalValue += items[i].value * ((double)remainingWeight / items[i].weight);
            break; // Knapsack is full
        }
    }
    return totalValue;
}

int main()
{
    int capacity;
    int n; // Number of items

    // Input capacity of knapsack
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // Input number of items
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weights(n);
    vector<int> values(n);

    // Input weights and values for each item
    for (int i = 0; i < n; ++i)
    {
        cout << "Enter weight and value for item " << i + 1 << ": ";
        cin >> weights[i] >> values[i];
    }

    // Calculate maximum value

    double maxValue = knapsackGreedy(capacity, weights, values);

    cout << "Maximum value in knapsack = " << maxValue << endl;

    return 0;
}