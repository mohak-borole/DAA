#include<iostream>
using namespace std;

void printSolution(int board[10][10] ,int size)
{
    for(int i = 0 ; i < size ; i++)
    {
        for (int j = 0 ; j < size ; j++)
        {
            if(board[i][j])
                cout<<"Q\t";
            else
                cout<<".\t";
        }
        cout<<"\n";
    }
}

bool isSafe(int board[10][10] , int row , int col , int size)
{
    int i, j;

    //check row on left
    for (i = 0 ; i < col ; i++)
        if(board[row][i])
            return false;
    
    //for diagonal on left
    for(i = row , j = col ; i>=0 && j>=0 ; i-- , j--)
        if(board[i][j])
            return false;
    //for diagonal on right
    for(i = row , j = col ; i < size && j >= 0 ; i++ , j--)
        if(board[i][j])
            return false;

    return true;
}

bool solveNQueenUtil(int board[10][10] , int col , int size)
{
    if(col >= size)
        return true;

    for (int i = 0 ; i < size ; i++)
    {
        if(isSafe(board , i , col , size))
        {
            board[i][col] = 1;

            if(solveNQueenUtil(board , col+1 , size))
                return true;

            board[i][col] = 0;
        }
    }

    return false;
}

bool solveNQueen(int N)
{
    int board[10][10] = {0};

    if (solveNQueenUtil(board, 0, N) == false) {
        cout << "Solution does not exist";
        return false;
    }

    printSolution(board , N);
    return true;
}

int main()
{
    int n = 4;
    if (!solveNQueen(n)) {
        cout << "Solution does not exist for N = " << n << endl;
    }
    return 0;
}