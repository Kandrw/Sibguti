#include <stdio.h>
#include <stdlib.h>
#include "DePolibi.h"
#include "Polibi.h"
//Расшифровка Полибия
char *DePolibi(char *shifrtext, key* K){
    int i, i2, i3;
    int k1, k2, N = 0;
    while(shifrtext[N] != '\0')//Подсчет длинны зашифрованнго слова
        ++N;
    ++N;
    char *rasshifrtext = (char*)malloc(sizeof(char) * (N/2) + 1);//Расшифрованнное слово
    for(i = 0, i3 = 0; i < N, i3 < N/2; i += 2, ++i3){//Обход зашифр(+=2) и расшифр слова(+=1)
        //Получение положение в кодовом слове
        for(i2 = 0; i2 < K->a; ++i2){
            if(K->slovo[i2] == shifrtext[i])
                k1 = i2;
            if(K->slovo[i2] == shifrtext[i+1])
                k2 = i2;
        }
        rasshifrtext[i3] = K->kvad[k1 * K->a + k2];// позиция в таблицы как kvad[k1][k2]
    }
    rasshifrtext[i3] = '\0';
    return rasshifrtext;//Результат расшифрованное слово
}