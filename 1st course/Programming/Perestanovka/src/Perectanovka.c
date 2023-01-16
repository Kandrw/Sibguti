#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Perectanovka.h"
//Копирование строки и возвращение новой
char* copy_str(char *str){
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
//Алгоритм перестановки
char *Perectanovka(char *text, char *key){
    int N1 = 0, N2 = 0;
    //Подсчет длины текста
    while(text[N1] != '\0')
        ++N1;
    ++N1;//если считать '\0'
    //Подсчет длины ключа шифра
    while(key[N2] != '\0')
        ++N2;   
    if(N2 < 2){
        printf("Error: shifr ne srabotaet\n");//Слишком короткое слово
        return NULL;
    }
    if(N1 < 2){
         printf("Error: len(text) = 1\n");//Слишком короткий ключ
        return NULL;
    }
    //printf("N1 = %d, N2 = %d\n", N1, N2);
    int y;
    //Проверка построения таблицы, то есть хватает ли длинны слова или ключа
    if((N1-1) % N2 == 0)
        y = N1/N2;
    else{
        printf("Error create tabl\n");
        int dy = N2;
        while((N1-1) % dy != 0)
            dy++;
        printf("Ne hvataet symbol key: %d\n", dy-N2);//Сколлько символов не хватает в ключе для работо-ти
        return NULL;
    }
    ++y;//Длинна СТОЛБЦА с учетом '\0'
    char *tabl[N2];//таблица
    int *lens = (int*)malloc(sizeof(int) * N2);//индексы для заполнения таблицы, нужно при заполнение
    int i, i2;
    for(i = 0; i < N2; ++i){
        tabl[i] = (char*)malloc(sizeof(char) * y);//выделение памяти для каждого столбца
        lens[i] = 0;//зануление
    }
    i2 = 0;
    //Заполение таблицы по столбцу
    //символы слова попадают по очередно
    for(i = 0; i < N1-1; ++i){
        tabl[i2][lens[i2]] = text[i];
        lens[i2]++;//длинна конкретного столбца, увеличивается
        i2++;//слудующий столбец
        if(i2 % N2 == 0){//Конец таблицы, столбцы снова заполняются, но уже длинны другая
            i2 = 0;
        }
    }
    for(i = 0; i < N2; ++i){
        tabl[i][lens[i]] = '\0';//добавление конца в каждый столбец таблицы
    }
    char p, *ptr;
    char *key2 = copy_str(key);//Копирование ключа
    //Пузырьковая сортировка ключа, и смена столбцов в таблицы по ключу
    for(i = N2 - 1; i >= 0; --i){
        for(i2 = 0; i2 < i; ++i2){
            if(key2[i2] > key2[i2 + 1]){
                p = key2[i2];
                key2[i2] = key2[i2+1];
                key2[i2+1] = p;
                ptr = tabl[i2];
                tabl[i2] = tabl[i2+1];
                tabl[i2+1] = ptr;
            }
        }
    }
    char *shifrtext = (char*)malloc(sizeof(char) * N1);//Здесь будет хранитбся зашифрованный текст
    i2 = 0;
    int i3 = 0;
    //Записывание всех столбцов в зашифр слово по очередно
    for(i = 0; i < N1-1; i++){
        //Здесь записывается
        if(tabl[i2][i3] != '\0'){
            shifrtext[i] = tabl[i2][i3];
            ++i3;
        }
        //Заодно очищаем таблицу
        else{
            free(tabl[i2]);
            i--;
            i2++;
            i3 = 0;
        }
    }
    //Очистка
    free(tabl[i2]);
    free(tabl);    
    free(key2); 
    free(lens);
    shifrtext[i] = '\0';//Знак конца
    return shifrtext;
}