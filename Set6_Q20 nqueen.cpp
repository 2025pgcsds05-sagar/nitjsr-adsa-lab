#include <stdio.h>
#include <math.h>

#define N 4  // you can change N for different board sizes

int board[N];

// Function to print the solution
void printSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if placing queen is safe
int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // check column & diagonal conflicts
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}

// Backtracking function
void solveNQueens(int row) {
    if (row == N) {
        // all queens placed successfully
        printSolution();
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;   // place queen
            solveNQueens(row + 1); // try next row
            // backtrack (no need to reset explicitly because board[row] will be overwritten)
        }
    }
}

int main() {
    printf("Solutions for %d-Queens problem:\n\n", N);
    solveNQueens(0);
    return 0;
}

