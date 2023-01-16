@echo off
gcc -c translate.c -o translate.o
del Program
gcc -o translate translate.o
del *.o
rem translate text_ru.txt Dictionary3.txt r1.txt