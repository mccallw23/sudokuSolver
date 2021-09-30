# Quad Mobile
# sudoku makefile



CFLAGS = -Wall -pedantic -std=gnu11 -D_GNU_SOURCE -ggdb
CC = gcc 
MAKE = make


all: creator solver sudokutest

creator: creator.o sudoku.o set.o
	$(CC) $(CFLAGS) $^ -o $@

solver: solver.o sudoku.o set.o
	$(CC) $(CFLAGS) $^ -o $@

sudokutest: sudokutest.o sudoku.o set.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f creator solver sudokutest

