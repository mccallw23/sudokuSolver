/* 
* solver.c - solves an incomplete sudoku passed in by user
* 
* Usage: ./solver [inputfile] [outputfile]
* 
* QUAD MOBILE
* CS50, 21X
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sudoku.h"
#include "set.h"


int main(int argc, char *argv[]) {

	// initialize new sudoku puzzle
	int sudoku1[9][9];
	newEmptyPuzzle(sudoku1);

	// initialize files
	FILE *inputFile;
	FILE *outputFile;

	// validate command line arguments
	if (argc == 1)
	{
		inputFile = stdin;
		outputFile = stdout;
	}
	else if (argc == 2) // input file passed in
	{
		inputFile = fopen(argv[1], "r");
		outputFile = stdout;
	}
	else if (argc == 3) { // input and output files passed in
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "w");
	}
	else {
		fprintf(stderr, " incorrect number of arguments, check usage ./solver [file1] [file2]\n");
		exit(-1);
	}


	// check if files opened successfully
	if (inputFile == NULL) {
		fprintf(stderr, " argument %s is not readable, check usage ./solver [file1] [file2]\n", argv[1]);
		exit(-1);
	}	
	if (outputFile == NULL) {
		fprintf(stderr, " argument %s is not writeable, check usage ./solver [file1] [file2]\n", argv[2]);
		exit(-1);
	}	

	// load in sudoku
	loadSudoku(inputFile, sudoku1);
	printSudoku(outputFile, sudoku1);
	fprintf(outputFile, "\n");
	fprintf(outputFile, "^loaded successfully\n");
	fprintf(outputFile, "number of unique solutions (should be 1): %d \n", numUnique(sudoku1,0,0,0));
	fprintf(outputFile, "\n");

	// solve and print sudoku
	solveSudoku(sudoku1);
	printSudoku(outputFile, sudoku1);
	if (isValidSudoku(sudoku1)) { // check every row, column, and cell to ensure valid
		fprintf(outputFile, "every item in the puzzle is valid, therefore the puzzle was solved successfully\n");
	} else {
		fprintf(outputFile, "not a valid sudoku\n");
	}
	
	// close files
	fclose(inputFile);
	fclose(outputFile);

	exit(0);
}
	

	


