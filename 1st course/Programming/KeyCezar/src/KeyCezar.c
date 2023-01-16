#include <stdlib.h>
#include <stdio.h>
#include "Func.h"
#include "KeyCezar.h"
//Шифр цезаря
//На вход падается ключ-алфавит, шифруемый текст, его длинна и язык текст и алфавита(1 или 0)
char2 **KeyCezar(char2 **alp1, char2 **alp2 , char2 **text){

    int N = 0;
    while(text[N] != NULL){
        ++N;
    }
    ++N;
    char2 **text2 = (char2**)malloc(sizeof(char2*) * N);
    text2[N-1] = NULL;
    int i = 0, i2;
    while(text[i] != NULL){
        i2 = 0;
        while(alp1[i2] != NULL){
            if(text[i]->s1 == alp1[i2]->s1 && text[i]->s2 == alp1[i2]->s2){
                text2[i] = (char2*)malloc(sizeof(char2));
                text2[i]->s1 = alp2[i2]->s1;
                text2[i]->s2 = alp2[i2]->s2;
                break;
            }
            i2++;
        }
        i++;
    }
    return text2;
}