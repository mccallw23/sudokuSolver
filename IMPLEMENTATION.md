# Implementation for Sudoku Solver (solver.c) and Creator (creator.c)
## Quad Mobil CS50 21X

### Overview

For general details and use about `solver.c`, `creator.c`, and the header file `sudoku.h` with its corresponding implementation `sudoku.c`, view the `README.md` file.


### Functions

Here are the functions contained in the header file, `sudoku.c`, most of which are used by both `solver.c` and `creator.c`:

```c
void newEmptyPuzzle(int puzzle[9][9]);
int getSquare(int puzzle[][9], int row, int column);
void setSquare(int puzzle[][9], int row, int column, int num);
bool solveSudoku(int puzzle[][9]);
bool isValidInput(int puzzle[][9], int row, int column, int numToInsert);
bool isValidRow(int puzzle[][9], int row, int numToInsert);
bool isValidColumn(int puzzle[][9], int column, int numToInsert);
bool isValidCell(int puzzle[][9], int row, int column, int numToInsert);
int numUnique(int puzzle[][9], int i, int j, int numFound);
void printSudoku(FILE * fileref, int puzzle[][9]);
void loadSudoku(FILE *fileref, int puzzle[][9]);
bool isValidSudoku(int puzzle[][9]);
```

Below are the functions used specifically by `creator.c`:

```c
void fillDiagonals(int puzzle[][9]);
void removeSquares(int puzzle[][9]);
int countValidSquares(int sudoku[][9]);
```

### Pseudocode for Sudoku Solver

1. Load a formatted sudoku file into a 2D array with loadSudoku(), storing '0' to represent empty squares
2. For each empty square:
    3. Loop through the numbers 1-9 and set square with the first number that is a validInput
    4. If a validInput is inserted, recursively call the solveSudoku() function to iterate until the next empty square and repeat step 3
    5. Else if a validInput is not found, then leave the square as '0' and return *false*. This will recurse upwards and reset the number of the previous index to the next validInput
6. Return *true* once the entire puzzle has been filled in


### Pseudocode for Sudoku Creator

1. Initialize a new empty puzzle, i.e. a 2D array filled w/ zeroes, with newEmptyPuzzle()
2. For each 3x3 cell along the main diagonal:
    - Randomly fill its boxes with the numbers 1-9
3. Call solveSudoku() to fill in the rest of the puzzle recursively (see above for sudoku solver pseudocode)
4. Establish the number of cells *n* to be removed (randomly chosen b/w 41 and 50)
5. Randomly remove *n* cells, only allowing a removal if numUnique() returns 1, i.e. the resulting puzzle has 1 unique solution


### Error Handling and Recovery

loadSudoku() exits on error if given an improperly formatted sudoku file

`creator.c` and `solver.c` exit on error if passed the improper number of arguments 

files are checked if readable/writeable upon opening. if they fail to open or do not fulfill these properties, exit on error


### Data Structures and APIs

The sudoku puzzle is stored in a 2D array.
`sudoku.c` uses `set` to check if isValidSudoku


### Resource management

The 2D array holding the sudoku puzzle is stored on the stack. We use significant stack memory in the recursive solveSudoku() method because we essentially create a copy of the sudoku puzzle (w/ 1 modification) with each recursive call.


### Assumptions

The solver assumes the puzzle has only 1 unique solution (we only check for the unique solution condition in creator)
