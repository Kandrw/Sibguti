@echo off

gcc -c Kyrsovik11.c -o Kyrsovik11.o
gcc -c Polibi.c -o Polibi.o
gcc -c DePolibi.c -o DePolibi.o

gcc -o Program Kyrsovik11.o Polibi.o DePolibi.o
Program

