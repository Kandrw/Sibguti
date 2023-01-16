@echo off

gcc -c Func.c
gcc -c naive_alg.c
gcc -c MITM.c

gcc -c Kyrsovik.c
del Kyrsovik.exe
gcc -o Kyrsovik *.o
del *.o



