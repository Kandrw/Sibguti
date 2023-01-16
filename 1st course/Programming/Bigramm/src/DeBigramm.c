#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Func.h"
//Дешифрование
char* DeBigramm(char *detext, char *tabl){
    int n = 0;
    int i = 0, i2;
    while(tabl[n] != '\0'){
        n++;
    }
    n++;
    int at = sqrt(n);
    while(detext[i] != '\0')
        ++i;
    int N = i+1;
    char *text = (char*)malloc(sizeof(char) * N);//текст расшифр
    text[N-1] = '\0';
    //printf("N = %d\n",N);
    i = 0;
    int k1, k2;
    //Перебор 
    while(detext[i] != '\0'){
        //Получение кода из таблицы
        for(i2 = 0; i2 < n-1; ++i2){
            if(detext[i] == tabl[i2])
                k1 = i2;
            if(detext[i+1] == tabl[i2])
                k2 = i2;
        }
        if(detext[i+1] == '\0')
            k2 = -1;
        //Два одинак  символа
        if(k2 == -1){
            k1-=at;
            if( k1 < 0)
                k1 = n+k1-1;
            text[i] = tabl[k1];
            break;
        }
        else if(k1 == k2){
            k1-=at;
            k2-=at;
            if( k1 < 0)
                k1 = n+k1-1;
            if( k2 < 0)
                k2 = n+k2-1;
            text[i] = tabl[k1];
            text[i+1] = tabl[k1];
        }
        //код 1 символа меньше 2
        else if(k1 < k2){
            //В одной строке
            if(k2-k1 < at && k2-k1 > 0 && (k1 / at == k2 / at)){
                if((k1) % at == 0)
                    k1+=5;
                else
                    k1--;
                if((k2) % at == 0)
                    k2+=5;
                else
                    k2--;
                text[i] = tabl[k1];
                text[i+1] = tabl[k2];
            }
            //В одном столбце
            else if((k2-k1) % at == 0){
                k1-=at; k2-=at;
                if( k1 < 0)
                    k1 = n+k1-1;
                if( k2 < 0)
                    k2 = n+k2-1;
                text[i] = tabl[k1];
                text[i+1] = tabl[k2];
            }
            // не в строке и не встолбце
            else{
                if((k1 % at) < (k2 % at)){
                        int b1 = k1 + ((k2-k1)/at)*at;
                        int b2 = k1 + ((k2-k1)%at);
                        text[i] = tabl[b2];
                        text[i+1] = tabl[b1];
                    }
                if((k1 % at) > (k2 % at)){
                        int b1 = (k1/at)*at + (k2%at);
                        int b2 = (k2/at)*at + (k1%at);
                        text[i] = tabl[b1];
                        text[i+1] = tabl[b2];
                }
            }
        }
        //Наоборот
        else if(k1 > k2){
            //В одной строке
            if(k1-k2 < at && k1-k2 > 0 && (k1 / at == k2 / at)){
                //Если символ первый
                if((k1) % at == 0)
                    k1+=5;
                else
                    k1--;
                //Если символ первый
                if((k2) % at == 0)
                    k2+=5;
                else
                    k2--;
                text[i] = tabl[k1];
                text[i+1] = tabl[k2];
            }
            //В одном столбце
            else if((k1-k2) % at == 0){
                k1-=at;
                k2-=at;
                if( k1 < 0)
                    k1 = n+k1+1;          
                if( k2 < 0)
                    k2 = n+k2+1;
                text[i] = tabl[k1];
                text[i+1] = tabl[k2];
            }
            // не в строке и не встолбце
            else{
                
                if((k1 % at) > (k2 % at)){
                        int b1 = k2 + ((k1-k2)/at)*at;
                        int b2 = k2 + ((k1-k2)%at);
                        text[i] = tabl[b1];
                        text[i+1] = tabl[b2];
                }
                if((k1 % at) < (k2 % at)){
                        int b1 = (k1/at) * at + (k2%at);
                        int b2 = (k2/at) * at + (k1%at) ;
                        text[i] = tabl[b1];
                        text[i+1] = tabl[b2];
                }
            }
        }
        i+=2;
    }
    return text;
}
//Дешифрование
string** DeBigrammRU(string **detext, string **tabl){
    int n = 0;
    int i = 0, i2;
    while(tabl[n] != NULL){
        n++;
    }
    n++;
    int at = sqrt(n);
    while(detext[i] != NULL)
        ++i;
    int N = i+1;
    //char *text = (char*)malloc(sizeof(char) * N);//текст расшифр
    string **text = (string**)malloc(sizeof(string*) * N);
    text[N-1] = NULL;
    //printf("N = %d\n",N);
    i = 0;
    int k1, k2;
    //printf("|||||||||||||\n");
    //Перебор 
    while(detext[i] != NULL){
        //printf("i = %d\n", i);
        //Получение кода из таблицы

        for(i2 = 0; i2 < n-1; ++i2){
            if(detext[i]->c1 == tabl[i2]->c1 && detext[i]->c2 == tabl[i2]->c2)
                k1 = i2;
            if(detext[i+1] != NULL && detext[i+1]->c1 == tabl[i2]->c1 && detext[i+1]->c2 == tabl[i2]->c2 )
                k2 = i2;
        }
        if(detext[i+1] == NULL)
            k2 = -1;
        //Два одинак  символа
        if(k2 == -1){
            k1-=at;
            if( k1 < 0)
                k1 = n+k1-1;
            //printf("\\/\n");
            text[i] = (string*)malloc(sizeof(string));
            text[i]->c1 = tabl[k1]->c1;
            text[i]->c2 = tabl[k1]->c2;
            text[i]->ru_en = tabl[k1]->ru_en;
            //text[i] = tabl[k1];
            break;
        }
        else if(k1 == k2){
            k1-=at;
            k2-=at;
            if( k1 < 0)
                k1 = n+k1-1;
            if( k2 < 0)
                k2 = n+k2-1;

            text[i] = (string*)malloc(sizeof(string));
            text[i]->c1 = tabl[k1]->c1;
            text[i]->c2 = tabl[k1]->c2;
            text[i]->ru_en = tabl[k1]->ru_en;

            text[i+1] = (string*)malloc(sizeof(string));
            text[i+1]->c1 = tabl[k1]->c1;
            text[i+1]->c2 = tabl[k1]->c2;
            text[i+1]->ru_en = tabl[k1]->ru_en;
        }
        //код 1 символа меньше 2
        else if(k1 < k2){
            //В одной строке
            if(k2-k1 < at && k2-k1 > 0 && (k1 / at == k2 / at)){
                if((k1) % at == 0)
                    k1+=5;
                else
                    k1--;
                if((k2) % at == 0)
                    k2+=5;
                else
                    k2--;
                //text[i] = tabl[k1];
                //text[i+1] = tabl[k2];

                text[i] = (string*)malloc(sizeof(string));
                text[i]->c1 = tabl[k1]->c1;
                text[i]->c2 = tabl[k1]->c2;
                text[i]->ru_en = tabl[k1]->ru_en;

                text[i+1] = (string*)malloc(sizeof(string));
                text[i+1]->c1 = tabl[k2]->c1;
                text[i+1]->c2 = tabl[k2]->c2;
                text[i+1]->ru_en = tabl[k2]->ru_en;

            }
            //В одном столбце
            else if((k2-k1) % at == 0){
                k1-=at; k2-=at;
                if( k1 < 0)
                    k1 = n+k1-1;
                if( k2 < 0)
                    k2 = n+k2-1;
                //text[i] = tabl[k1];
                //text[i+1] = tabl[k2];

                text[i] = (string*)malloc(sizeof(string));
                text[i]->c1 = tabl[k1]->c1;
                text[i]->c2 = tabl[k1]->c2;
                text[i]->ru_en = tabl[k1]->ru_en;

                text[i+1] = (string*)malloc(sizeof(string));
                text[i+1]->c1 = tabl[k2]->c1;
                text[i+1]->c2 = tabl[k2]->c2;
                text[i+1]->ru_en = tabl[k2]->ru_en;
            }
            // не в строке и не встолбце
            else{
                
                if((k1 % at) < (k2 % at)){
                        int b1 = k1 + ((k2-k1)/at)*at;
                        int b2 = k1 + ((k2-k1)%at);
                        //text[i] = tabl[b2];
                        //text[i+1] = tabl[b1];

                        text[i] = (string*)malloc(sizeof(string) * N);
                        text[i]->c1 = tabl[b2]->c1;
                        text[i]->c2 = tabl[b2]->c2;
                        text[i]->ru_en = tabl[b2]->ru_en;
                
                        text[i+1] = (string*)malloc(sizeof(string) * N);
                        text[i+1]->c1 = tabl[b1]->c1;
                        text[i+1]->c2 = tabl[b1]->c2;
                        text[i+1]->ru_en = tabl[b1]->ru_en;

                    }
                if((k1 % at) > (k2 % at)){
                        int b1 = (k1/at)*at + (k2%at);
                        int b2 = (k2/at)*at + (k1%at);
                        //text[i] = tabl[b1];
                        //text[i+1] = tabl[b2];

                        text[i] = (string*)malloc(sizeof(string) * N);
                        text[i]->c1 = tabl[b1]->c1;
                        text[i]->c2 = tabl[b1]->c2;
                        text[i]->ru_en = tabl[b1]->ru_en;
                
                        text[i+1] = (string*)malloc(sizeof(string) * N);
                        text[i+1]->c1 = tabl[b2]->c1;
                        text[i+1]->c2 = tabl[b2]->c2;
                        text[i+1]->ru_en = tabl[b2]->ru_en;
                }
            }
        }
        //Наоборот
        else if(k1 > k2){
            //В одной строке
            if(k1-k2 < at && k1-k2 > 0 && (k1 / at == k2 / at)){
                //Если символ первый
                if((k1) % at == 0)
                    k1+=5;
                else
                    k1--;
                //Если символ первый
                if((k2) % at == 0)
                    k2+=5;
                else
                    k2--;
                //text[i] = tabl[k1];
                //text[i+1] = tabl[k2];
                text[i] = (string*)malloc(sizeof(string));
                text[i]->c1 = tabl[k1]->c1;
                text[i]->c2 = tabl[k1]->c2;
                text[i]->ru_en = tabl[k1]->ru_en;

                text[i+1] = (string*)malloc(sizeof(string));
                text[i+1]->c1 = tabl[k2]->c1;
                text[i+1]->c2 = tabl[k2]->c2;
                text[i+1]->ru_en = tabl[k2]->ru_en;
            }
            //В одном столбце
            else if((k1-k2) % at == 0){
                k1-=at;
                k2-=at;
                if( k1 < 0)
                    k1 = n+k1+1;          
                if( k2 < 0)
                    k2 = n+k2+1;
                
                //text[i] = tabl[k1];
                //text[i+1] = tabl[k2];
                text[i] = (string*)malloc(sizeof(string));
                text[i]->c1 = tabl[k1]->c1;
                text[i]->c2 = tabl[k1]->c2;
                text[i]->ru_en = tabl[k1]->ru_en;

                text[i+1] = (string*)malloc(sizeof(string));
                text[i+1]->c1 = tabl[k2]->c1;
                text[i+1]->c2 = tabl[k2]->c2;
                text[i+1]->ru_en = tabl[k2]->ru_en;

            }
            // не в строке и не встолбце
            else{
                
                if((k1 % at) > (k2 % at)){
                        int b1 = k2 + ((k1-k2)/at)*at;
                        int b2 = k2 + ((k1-k2)%at);
                        //text[i] = tabl[b1];
                        //text[i+1] = tabl[b2];
                        text[i] = (string*)malloc(sizeof(string) * N);
                        text[i]->c1 = tabl[b1]->c1;
                        text[i]->c2 = tabl[b1]->c2;
                        text[i]->ru_en = tabl[b1]->ru_en;
                
                        text[i+1] = (string*)malloc(sizeof(string) * N);
                        text[i+1]->c1 = tabl[b2]->c1;
                        text[i+1]->c2 = tabl[b2]->c2;
                        text[i+1]->ru_en = tabl[b2]->ru_en;
                }
                if((k1 % at) < (k2 % at)){
                        int b1 = (k1/at) * at + (k2%at);
                        int b2 = (k2/at) * at + (k1%at) ;
                        //text[i] = tabl[b1];
                        //text[i+1] = tabl[b2];

                        text[i] = (string*)malloc(sizeof(string) * N);
                        text[i]->c1 = tabl[b1]->c1;
                        text[i]->c2 = tabl[b1]->c2;
                        text[i]->ru_en = tabl[b1]->ru_en;
                
                        text[i+1] = (string*)malloc(sizeof(string) * N);
                        text[i+1]->c1 = tabl[b2]->c1;
                        text[i+1]->c2 = tabl[b2]->c2;
                        text[i+1]->ru_en = tabl[b2]->ru_en;
                }
            }
        }
        i+=2;
    }
    return text;
}