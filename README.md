# Sudoku Solver


This ReadMe was last updated: August 22, 2021


Sudoku is well known logic puzzle where numbers between 1 and 9 are placed on a 9x9 grid of cells. The placement of numbers has to follow certain rules:
1. A sudoku board must be 9x9.
2. Each row must contain the numbers [1-9] with no repetition.
3. Each column must contain the numbers [1-9] with no repetition.
4. Each 3x3 "cell" must contain the numbers [1-9] with no repetition.

This module is capable of randomly generating and returning an sudoku board with just 1 unique solution to be solved.  It is also capable of completely solving a given 9x9 sudoku board if a solution exists.

To build this module run command `make`.  For representative test cases, run `make test`.  To make a new random sudoku puzzle, run `./creator [filename]` which writes a randomly generated and formatted sudoku puzzle to output file [filename].  To solve a given sudoku puzzle, run `./solver [fileinput] [fileoutput]` which takes a reference to a file with a formatted sudoku puzzle for processing, and a seperate filename to return the completed puzzle.  Alternatively, you may choose to run `./creator | ./solver` which will create and solve a puzzle, outputting the result to standard output.

