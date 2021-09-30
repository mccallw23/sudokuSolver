# High Level Design for Sudoku Solver
## CS50, 21X

### Functions

* actually solve the puzzle
	* checks for one square if its a valid number input
		* does the number break the row?
		* break the column?
		* break the subgrid?
		* if valid input, move on to the next empty square
		* if not valid input, go back to the most recent square filled and try a new number
	* check if whole puzzle is valid
		* check every row, column, and 3x3 (do 3 loops)
			* nested loop for each 3x3
		* if they all pass, then we are good!
	
* is the solution unique?


### Potential problems and their solutions

1. making sure you don't write over fixed spaces when backtracking
	* go through each box in the puzzle 
	* once we come across a box that is empty, attempt to fill it with a valid number
	* keep track of that box as the "parent node", move onto the next empty box
	* if there is no valid input for that next empty box, return to the parent node (the previous empty box that has just been filled) and try again
