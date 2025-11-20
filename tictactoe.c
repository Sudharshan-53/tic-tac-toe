#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 3

// Function prototypes
void initializeBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
int isValidMove(char board[SIZE][SIZE], int row, int col);
int checkWinner(char board[SIZE][SIZE]);
int isBoardFull(char board[SIZE][SIZE]);

int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int row, col;
    int winner = 0;

    initializeBoard(board);

    printf("=== TIC TAC TOE ===\n");
    printf("Player 1: X | Player 2: O\n");
    printf("Enter row and column (1-3) for your move.\n\n");

    while (1) {
        printBoard(board);

        // Get player input
        printf("Player %c, enter your move (row col): ", currentPlayer);
        if (scanf("%d %d", &row, &col) != 2) {
            printf("Invalid input. Please enter two integers.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }

        // Adjust for 0-based index
        row--;
        col--;

        // Validate move
        if (!isValidMove(board, row, col)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        // Make move
        board[row][col] = currentPlayer;

        // Check for winner
        winner = checkWinner(board);
        if (winner) {
            printBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        // Check for draw
        if (isBoardFull(board)) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

// Initialize the board with spaces
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

// Print the board
void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

// Check if move is valid
int isValidMove(char board[SIZE][SIZE], int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE)
        return 0;
    if (board[row][col] != ' ')
        return 0;
    return 1;
}

// Check for winner
int checkWinner(char board[SIZE][SIZE]) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return 1;
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return 1;
    }
    // Check diagonals
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return 1;
    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return 1;

    return 0;
}

// Check if board is full
int isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}
