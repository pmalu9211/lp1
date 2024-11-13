#include <iostream>
#include <vector>
using namespace std;

bool isSafe(const vector<int> &board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || board[i] == col - (row - i) || board[i] == col + (row - i))
            return false;
    }
    return true;
}

bool solveNQueensUtil(vector<int> &board, int row, int n) {
    if (row == n) return true;
    
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            if (solveNQueensUtil(board, row + 1, n)) return true;
            board[row] = -1;
        }
    }
    return false;
}

vector<int> solveNQueens(int n) {
    vector<int> board(n, -1);
    solveNQueensUtil(board, 0, n);
    return board;
}

int main() {
    int n = 4;
    for (int col : solveNQueens(n)) cout << col << " ";
    cout << endl;
    return 0;
}




/*
#include <iostream>
#include <vector>
using namespace std;

bool isSafe(const vector<int> &board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || board[i] == col - (row - i) || board[i] == col + (row - i))
            return false;
    }
    return true;
}

void solveNQueensUtil(vector<int> &board, int row, int n, vector<vector<int>> &solutions) {
    if (row == n) {
        solutions.push_back(board);  // Store the current board configuration as a solution
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueensUtil(board, row + 1, n, solutions);
            board[row] = -1;  // Backtrack
        }
    }

}

vector<vector<int>> solveNQueens(int n) {
    vector<int> board(n, -1);              // Board configuration
    vector<vector<int>> solutions;         // All possible solutions
    solveNQueensUtil(board, 0, n, solutions);
    return solutions;
}

int main() {
    int n = 4;
    vector<vector<int>> solutions = solveNQueens(n);
    cout << "Total solutions for " << n << "-Queens: " << solutions.size() << endl;
    for (const auto &solution : solutions) {
        for (int col : solution) cout << col << " ";
        cout << endl;
    }
    return 0;
}
*/