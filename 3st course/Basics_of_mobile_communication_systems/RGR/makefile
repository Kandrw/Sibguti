

SRC = 
FLG = -lm
PROGRAM = 
CC = gcc
FORMAT = c
VAR = 
.PHONY: $(SRC)
all: main #$(SRC)
main: $(SRC)
	$(CC) -o $(PROGRAM) $(VAR) -lm $^
#	gcc -o $(basename $@) $(FLG)  $@
%.o: %.$(FORMAT)
	$(CC) $< -c -o $@
