// Overall Time Complexity
// The solveNQueens function makes recursive calls, and each call to solveNQueens can make
// 𝑁 calls to isSafe (one for each column).
// Given the recursive depth
// 𝑁 and 𝑂(𝑁) operations within each depth level, the overall worst-case time complexity of this algorithm is roughly 𝑂(𝑁𝑁×𝑁)=𝑂(𝑁𝑁+1).
// Space Complexity
// The space complexity is 𝑂(𝑁2)due to the 2D vector board of size 𝑁×𝑁.
// The recursion stack also takes 𝑂(𝑁) space in the worst case (one level per row).
// Therefore, the space complexity is dominated by the board, resulting in an overall space complexity of 𝑂(𝑁2)

// O(N!)

#include <iostream>
#include <vector>
using namespace std;

// Function to print the chessboard solution
void printBoard(const vector<vector<int>> &board, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 1)
                cout << "Q "; // 'Q' denotes a queen
            else
                cout << ". "; // '.' denotes an empty cell
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if placing a queen at (row, col) is safe
bool isSafe(const vector<vector<int>> &board, int row, int col, int N)
{
    // Check the column for any queens
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
            return false;
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
    {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

// Recursive function to solve the N-Queens problem
bool solveNQueens(vector<vector<int>> &board, int row, int N)
{
    // Base case: If all queens are placed
    if (row == N)
    {
        printBoard(board, N); // Print one of the possible solutions
        return true;
    }

    bool foundSolution = false;

    // Try placing the queen in each column of the current row
    for (int col = 0; col < N; col++)
    {
        if (isSafe(board, row, col, N))
        {
            // Place the queen
            board[row][col] = 1;

            // Recur to place the rest of the queens
            foundSolution = solveNQueens(board, row + 1, N) || foundSolution;

            // Backtrack (remove the queen) if placing queen at (row, col) doesn't lead to a solution
            board[row][col] = 0;
        }
    }

    return foundSolution;
}

int main()
{
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;

    // Initialize an empty N x N chessboard
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueens(board, 0, N))
    {
        cout << "No solution exists for " << N << " queens.\n";
    }

    return 0;
}
