# define the name of the executable
EXE = main

# define the source and header files
SRC = main.c
HDR = ../library/include/lib.h

# define the compiler and the flags
CC = gcc
CFLAGS = -Wall -I../library/include
LDFLAGS = -L../library -lmylib

# define the rule to create the executable
$(EXE): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@

# define the rule to clean the files
clean:
	rm -f $(EXE)
