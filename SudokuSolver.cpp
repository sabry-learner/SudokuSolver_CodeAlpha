#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

const int SIZE = 9;

bool isValidMove(int board[SIZE][SIZE], int row, int col, int num)
{
    // Check if 'num' is already in the same row or column
    for (int i = 0; i < SIZE; i++)
    {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // Check if 'num' is already in the same 3x3 box
    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;

    for (int i = boxRowStart; i < boxRowStart + 3; i++)
    {
        for (int j = boxColStart; j < boxColStart + 3; j++)
        {
            if (board[i][j] == num)
                return false;
        }
    }

    return true;
}

void printBoard(int grid[SIZE][SIZE])
{
    system("cls");
    cout << "==============================" << endl;
    cout << "         SUDOKU GAME          " << endl;
    cout << "==============================" << endl;

    for (int i = 0; i < SIZE; i++)
    {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------" << endl;
        for (int j = 0; j < SIZE; j++)
        {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            if (grid[i][j] == 0)
                cout << ". ";
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool solveSudoku(int board[SIZE][SIZE], int row, int col)
{
    if (row == SIZE - 1 && col == SIZE)
        return true;

    if (col == SIZE)
    {
        row++;
        col = 0;
    }

    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);

    for (int num = 1; num <= SIZE; num++)
    {
        if (isValidMove(board, row, col, num))
        {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}

void generateSudoku(int board[SIZE][SIZE])
{
    srand(time(0));
    solveSudoku(board, 0, 0);

    // Remove random numbers to create a puzzle
    int numToRemove = 40; // Adjust difficulty level here
    while (numToRemove > 0)
    {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (board[row][col] != 0)
        {
            board[row][col] = 0;
            numToRemove--;
        }
    }
}

int main()
{
    int board[SIZE][SIZE] = {0};

    generateSudoku(board);

    while (true)
    {
        cout << "==============================" << endl;
        cout << "         SUDOKU GAME          " << endl;
        cout << "==============================" << endl;
        cout << "[1] Play Sudoku" << endl;
        cout << "[2] Show Solution" << endl;
        cout << "[3] Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            printBoard(board);
            cout << "\nFill in the empty cells with numbers from 1 to 9." << endl;
            cout << "Enter row, column, and number separated by spaces (e.g., 1 1 5)." << endl;
            cout << "Enter -1 to exit." << endl;
            while (true)
            {
                int row, col, num;
                cout << "\nEnter your move: ";
                cin >> row >> col >> num;

                if (row == -1 || col == -1 || num == -1)
                {
                    cout << "\nGoodbye!\n";
                    return 0;
                }

                if (row < 1 || row > SIZE || col < 1 || col > SIZE || num < 1 || num > 9)
                {
                    cout << "Invalid input! Please enter numbers between 1 and 9 for row, column, and number.\n";
                    continue;
                }

                if (board[row - 1][col - 1] != 0)
                {
                    cout << "Cell is already filled. Please choose an empty cell.\n";
                    continue;
                }

                if (!isValidMove(board, row - 1, col - 1, num))
                {
                    cout << "Invalid move! Try again.\n";
                    continue;
                }

                board[row - 1][col - 1] = num;
                printBoard(board);

                if (solveSudoku(board, 0, 0))
                {
                    cout << "\nCongratulations! You have solved the Sudoku puzzle.\n";
                    break;
                }
            }
            break;
        case 2:
            if (solveSudoku(board, 0, 0))
            {
                cout << "Completely Solved Sudoku is: " << endl;
                cout << endl
                     << endl;
                for (int row = 0; row < SIZE; row++)
                {
                    for (int col = 0; col < SIZE; col++)
                    {
                        if (col == 3 || col == 6)
                            cout << " | ";
                        cout << board[row][col] << " ";
                    }
                    if (row == 2 || row == 5)
                    {
                        cout << endl;
                        for (int i = 0; i < SIZE; i++)
                            cout << "---";
                    }
                    cout << endl;
                }
                cout << endl;
                cout << "Better luck next time!!!" << endl;
            }
            else
                cout << "No solution found" << endl;

            break;
        case 3:
            cout << "Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
