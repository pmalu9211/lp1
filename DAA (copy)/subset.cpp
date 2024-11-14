#include <iostream>
#include <vector>

using namespace std;

// Recursive function to check if a subset with a given sum exists
bool findSubsetWithSum(const vector<int> &numbers, int targetSum, int index, vector<int> &subset)
{
    // Base cases
    if (targetSum == 0)
    { // Found a subset that matches the target sum
        return true;
    }
    if (index == 0 || targetSum < 0)
    { // Reached end of list or sum went negative
        return false;
    }

    // Include the current element in the subset and check further
    subset.push_back(numbers[index - 1]);
    if (findSubsetWithSum(numbers, targetSum - numbers[index - 1], index - 1, subset))
    {
        return true;
    }

    // Exclude the current element and check further
    subset.pop_back();
    return findSubsetWithSum(numbers, targetSum, index - 1, subset);
}

// Wrapper function to print the result
void printSubsetWithSum(const vector<int> &numbers, int targetSum)
{
    vector<int> subset;
    int n = numbers.size();

    // Call the recursive function to find the subset
    if (findSubsetWithSum(numbers, targetSum, n, subset))
    {
        cout << "Subset found with sum " << targetSum << ": ";
        for (int num : subset)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No subset found with sum " << targetSum << endl;
    }
}

int main()
{
    int targetSum = 35;

    // Test with different sets of numbers
    vector<int> set1 = {5, 7, 10, 12, 15, 18, 20};
    vector<int> set2 = {20, 18, 15, 12, 10, 7, 5};
    vector<int> set3 = {15, 7, 20, 5, 18, 10, 12};

    cout << "Testing set {5, 7, 10, 12, 15, 18, 20}\n";
    printSubsetWithSum(set1, targetSum);

    cout << "\nTesting set {20, 18, 15, 12, 10, 7, 5}\n";
    printSubsetWithSum(set2, targetSum);

    cout << "\nTesting set {15, 7, 20, 5, 18, 10, 12}\n";
    printSubsetWithSum(set3, targetSum);

    return 0;
}
