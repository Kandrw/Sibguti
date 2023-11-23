
@echo off
del item1.exe item2.exe item4.exe
g++ item1.cpp -o item1 -lm
g++ item2.cpp -o item2 -lm
g++ item4.cpp -o item4 -lm


item1.exe
item2.exe
item4.exe



