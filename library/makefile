# define the name of the library
LIBNAME = libmylib.a

# define the source and header files
SRC = src/lib.c
HDR = include/lib.h

# define the object file
OBJ = $(SRC:.c=.o)

# define the compiler and the flags
CC = gcc
CFLAGS = -Wall -Iinclude

# define the rule to create the library
$(LIBNAME): $(OBJ)
	ar rcs $@ $^

# define the rule to compile the source file
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# define the rule to clean the files
clean:
	rm -f $(OBJ) $(LIBNAME)
