// Complete a Knights Tour 
// The Knight Can Only Make Legal Moves 
// and must reach every space.
// Author: Gabriel Brown
// Instructor: Tom Rishel
// 9/16/2020

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#define N 8
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Function Prototypes

// Calls two functions (OnBoard & SquareCheck ) and checks 
// to make sure the knights move is a valid one.
bool isValid(int board[][N], int move, int row, int col);

// Ensures move is on the array or board
bool onBoard(int move, int row, int col);

// Makes sure the move has not already been made.
bool squareCheck(int board[][N], int move, int row, int col);

// Prints the board and marks the last valid move
void printBoard(int board[][N], int counter);

// Makes move
void makeMove(int board[][N], int bestAccess);

// Runs a Single Tour
int runTour(int board[][N], int startRow, int startCol);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Global Variables

const int horz[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int vert[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };

int access[N][N] =
{
{ 2, 3, 4, 4, 4, 4, 3, 2 },
{ 3, 4, 6, 6, 6, 6, 4, 3 },
{ 4, 6, 8, 8, 8, 8, 6, 4 },
{ 4, 6, 8, 8, 8, 8, 6, 4 },
{ 4, 6, 8, 8, 8, 8, 6, 4 },
{ 4, 6, 8, 8, 8, 8, 6, 4 },
{ 3, 4, 6, 6, 6, 6, 4, 3 },
{ 2, 3, 4, 4, 4, 4, 3, 2 }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{

	int board[N][N] = { 0 };

	int startRow = 0;
	int startCol = 0;

	int counter = runTour(board, startRow, startCol);

	printBoard(board, counter);

	cout << "Highest move number is: " << counter << endl;
	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Function to keep chess piece on the board.
bool onBoard(int move, int row, int col)
{
	if (row + vert[move] > (N - 1)
		|| row + vert[move] < 0)
	{
		return false;
	}
	else if (col + horz[move] > (N - 1)
		|| col + horz[move] < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Function to ensure chess piece does not make a move to an area previously visited.
bool squareCheck(int board[][N], int move, int row, int col)
{
	if (board[row + vert[move]][col + horz[move]] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function that calls two previous fanctions, making it the complete valid checker.
bool isValid(int board[][N], int move, int row, int col)
{
	if (onBoard(move, row, col) && squareCheck(board, move, row, col))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool lowAccess(int access[][N], int move, int row, int col, int bestAccess)
{
	if (access[row + vert[move]][col + horz[move]] <= bestAccess)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// Changes the row and column to the position of the valid move
void makeMove(int board[][N], int& curRow, int& curCol, int bestaccmove)
{
	curRow += vert[bestaccmove];
	curCol += horz[bestaccmove];
}

// Prints out the board
void printBoard(int board[][N], int counter)
{
	cout << "******************* BOARD ARRAY ******************************" << endl << endl;

	// loop through board and print values

	for (int row = 0; row < N; row++)
	{

		for (int col = 0; col < N; col++)
		{
			if (board[row][col] == counter)
			{
				cout << '*' << board[row][col] << '*' << "\t";
			}
			else
			{
				cout << board[row][col] << "\t";
			}
		}
		cout << endl << endl;
	}
}

int runTour(int board[][N], int startRow, int  startCol)
{
	// Used to indicate that there are no more valid moves
	bool noValidMove = false;

	// Reset Counter and return to starting square
	int counter = 1;
	int cRow = startRow;
	int cCol = startCol;

	// Set value of the starting square to 1 to mark first position
	board[cRow][cCol] = counter;

	// A Completed Tour has no more than 64 moves
	while (counter < 65 && noValidMove == false)
	{
		int bestAccess = 10;
		int accessMoves[8] = { 0 };
		int bestaccmove = 10;


		for (int move = 0; move < 8; move++)
		{
			if (isValid(board, move, cRow, cCol))
			{
				// If the move is valid, subtract one from the accessibility array, as it cant move to where you are now, then record the accessibility number in the array accessMoves

				accessMoves[move] = access[cRow + vert[move]][cCol + horz[move]];
				if (access[cRow + vert[move]][cCol + horz[move]] < 1)
				{
					(accessMoves[move] = 99);
				}
				else
				{
					access[cRow + vert[move]][cCol + horz[move]]--;
				}
				// If the number on the accessibility array is less than the previous number, than it is the least acessible move and it should be recorded. 
				if (accessMoves[move] <= bestAccess)
				{
					// This will be how we get our best move each turn.
					bestAccess = accessMoves[move];
					bestaccmove = move;
				}

			}
			if (move == 7)
			{
				if (bestAccess == 10)
				{
					noValidMove = true;
				}
				else
				{
					cout << counter << ".)" << bestAccess << endl;
					makeMove(board, cRow, cCol, bestaccmove);
					counter++;
					board[cRow][cCol] = counter;
					break;
				}

			}
		}
	}
	// Tells how many times tour has completed.
	return counter;
}
