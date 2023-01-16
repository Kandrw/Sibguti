#include <stdlib.h>
#include <stdio.h>

#include "Func.h"
#include "DeKeyCezar.h"
//Дешифровка текста
//На вход падается ключ-алфавит, зашифрованный текст, его длинна и язык текста и алфавита(1 или 0)
//Пребор осуществляется также как и зашифровке, только перебирается ключ-алфавит, находится в нем позиции и по этой позиции берется символ из обычного алфавита 
char2 **DeKeyCezar(char2 **alp1, char2 **alp2 , char2 **text){
    int N = 0;
    while(text[N] != NULL){
        ++N;
    }
    ++N;
    char2 **detext = (char2**)malloc(sizeof(char2*) * N);
    detext[N-1] = NULL;
    int i = 0, i2;
    while(text[i] != NULL){
        i2 = 0;
        while(alp1[i2] != NULL){
            if(text[i]->s1 == alp2[i2]->s1 && text[i]->s2 == alp2[i2]->s2){
                detext[i] = (char2*)malloc(sizeof(char2));
                detext[i]->s1 = alp1[i2]->s1;
                detext[i]->s2 = alp1[i2]->s2;
                break;
            }
            i2++;
        }
        i++;
    }
    return detext;
}