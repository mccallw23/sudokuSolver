#!/bin/bash
#
# arguments.sh - test argument error handling for solver.c and creator.c
#
# Usage: ./arguments.sh
#
# Quad Mobile
# CS50, 21X

### testing creator.c argument handling

# too many args
echo 1
./creator testfile arg2

# writing to valid file
echo 2
./creator argumentstestfile
echo "written to valid file"

# writing to stdout
echo 3
./creator


### testing solver.c argument handling

# invalid input file
echo 5
./solver notreal outputfile

# writing to stdout (valid)
echo 6
./solver argumentstestfile
