#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "DePerectanovka.h"

//Копирование строки и возвращение новой
char* copy_str1(char *str){
	int i = 0;
	while(str[i] != '\0')
		++i;
	char *newstr = (char*)malloc(sizeof(char) * (i+1));//Новая строка
	i = 0;
	while(str[i] != '\0'){
		newstr[i] = str[i]; ++i;
	} 
	newstr[i] = '\0';//Конец строки
	return newstr;
}

//Алгоритм дешифровки перестановки
char *DePerestanovka(char *shifrtext, char *key){
    int N1 = 0, N2 = 0;
    //Подсчет длинны
    while(shifrtext[N1] != '\0')
        ++N1;
    ++N1;
    while(key[N2] != '\0')
        ++N2;   
    if(N2 < 2){
        printf("Error: shifr ne srabotaet\n");
        return NULL;
    }
    if(N1 < 2){
         printf("Error: len(text) = 1\n");
        return NULL;
    }
    //printf("N1 = %d, N2 = %d\n", N1, N2);
    if((N1-1) % N2 != 0){
        printf("Error create tabl\n");
        return NULL;
    }
    //размер столбца
    //Внимание: здесь нет проверки на то что таблица полностью заполняется, т.к. проверка уже осуществяется в Perestanovka, и предпологается что алгоритм используется после предыдущего алгоритма
    int y = N1/N2 + 1;
    char *tabl[N2];//таблица
    int i, i2, i3;
    //выделение памяти в таблицы
    for(i = 0; i < N2; ++i)
        tabl[i] = (char*)malloc(sizeof(char) * y);
    i2 = 0; i3 = 0;
    //Заполение таблицы
    for(i = 0; i < N1-1; ++i){
        tabl[i2][i3] = shifrtext[i];
        ++i3;
        if(i3 == y-1){//Конец столбца
            tabl[i2][i3+1] = '\0';
            i2++;//Переход в другой, с начала
            i3 = 0;
        }
    }
    char *key2 = copy_str1(key), p;//копр ключ
    //сортировка ключа пузырьковой сорт
    for(i = N2 - 1; i >= 0; --i){
        for(i2 = 0; i2 < i; ++i2){
            if(key2[i2] > key2[i2 + 1]){
                p = key2[i2];
                key2[i2] = key2[i2+1];
                key2[i2+1] = p;
            }
        }
    }
    char *ptr;
    char *tabl2[N2];//новая таблица, без выделениея памяти, элементы берутся из первой таблицы, только порядок другой
    //Работает с помощью ключа и его отсортированной версии
    for(i = 0; i < N2; ++i){
        for(i2 = 0; i2 < N2; ++i2){
            if(key[i] == key2[i2])
                tabl2[i] = tabl[i2];
        }
    }
    char *detext = (char*)malloc(sizeof(char) * N1);//расшифрованный текст
    i3 = 0;
    //Просто обход 2 таблицы и сбор их в слово
    for(i = 0; i < y-1; ++i){
        for(i2 = 0; i2 < N2; ++i2){
            detext[i3] = tabl2[i2][i];
            ++i3;
        }
    }
    detext[i3] = '\0';
    //Очистка
    for(i = 0; i < N2; ++i)
        free(tabl[i]);
    free(tabl);
    free(tabl2);
    free(key2);
    return detext;
}