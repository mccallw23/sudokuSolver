#!/bin/bash
# fuzz testing for sudoku creator.c and solver.c
# 
# Usage: ./fuzztest n
#
# Program creates (creator.c) and solves (solver.c) n number of sudoku puzzles 

# Incorrect # of args error
if [  $# != 1 ] 

then echo "You did not pass the correct arguments"
     
    exit 2;
fi


n=$1

while [ 0 -lt $n ]
do 
	echo
	./creator | ./solver
	n=$(( $n - 1 ))
	sleep 1
	
done 

