#include <iostream>
#include <vector>

using namespace std;
// Function to print a subset
void printSubset(const vector<int>& subset) {
    cout << "{ ";
    for (int num : subset) {
        cout << num << " ";
    }
    cout << "}" << endl;
}
// Recursive function to find subsets that sum to M
void subsetSum(const vector<int>& w, vector<int>& subset, int index, int currentSum, int M) {
    // Base case: If the current sum is equal to M, print the subset
    if (currentSum == M) {
        printSubset(subset);
        return;
    }

    // If the sum exceeds M or we have reached the end of the array, return
    if (currentSum > M || index == w.size()) {
        return;
    }

    // Include the current element and proceed
    subset.push_back(w[index]);
    subsetSum(w, subset, index + 1, currentSum + w[index], M);

    // Exclude the current element and proceed
    subset.pop_back();
    subsetSum(w, subset, index + 1, currentSum, M);
}

void findSubsetsWithSumM(const vector<int>& w, int M) {
    vector<int> subset;
    cout << "Subsets of sum " << M << ":\n";
    subsetSum(w, subset, 0, 0, M);
    cout << endl;
}

int main() {
    int M = 35;

    vector<int> w1 = {5, 7, 10, 12, 15, 18, 20};
    vector<int> w2 = {20, 18, 15, 12, 10, 7, 5};
    vector<int> w3 = {15, 7, 20, 5, 18, 10, 12};

    cout << "For set w1:\n";
    findSubsetsWithSumM(w1, M);

    cout << "For set w2:\n";
    findSubsetsWithSumM(w2, M);

    cout << "For set w3:\n";
    findSubsetsWithSumM(w3, M);

    return 0;
}
