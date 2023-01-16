@echo off
del *.o
gcc -c K2.c
gcc -c Bigramm.c
gcc -c DeBigramm.c
gcc -c Func.c
del Program
gcc -o Program K2.o Func.o Bigramm.o DeBigramm.o

rem Program test2.txt keyru.txt

rem Program test1.txt runs res1.txt
