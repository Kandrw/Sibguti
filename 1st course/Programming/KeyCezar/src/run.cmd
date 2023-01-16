@echo off

gcc -c KeyCezar.c -o KeyCezar.o
gcc -c DeKeyCezar.c -o DeKeyCezar.o
gcc -c Func.c -o Func.o
gcc -c K2.c -o K2.o 


del Program
gcc -o Program K2.o Func.o KeyCezar.o DeKeyCezar.o

rem Запуск с передачей файлов на вход программы
rem Program test1.txt keyru.txt 4 res1.txt
rem Program test2.txt keyen.txt 4 res2.txt

del *.o