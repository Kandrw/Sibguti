@echo off


gcc -c Perectanovka.c -o Perectanovka.o
gcc -c DePerectanovka.c -o DePerectanovka.o
gcc -c Kyrsovik12.c -o Kyrsovik12.o

gcc -o Program Kyrsovik12.o Perectanovka.o DePerectanovka.o 
del *.o
rem Program