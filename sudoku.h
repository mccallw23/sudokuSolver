/*
 * sudoku.h - header file for sudoku puzzle
 *
 * QUAD MOBILE
 * CS50, 21X
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

#ifndef __SUDOKU_H
#define __SUDOKU_H

/*** newEmptyPuzzle() ***/
/*
 * loops through the entire 9x9 grid and sets every single index to 0
  because a 0 in any index signifies to other functions an empty index
 */
void newEmptyPuzzle(int puzzle[9][9]);

/*** getSquare() ***/
/*
 * returns the value of the index given coordinates and a 9x9 grid 
 */
int getSquare(int puzzle[][9], int row, int column);

/*** setSquare() ***/
/*
 * sets the value of a given index to a parameter "num" when given coordinates and a 9x9 array
 */
void setSquare(int puzzle[][9], int row, int column, int num);

/*** solveSudoku() ***/
/*
 * given a 9x9 puzzle, the solve method will iterate through every column of every row. if a given index is empty, 
 the solver will try and insert a number between 1-9 that is a valid entry, meaning that it is unique to its row column and cell, 
if it deems the insertion valid, it will set that index to that number and then recursively call the function again. if no number 1-9
works for the solver, it will set that index back to 0 and backtrace, and change the previous number in the puzzle until the puzzle has been solved
 */
bool solveSudoku(int puzzle[][9]);

/*** isValidRow() ***/
/*
 * iterates through the row and ensures that the number being inserted is unique to that row
 * given a row number a puzzle and a number to be inserted
 */
bool isValidRow(int puzzle[][9], int row, int numToInsert);

/*** isValidColumn() ***/
/*
 * iterates through the row and ensures that the number being inserted is unique to that column 
 * given a column number a puzzle and a number to be inserted
 */
bool isValidColumn(int puzzle[][9], int column, int numToInsert);

/*** isValidCell() ***/
/* 
 * uses a modulus equation to figure out the top left index of any 3x3 cell given any coordinates 
 and iterates through the 3x3 box to see if that number to insert is infact a valid insertion
 */
bool isValidCell(int puzzle[][9], int row, int column, int numToInsert);

/*** isValidInput() ***/
/*
 * calls isValidColumn, isValidRow, isValidCell and ensures they all return true
 */
bool isValidInput(int puzzle[][9], int row, int column, int numToInsert);


/*** numUnique() ***/
/* Return the number of unique solutions for the sudoku puzzle (recursively)
 *
 * Caller provides:
 *   a sudoku puzzle (9x9 2d-array), a start index (i,j), and the number of unique solutions found so far.
 * We return:
 *   0 if no unique solutions. 
 *   1 if one unique solution.
 *   2 if two or more unique solutions
 * Note: 
 *   The user-provided start index (i,j) should be (0,0) and numFound should be 0.
 *   These are only given as parameters so the recursive function can increment them
 */
int numUnique(int puzzle[][9], int i, int j, int numFound);


/*** printSudoku() ***/
/* Print the whole sudoku puzzle. 
 *
 * Caller provides:
 *   a FILE open for writing, and a sudoku puzzle (9x9 2d-array).
 * We print: 
 *   A formatted sudoku board (columns separated by spaces, rows separated by newlines).
 */
void printSudoku(FILE * fileref, int puzzle[][9]);


/*** isValidSudoku() ***/
/* Returns true if the sudoku is valid, false otherwise.
 *
 * Caller provides:
 *   a sudoku puzzle (9x9 2d-array).
 * Note:
 *   a sudoku is valid if it is doesn't have repeats in its rows, columns, or cells
 */
bool isValidSudoku(int puzzle[][9]);


/*** loadSudoku() ***/
/* Loads a sudoku file into a sudoku puzzle (a 9x9 2d-array))
 *
 * Caller provides:
 *   a FILE open for writing, and a sudoku puzzle (9x9 2d-array).
 * We guarantee:
 *   the sudoku file is properly formatted, print error message if not
 */
void loadSudoku(FILE *fileref, int puzzle[][9]);
#endif








