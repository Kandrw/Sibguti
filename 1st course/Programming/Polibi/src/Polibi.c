#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Polibi.h"

//Создание ключа, то есть таблицы и ключа(на вход)
//Результат структура с размером код слова и его самого и таблица
key *GenerateKey(char *sl){
    int i, i2;
    int a = 0;
    int n = 6;//Таблица 6x6

    while(sl[a] != '\0'){//Длина кодового слова
        a++;
    }
    a++;
    if(a < n+1){
        printf("Error: len slovo < 6\n");
        return NULL;
    }
    key *K = (key*)malloc(sizeof(key));//Где будет храниться код слова длинна и таблица
    K->slovo = (char*)malloc(sizeof(char) * (n+1));
    K->kvad = (char*)malloc(sizeof(char) * n*n + 1);
    for(i = 0; i < n+1; ++i)//Запись кодового слова в структуру
        K->slovo[i] = sl[i];
    //Создание таблицы из англ алфавита
    for(i = 65, i2 = 0; i < 91; i++, i2++){
        K->kvad[i2] = i;
    }
    K->a = n;
    //Также добавляется еще символы чтоб размер был 6X6
    K->kvad[i2++] = ' '; K->kvad[i2++] = '.';
    K->kvad[i2++] = ','; K->kvad[i2++] = '!';
    K->kvad[i2++] = '?'; K->kvad[i2++] = '-';
    K->kvad[i2++] = ';'; K->kvad[i2++] = '\n';
    K->kvad[i2++] = ':'; K->kvad[i2++] = '&';
    K->kvad[i2++] = '\0';
    //Просто печать таблицы
    printf("   ");
    for(i = 0; i < K->a; i++)
        printf("%2c ", K->slovo[i]);
    printf("\n");
    for(i = 0; i < K->a; i++){
        printf("%c  ", K->slovo[i]);
        for(i2 = 0; i2 < K->a; i2++){
            if(K->kvad[i*K->a + i2] == '\n')
                printf(" \\n");
            else
                printf("%2c ", K->kvad[i * K->a + i2]);
            
        }
        printf("\n");
    }
    printf("--------------\n");
    return K;
}
//Шифр Полибия
char* Polibi(char *text, key *K){
    int N = 0, i, i2, i3, i4;
    while(text[N] != '\0')
        ++N;
    char *shifrtext = (char *)malloc(sizeof(char) * (N*2) + 1);//здесь будет храниться зашивр слово
    for(i = 0, i3 = 0; i < N; i++, i3+=2){//Обход слова и зашифр слова для заполнения
        //Обход таблицы, то есть квадрата
        for(i2 = 0; i2 < K->a; i2++){
            for(i4 = 0; i4 < K->a; i4++){
                if(text[i] == K->kvad[i2 * K->a + i4]){
                    shifrtext[i3] = K->slovo[i2];//Заполение зашифр слова, буква 1 (вертикально)
                    shifrtext[i3+1] = K->slovo[i4];//Заполение зашифр слова, буква 2 (горизонтально)
                    break;
                }
            }
        }
    }
    shifrtext[i3] = '\0';//Конец слова, не учитывается при расшифровке
    return shifrtext;
}

