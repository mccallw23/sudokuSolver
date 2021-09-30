# Sudoku Creator/Solver Design Spec
## QUAD-MOBILE; CS50, 21X

### Overview

A sudoku puzzle is a 9x9 grid in which each square in the grid contains a number 1-9. For a filed sudoku board to have a correct solution, no number may be repeated in any row, column, or 3x3 subgrid. Furthermore, a valid sudoku puzzle may only have one valid solution.

In this project, we create a program that randomly generates a valid sudoku puzzle with only one unique solution. We create another program which solves the randomly created sudoku.

Components of the design spec:

* User Interface
* Inputs and Outputs
* Functional Decomposition into Modules
* Pseudocode for Logic/Algorithmic Flow
* Dataflow Through Modules
* Major Data Structures
* Testing Plan

Each component is more thoroughly explained below.


### User Interface
The sudoku creator's only interface with the user is on the command line; it will require no argumemts

For Example:
```bash
./sudokucreator
```

The sudoku solver's only interface with the user is on the command line; it will require that the sudoku creator's output be piped into this command

For Example:
```bash
./sudokucreator | ./sudokusolver
```

### Inputs and Outputs

Inputs:
  * for the sudoku creator, there is no input
  * for the sudoku solver, an incomplete but solvable sudoku puzzle is piped in from the creator

Outputs:
  * for the sudoku creator, an incomplete but solvable sudoku puzzle with only one unique solution
  * for the sudoku solver, a completed sudoku puzzle


### Functional Decomposition

We anticipate the following functions or modules:

  1. *main*, 
  2. *solve*, which actually solves the sudoku puzzle
  3. *validinput*, which makes sure a number is a valid input for the current square (i.e., does not yet exist in the row, column, or subgrid)
  4. *validpuzzle*, which checks to make sure the solution found is a valid solution
  5. *uniquesolution*, which makes sure that there is one and only one solution to the puzzle

As for helper modules and data structures:

For *validinput*, there will be three helper functions to ensure that an input is infact valid
    * isValidRow, which iterates to the row to ensure that the entry is unique to that row
    * isValidColumn, which iterates to the column to ensure that the entry is unique to that column
    * isValidCell, which uses the coordinates of the index in question to determine the 3x3 cell that it is located in, and iterates through that cell to ensure      that the entry is unique


### Psuedocode for Sudoku Creator
1.  Begin with the first index, randomly fill in the first 3x3 cell with numbers 1-9
2.  Move on to the next diagonal 3x3 cell, the middle of the puzzle and then fill it in, do the same with the bottom right corner 3x3 cell
3.  Use the sudoko solver to fill in the rest of the puzzle recursively (see below for sudoku solver psedudocode)
4.  Randomly reset one index at a time and call uniquesolution() after an index is removed to ensure that the emptied puzzle still has a unique solution, keep doing this until the puzzle is as small as possible without losing its unique solution characteristic


### Pseudocode for Sudoku Solver
1. Using the piped in 2D array from the sudoku creator, the sudoko solver will iterate through the rows of the array
2. For each index in the puzzle
3. If the index is marked with a '0', which represents an empty space
4. Loop through the numbers 1-9 and fill in the index with the first number that is a validinput
5. Once a valid number has been inserted, recursively call the function to iterate until the next empty space is reached and repeat step 4
6. If an index cannot be filled in with any number 1-9, it will get reset back to 0 and return false, which will recurse upwards and reset the number of the previous index to a new valid number
7. Once the entire puzzle has been filled in, the function will return true and we will know that the puzzle has been filled successfully

### Pseudocode for checking Unique solution
1. Take parameters i,j, reference to grid, numfound
2. If we have indexed out of bounds (to 8,9) return numfound + 1 (new solution found)
3. If the cell we have indexed to already contains a non zero number, recurse to the next cell containing by calling the function on the next cell.
4. once we reach a '0' cell, test possibleValues 1-9, using helper function validinput to determine if possiblevalue can go in this cell. 
5. recurse on the next adjacent cell with numfound 
6. once the loop terminates, that means there are no possible valid entries, so return numFound and set this cell's value to prepare for subsequent recursive calls.


### Dataflow

We will keep a header file that will contain all of the functions that will be used in our modules for sudoku creator and sudoku solver

*solve*, recieves an incomplete puzzle (2d array) and solves the sudoku puzzle, returns true when puzzle is solved (and solvable) and returns false when there is no solution
*validinput*, which makes sure a number is a valid input for the current square (i.e., does not yet exist in the row, column, or subgrid) based on parameters passed into it (the coordinates of the index that requires insertion and the number that is going to be inserted)
*validpuzzle*, which takes in the puzzle as a parameter and returns true or false based upon whether or not it is a valid puzzle
*uniquesolution*, which takes in the puzzle as a parameter and returns an int based on the number of solutions that exist for that puzzle


### Data Structures
1. A 9x9 2D array to represent the sudoku puzzle


### Testing
We will create a testing shell script which generates several random puzzles. We will ensure that these random puzzles have only one solution and then we will solve each of these puzzles and ensure that the solved output is infact a correct solution.  We will also test the functionality of our code against a variety of cases to ensure that is has robust error handling.  This will include checking validity and number of arguments as well as handling the cases of a puzzle having no valid solutions, one valid solution, or multiple valid solutions.


