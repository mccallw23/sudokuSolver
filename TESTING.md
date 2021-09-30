# Testing for Sudoku solver.c and creator.c
## Quad Mobile, CS50 21X

Here, we thoroughly document all the kinds of testing done for sudoku.c, solver.c, and creator.c. The kinds of testing used are:
  
  * argument testing
  * fuzz testing
  * unit testing


### Argument Testing

With a shell script, run various cases of invalid command line arguments to test argument error handling.

This testing can be run by doing `./arguments.sh`. Below is the output:
```
1
too many arguments. Usage: ./creator [optional: filename]
2
written to valid file
3
5 0 9 0 0 0 7 8 0 
7 0 0 1 6 0 3 0 0 
6 0 3 5 0 9 2 0 0 
0 9 0 6 0 0 0 0 0 
0 0 7 8 0 4 9 6 0 
8 3 0 0 0 0 0 2 0 
0 0 1 0 2 0 0 0 8 
9 6 4 0 0 0 1 0 0 
0 0 0 0 0 1 0 0 3 
5
 argument notreal is not readable, check usage ./solver [file1] [file2]
6
5 0 9 0 0 0 7 8 0 
7 0 0 1 6 0 3 0 0 
6 0 3 5 0 9 2 0 0 
0 9 0 6 0 0 0 0 0 
0 0 7 8 0 4 9 6 0 
8 3 0 0 0 0 0 2 0 
0 0 1 0 2 0 0 0 8 
9 6 4 0 0 0 1 0 0 
0 0 0 0 0 1 0 0 3 

^loaded successfully
number of unique solutions (should be 1): 1 

5 1 9 2 4 3 7 8 6 
7 4 2 1 6 8 3 5 9 
6 8 3 5 7 9 2 1 4 
4 9 5 6 1 2 8 3 7 
1 2 7 8 3 4 9 6 5 
8 3 6 9 5 7 4 2 1 
3 7 1 4 2 6 5 9 8 
9 6 4 3 8 5 1 7 2 
2 5 8 7 9 1 6 4 3 
every item in the puzzle is valid, therefore the puzzle was solved successfully
```


### Fuzz testing

For our programs, fuzz testing creates and solves n puzzles (n is provided in the command line when the program is ran). `./creator` is piped to `./solver` n times, and both the incomplete and completed puzzles can be viewed in stdout.

Fuzz testing can be ran by doing `./fuzztest.sh`. 

Example output from running fuzz testing:

```
$ ./fuzztest.sh 1

0 2 3 0 5 4 0 0 9 
0 0 0 0 0 0 0 0 0 
7 0 5 0 0 8 2 3 1 
2 6 0 8 0 0 0 0 4 
3 5 0 6 4 0 1 0 7 
4 0 9 5 3 0 8 2 0 
0 7 0 4 8 0 9 1 0 
0 0 0 7 0 0 4 8 0 
1 8 0 0 9 5 7 0 0 

^loaded successfully
number of unique solutions (should be 1): 1 

8 2 3 1 5 4 6 7 9 
6 9 1 2 7 3 5 4 8 
7 4 5 9 6 8 2 3 1 
2 6 7 8 1 9 3 5 4 
3 5 8 6 4 2 1 9 7 
4 1 9 5 3 7 8 2 6 
5 7 2 4 8 6 9 1 3 
9 3 6 7 2 1 4 8 5 
1 8 4 3 9 5 7 6 2 
every item in the puzzle is valid, therefore the puzzle was solved successfully
```


### Unit Testing

For unit testing, we individually test the various functionality used in `sudoku.c`. The testing of these functions is done using both a completely empty sudoku puzzle and a hard-coded incomplete sudoku puzzle.

The following tests are run in `sudokutest.c`:

  1. make sure newEmptyPuzzle sets all squares to 0
  2. test printSudoku by printing out a hard coded puzzle
  3. test the getter and setter
    3. set a square value in the empty puzzle, then get it to make sure it worked
    3. find a square in the hardcoded puzzle and get it from coordinates you pick
  4. test checking a valid input
    4. call isValidRow with a value you know is already in that row
    4. call isValidColumn with a value you know is already in that column
    4. call isValidCell with a value you know is already in that cell 
    4. call isValidInput for all three values/locations tested above to make sure this function calls the other three properly
  5. test boundary cases for `solver.c`
    5. solve the empty puzzle (won't work, there isn't one unique solution)
    5. solve an invalid board (set a square to a repeated value and try to solve, just make sure you set it back afterwards)
    5. solve on a valid board with one unique solution
  6. test load function by printing the solved board to a file, opening the file again and loading it into the empty puzzle

At most/all of the above steps, print out the sudoku boards along the way to check their status as they are being tested on.

Output from running unit testing:

```
$ ./sudokutest

testing initialize puzzle...(all squares should be 0)
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 

created a hardcoded incomplete sudoku puzzle:
num solutions: 1
8 1 0 0 0 0 0 9 0 
0 0 2 0 0 6 0 0 0 
0 3 4 8 0 7 0 0 0 
0 0 3 2 0 0 0 4 6 
0 0 0 4 6 0 0 0 0 
0 0 0 0 1 9 0 2 3 
3 0 7 0 0 0 4 0 2 
2 0 0 0 3 5 0 6 9 
5 9 1 0 0 2 0 0 8 

testing setter in empty puzzle...
	setting (0,0) to 9
	making sure with getSquare: 9
	setting (7,2) to 3
	making sure with getSquare: 3

testing getter in hard coded puzzle...
	getSquare at (0,0) (should be 8): 8
	getSquare at (3,2) (should be 3): 3

testing validate input...
	testing insertion of 8 at (0,3) (repeat in row)
	could not insert in row
	testing insertion of 5 at (2,0) (repeat in column)
	could not insert in column
	testing insertion of 4 at (1,1) (repeat in subgrid)
	could not insert in cell

making sure isValidInput can call all three...
	could not insert (double checking row insertion)
	make sure square is still 0: 0
	could not insert (double checking column insertion)
	make sure square is still 0: 0

testing solver method...
	testing on emtpy puzzle (more than one sol, expect return value > 1)
	number of solutions: 2
	showing it still isn't solved: 
8 1 0 0 0 0 0 9 0 
0 0 2 0 0 6 0 0 0 
0 3 4 8 0 7 0 0 0 
0 0 3 2 0 0 0 4 6 
0 0 0 4 6 0 0 0 0 
0 0 0 0 1 9 0 2 3 
3 0 7 0 0 0 4 0 2 
2 0 0 0 3 5 0 6 9 
5 9 1 0 0 2 0 0 8 
	testing on invalid board (repeat number in a row, col, etc.)
	num solutions: 0
	showing it still isn't solved: 
8 1 0 0 0 0 0 9 0 
0 0 2 0 0 6 0 0 0 
0 3 4 8 0 7 0 0 0 
0 0 3 2 0 0 0 4 6 
0 0 0 4 6 0 0 0 0 
0 0 0 0 1 9 0 2 3 
3 0 7 0 0 0 4 0 2 
2 0 0 0 3 5 0 6 9 
5 9 1 0 0 2 0 0 0 

	actually solving the puzzle now!
8 1 0 0 0 0 0 9 0 
0 0 2 0 0 6 0 0 0 
0 3 4 8 0 7 0 0 0 
0 0 3 2 0 0 0 4 6 
0 0 0 4 6 0 0 0 0 
0 0 0 0 1 9 0 2 3 
3 0 7 0 0 0 4 0 2 
2 0 0 0 3 5 0 6 9 
5 9 1 0 0 2 0 0 0 
	number of solutions: 1
8 1 5 3 2 4 6 9 7 
9 7 2 1 5 6 8 3 4 
6 3 4 8 9 7 2 1 5 
1 5 3 2 7 8 9 4 6 
7 2 9 4 6 3 5 8 1 
4 8 6 5 1 9 7 2 3 
3 6 7 9 8 1 4 5 2 
2 4 8 7 3 5 1 6 9 
5 9 1 6 4 2 3 7 8 

testing load function by loading hard coded puzzle into empty puzzle
printing loaded puzzle: (should be a copy of solved hard coded puzzle)
8 1 5 3 2 4 6 9 7 
9 7 2 1 5 6 8 3 4 
6 3 4 8 9 7 2 1 5 
1 5 3 2 7 8 9 4 6 
7 2 9 4 6 3 5 8 1 
4 8 6 5 1 9 7 2 3 
3 6 7 9 8 1 4 5 2 
2 4 8 7 3 5 1 6 9 
5 9 1 6 4 2 3 7 8 
```
