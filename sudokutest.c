/*
 * sudokutest.c - unit testing for individual functionality of sudoku module
 *
 * Usage: ./sudokutest
 *
 * Quad Mobile
 * CS50, 21X
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sudoku.h"
#include "set.h"

/******************** MAIN ********************/
int main(void)
{
	int emptySudoku[9][9];
	
	// test newEmptyPuzzle()
	printf("testing initialize puzzle...(all squares should be 0)\n");
	newEmptyPuzzle(emptySudoku);
	printSudoku(stdout, emptySudoku);
	printf("\n");

	// create hard coded puzzle to test with
	int hardCoded[9][9] = {
	    {8, 1, 0, 0, 0, 0, 0, 9, 0},
	    {0, 0, 2, 0, 0, 6, 0, 0, 0},
	    {0, 3, 4, 8, 0, 7, 0, 0, 0},
	    {0, 0, 3, 2, 0, 0, 0, 4, 6},
	    {0, 0, 0, 4, 6, 0, 0, 0, 0},
	    {0, 0, 0, 0, 1, 9, 0, 2, 3},
	    {3, 0, 7, 0, 0, 0, 4, 0, 2},
	    {2, 0, 0, 0, 3, 5, 0, 6, 9},
	    {5, 9, 1, 0, 0, 2, 0, 0, 8}
	};

	printf("created a hardcoded incomplete sudoku puzzle:\n");
	printf("num solutions: %d\n", numUnique(hardCoded, 0, 0, 0));
	printSudoku(stdout, hardCoded);
	printf("\n");

	// test getter/setter
	printf("testing setter in empty puzzle...\n");
	printf("\tsetting (0,0) to 9\n");
	setSquare(emptySudoku, 0, 0, 9);
	printf("\tmaking sure with getSquare: %d\n", getSquare(emptySudoku, 0, 0));
	setSquare(emptySudoku, 0, 0, 0);

	printf("\tsetting (7,2) to 3\n");
	setSquare(emptySudoku, 7, 2, 3);
	printf("\tmaking sure with getSquare: %d\n", getSquare(emptySudoku, 7, 2));
	setSquare(emptySudoku, 7, 2, 0);
	printf("\n");

	printf("testing getter in hard coded puzzle...\n");
	printf("\tgetSquare at (0,0) (should be 8): %d\n", getSquare(hardCoded, 0, 0));
	printf("\tgetSquare at (3,2) (should be 3): %d\n", getSquare(hardCoded, 3, 2));
	printf("\n");

	// testing valid row, column, and cell individually
	printf("testing validate input...\n");
	printf("\ttesting insertion of 8 at (0,3) (repeat in row)\n");
	if (!isValidRow(hardCoded, 0, 8)) {
		printf("\tcould not insert in row\n");
	}

	printf("\ttesting insertion of 5 at (2,0) (repeat in column)\n");
	if (!isValidColumn(hardCoded, 0, 5)) {
		printf("\tcould not insert in column\n");
	}

	printf("\ttesting insertion of 4 at (1,1) (repeat in subgrid)\n");
	if (!isValidCell(hardCoded, 1, 1, 4)) {
		printf("\tcould not insert in cell\n");
	}
	printf("\n");

	// test isValidInput (testing all three insert functions together)
	printf("making sure isValidInput can call all three...\n");
	if (!isValidInput(hardCoded, 0, 3, 8)) {
                printf("\tcould not insert (double checking row insertion)\n");
        	printf("\tmake sure square is still 0: %d\n", getSquare(hardCoded, 0, 3));
	}

	if (!isValidInput(hardCoded, 2, 0, 5)) {
                printf("\tcould not insert (double checking column insertion)\n");
        	printf("\tmake sure square is still 0: %d\n", getSquare(hardCoded, 2, 0));
	}

	if (!isValidInput(hardCoded, 1, 1, 4)) {
                printf("\tcould not insert (double checking cell insertion)\n");
        	printf("\tmaks sure square is still 0: %d\n", getSquare(hardCoded, 1, 1));
	}
	printf("\n");

	// testing boundary cases for solver
	printf("testing solver method...\n");

	printf("\ttesting on invalid board (repeat number in a row, col, etc.)\n");
	setSquare(hardCoded, 8, 8, 4);
	solveSudoku(hardCoded);
	printf("\tnum solutions: %d\n", numUnique(hardCoded, 0, 0, 0));
	setSquare(hardCoded, 8, 8, 0);
	printf("\tshowing it still isn't solved: \n");
        printSudoku(stdout, hardCoded);

	printf("\n\tactually solving the puzzle now!\n");
	printSudoku(stdout, hardCoded);
	printf("\tnumber of solutions: %d\n", numUnique(hardCoded, 0, 0, 0));
	solveSudoku(hardCoded);
	printSudoku(stdout, hardCoded);
	printf("\n");
	
	// testing load function
	printf("testing load function by loading hard coded puzzle into empty puzzle\n");
	
	FILE *test = fopen("testfile", "w");
	if (test == NULL) {
		fprintf(stderr, "file could not be opened for writing\n");
		return 1;
	}
	printSudoku(test, hardCoded);
	fclose(test);

	test = fopen("testfile", "r");
	if (test == NULL) {
		fprintf(stderr, "file could not be opened for reading\n");
		return 2;
	}

	loadSudoku(test, emptySudoku);
	fclose(test);
	printf("printing loaded puzzle: (should be a copy of solved hard coded puzzle)\n");
	printSudoku(stdout, emptySudoku);
	printf("\n");

	return 0;
}
