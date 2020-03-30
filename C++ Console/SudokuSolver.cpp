// SudokuSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <time.h>

std::vector<char> SolveSudoku(char row, char col, char n, std::vector<char> board);
bool PossibleMove(char row, char col, char move, char n, std::vector<char>& board);
bool IsCorrect(std::vector<char>& board);

int main()
{
    int n = 9;
    std::cout << "Enter n: ";
    std::cin >> n;
    
    srand(time(NULL));

    std::vector<char> board;
    board.push_back(rand() % n);
    for (char a = 1; a < n*n; ++a)
    {
        board.push_back(n);
    }

    std::vector<char> res = SolveSudoku(0, 1, n, board);

    //Checking if the solution is correct
    if (IsCorrect(res))
    {
        //Printing the solved sudoku
        for (char row = 0; row < n; ++row)
        {
            for (char col = 0; col < n; ++col)
            {
                if (res[row * n + col] == n)
                    std::cout << "| ";
                else
                    std::cout << "|" << (int)res[row * n + col];
            }
            std::cout << "|\n";
        }
    }
}

std::vector<char> SolveSudoku(char row, char col, char n, std::vector<char> board)
{
    //Checking if the sudoku has been solved
    if (row == n && col == 0)
        return board;

    //Selecting the value to be entered in the current cell
    for (char a = 0; a < n; ++a)
    {
        if (PossibleMove(row, col, a, n, board))
        {
            board[row * n + col] = a;
            std::vector<char> res;
            if (col == n - 1)
                res = SolveSudoku(row + 1, 0, n, board);
            else
                res = SolveSudoku(row, col + 1, n, board);

            if (res.size() != 0)
                return res;
            board[row * n + col] = n;
        }
    }

    //Returning a empty vector as no solution was found
    return std::vector<char>();
}

bool PossibleMove(char row, char col, char move, char n, std::vector<char>& board)
{
    //Checking if row is safe
    for (char c = 0; c < col; ++c)
    {
        if (board[row * n + c] == move)
            return false;
    }

    //Checking if column is safe
    for (char r = 0; r < row; ++r)
    {
        if (board[r * n + col] == move)
            return false;
    }

    return true;
}

bool IsCorrect(std::vector<char>& board)
{
    static char coords[] = { 0, 0 };

    //Calculating the dimensions of the Sudoku grid
    char n = (char)sqrt(board.size());

    //Exiting function as all the cells have been checked
    if (coords[0] == n)
        return true;

    //Checking if number is repeated in row
    for (char c = 0; c < n; ++c)
    {
        if (c != coords[1])
        {
            if (board[coords[0] * n + coords[1]] == board[coords[0] * n + c])
                return false;
        }
    }

    //Checking if number is repeated in column
    for (char r = 0; r < n; ++r)
    {
        if (r != coords[0])
        {
            if (board[coords[0] * n + coords[1]] == board[r * n + coords[1]])
                return false;
        }
    }

    //Updating the coords
    coords[0] = coords[1] == n - 1 ? coords[0] + 1 : coords[0];
    coords[1] = coords[1] == n - 1 ? 0 : coords[1] + 1;

    //Recursively checking in the next cells
    return IsCorrect(board);
}