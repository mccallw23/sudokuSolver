/*
 * sudoku.c - implementation for sudoku.h header file
 *
 * QUAD MOBILE
 * CS50, 21X
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sudoku.h"
#include "set.h"

/*** newEmptyPuzzle() ***/
/* see sudoku.h for more description */
void newEmptyPuzzle(int puzzle[9][9]) {
        //nested for loop sets every square equal to 0 to start.
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
		      setSquare(puzzle, i, j, 0);
		}
	}

}

/*** getSquare() ***/
/* see sudoku.h for more description */
int getSquare(int puzzle[][9], int row, int column)
{
        //simple getter
	return puzzle[row][column];
}

/*** setSquare() ***/
/* see sudoku.h for more description */
void setSquare(int puzzle[][9], int row, int column, int num)
{
        //simple setter
	puzzle[row][column] = num;
}

/*** solveSudoku() ***/
/* see sudoku.h for more description */
bool solveSudoku(int puzzle[][9]) {
        //nested for loop to iterate over each item in the puzzle
	for (int row = 0; row < 9; row++) {
                for (int column = 0; column < 9; column++) {

                        //check to see if the value in this index is 0.  If it is, test possible insertions from 1-9.  Otherwise
                        //simply continue to the next row,col location and repeat
                        if (getSquare(puzzle, row, column) == 0) {
                                for (int insertion = 1; insertion <= 9; insertion++) {
                                        //if the insertion is valid, set it
                                        if (isValidInput(puzzle, row, column, insertion)) {
                                                setSquare(puzzle, row, column, insertion);
                                                //recursive approach.  if everything was subsequently solved, return true.
                                                if (solveSudoku(puzzle)) {
                                                        return true;
                                                } 
                                                else {
                                                        //otherwise, set the value to 0 for subsequent edits
                                                        setSquare(puzzle, row, column, 0);
                                                }
                                        }
                                }
        
				return false;
                        }
                }
        }
        // if we get through every index successfully return true.
        return true;
}	

/*** isValidInput() ***/
/* see sudoku.h for more description */
bool isValidInput(int puzzle[][9], int row, int column, int numToInsert) {

  //checks helpers for cell, col, row.

	return isValidCell(puzzle, row, column, numToInsert) && isValidColumn(puzzle, column, numToInsert) && isValidRow(puzzle, row, numToInsert);
}


/*** isValieRow() ***/
/* see sudoku.h for more description */
bool isValidRow(int puzzle[][9], int row, int numToInsert) 
{
        //iterate through row and make sure nothing with same value exists in row
	for (int i = 0; i < 9; i++) {
                if (puzzle[row][i] == numToInsert) {
                        return false;
                }
        }
	
        return true;
}

/*** isValidColumn() ***/
/* see sudoku.h for more description */
bool isValidColumn(int puzzle[][9], int column, int numToInsert) 
{
        //iterate through column and ensure nothing with same value already exists
	for (int i = 0; i < 9; i++) {
                if (puzzle[i][column] == numToInsert) {
                        return false;
                }
        }
	
        return true;
}

/*** isValidCell() ***/
/* see sudoku.h for more description */
bool isValidCell(int puzzle[][9], int row, int column, int numToInsert) 
{
        //automatically maps to top left index of each cell
        int currCellRow = row - row % 3;
        int currCellColumn = column - column % 3;
        // for each item in the cell, ensure that it is not equal to the desired insertion value.
        for (int i = currCellRow; i < currCellRow + 3; i++) {
                for (int j = currCellColumn; j < currCellColumn +3; j++) {
                        if (puzzle[i][j] == numToInsert) {
                                return false;
                        }
                }
        }
	
        return true;
}

/*** numUnique() ***/
/* see sudoku.h for more description */
int numUnique(int puzzle[][9], int i, int j, int numFound) 
{
        //logic for iterating through the puzzle. increment j if i is 9.
        if (i == 9) {
                i = 0;
                j += 1;
                //if we exceed j bounary we have found a solution
                if (j == 9) {
                	return numFound + 1;
                }
        }
        // if the value at this position is not 0, recursively skip it.
        if (getSquare(puzzle, i, j) != 0) {
                return numUnique(puzzle, i+1, j, numFound);
        }
        //otherwise, test insertions, if insertion works, recurse
        for (int insertion = 1; insertion <= 9 && numFound < 2; insertion++) {
                if (isValidInput(puzzle, i , j, insertion)) {
                        setSquare(puzzle, i, j, insertion);
                        numFound = numUnique(puzzle, i+1, j, numFound);
                }
        }
        // if no insertions work then set square value to 0 before bubbling up.
        setSquare(puzzle, i, j, 0);

        return numFound;

}

/*** printSudoku() ***/
/* see sudoku.h for more description */
void printSudoku(FILE *fileref, int puzzle[][9])
{
        //nested for loop printing a space between each integer in a row and new line for each column.
	for (int row = 0; row < 9; row++) {
                
                for (int column = 0; column < 9; column++) {
                        fprintf(fileref, "%d ", getSquare(puzzle, row, column));
                }
                fputc('\n', fileref);
               
        }


}

/*** loadSudoku() ***/
/* see sudoku.h for more description */
void loadSudoku(FILE *fileref, int puzzle[][9])
{
  	//loads sudoku in from a file
        // 81 numbers to scan
        int numstoscan = 81;
        int i = 0;

        //while more to scan, check for integers, read them in to appropriate row/column
        while (i < numstoscan)
        {       
                if (fscanf(fileref, "%d ", &puzzle[i/9][i%9]) != 1)
                {
                        fprintf(stderr, "improperly formatted input\n");
                }

                i++;
        }

}

//function to determine if sudoku puzzle is valid after completion.
bool isValidSudoku(int puzzle[][9]) {
        //make new set of entries
        set_t *entries = set_new();
        // character ID's for row, col, cell.
        char *row = "row";
        char *col = "col";
        char *cell = "cell";
        // for each item in the cell
        for (int i = 0; i < 9; i++) {
                
                for (int j = 0; j < 9; j++) {
                //insert the current value into the set as having been found in the appropriate row, col, and cell
                int currVal = puzzle[i][j];

                char *rowEntry;
                asprintf(&rowEntry, "%d %s %d", currVal, row, i);

                char *colEntry;
                asprintf(&colEntry, "%d %s %d", currVal, col, j);

                char *cellEntry;
                //identify cell by top left index.
                asprintf(&cellEntry, "%d %s %d %s %d", currVal, cell, i/3, "-", j/3);

                // ensure that no value has already been inserted into the set.  If it has that violates sudoku constraints
                if ((!set_insert(entries, rowEntry, ".")) || 
                       		!set_insert(entries, colEntry, ".") || 
                        	!set_insert(entries, cellEntry, ".")) {
                        	return false;
                        }       
                }
        }
        // if we exit the loop our set is valid.
        return true;
}
