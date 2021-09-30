/* 
 * creator.c - creates a incomplete yet valid sudoku puzzle that has one unique solution
 *
 * Usage: ./creator [optional: filename]
 *
 * QUAD MOBILE
 * CS50, 21X
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "sudoku.h"

/************ function declarations ************/
void removeSquares(int puzzle[][9]);
void fillDiagonals(int puzzle[][9]);

/****************** main ******************/
int main(int argc, char *argv[])
{
	int sudoku[9][9];
	FILE *unsolved;
	
	// check command line arguments
	if (argc > 2) {
		fprintf(stderr, "too many arguments. Usage: ./creator [optional: filename]\n");
		return 1;
	} else if (argc == 1) {
		unsolved = stdout;
	} else {
		unsolved = fopen(argv[1], "w");
	}

	if (unsolved == NULL) {
		fprintf(stderr, "file cannot be found/opened\n");
		return 2;
	}

	//set a seed based on current time for random number generation
	srand(time(NULL));
	
	// initialize all values in puzzle to 0
	newEmptyPuzzle(sudoku);
	
	// randomly fill in diagonal 3x3s
	fillDiagonals(sudoku);
	
	// fill in the rest of the board
	solveSudoku(sudoku);

	// remove a random number of squares to make an incomplete board
	removeSquares(sudoku);
	
	// print incomplete board to file
	printSudoku(unsolved, sudoku);
		
	return 0;
}

/****************** functions ******************/
/*** removeSquares() ***/
/* Reset a random amount of randomly placed squares in the sudoku
 * puzzle back to 0 to provide an incomplete board that can be solved
 */
void removeSquares(int sudoku[][9])
{
	// need to establish upper and lower bounds of # you can remove
	int lowerBound = 41;
	int upperBound = 50;
	int maxRemove = rand() % (upperBound + 1 - lowerBound) + lowerBound;  

	// used to index into sudoku board
	int row;
	int col;
	
	int removed = 0;
	while (removed < maxRemove) { // while you can still remove squares
		// randomly pick a square, make sure it's value isn't already 0
		do {
			row = rand() % 9;
			col = rand() % 9;
		} while (getSquare(sudoku, row, col) == 0);

		// get current square value in case you need to reset it
		int curr = getSquare(sudoku, row, col);
		setSquare(sudoku, row, col, 0);

		// if you don't have only one unique solution from previous remove
		if (numUnique(sudoku, 0, 0, 0) != 1) {
			// reset the square you just set to 0
			setSquare(sudoku, row, col, curr);
		} else {
			// only increment number of removed on a successful remove
			removed++;
		}
	}

}

/*** fillDiagonals() ***/
/* Randomly fill every square in the 1st, 5th, and 9th quadrant of the sudoku board
 */
void fillDiagonals(int sudoku[][9])
{	
	int quadrant = 0;
	
	for (int row = 0; row < 9; row++) { // for the 3 diagonal subgrids (still go through 9 rows)
		for (int col = 0 + quadrant; col < 3 + quadrant; ) {
			int randnum = rand() % 9 + 1; // get a random number between 1 and 9

			// make sure it's a valid insert
			if (isValidCell(sudoku, row, col, randnum)) {
				// is square already set by calling isValidCell?
				setSquare(sudoku, row, col, randnum);

				// only go to next square once you've done a valid insert
				col++;
			}
		}
		
		// see if you need to go to next subgrid
		if (((row+1) % 3) == 0) quadrant+=3;
	}

}

/*** countValidSquares() ***/
/* testing function
 * count how many squares have a 0 value (have not been filled yet)
 */
int countValidSquares(int sudoku[][9]) {
	int count = 0;
	
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
		    if (getSquare(sudoku, row, col) == 0) {
		    	count++;
		    }
		}
	}
	
	return count;
}
