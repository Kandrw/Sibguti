#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Func.h"
//Шифрование
char *Bigramm(char *text, char *tabl){
    int n = 0;
    //Длинна таблицы
    int i = 0, i2;
    while(tabl[n] != '\0'){
        n++;
    }
    n++;
    int at = sqrt(n);//Размер таблицы(коли-во столбцов)
    //подсчет длинны
    while(text[i] != '\0')
        ++i;
    int N = i+1;//для '\0'
    char *detext = (char*)malloc(sizeof(char) * N);//новый тект
    detext[N-1] = '\0';
    //printf("N = %d\n",N);
    i = 0;
    int k1, k2;
    while(text[i] != '\0'){
        //Если имеется два символа
        if(text[i+1] != '\0'){
            //Получение кода из таблицы
            for(i2 = 0; i2 < n-1; ++i2){
                if(text[i] == tabl[i2])
                    k1 = i2;
                if(text[i+1] == tabl[i2])
                    k2 = i2;
            }
            if(k1 == k2){
                for(i2 = 0; i2 < n-1; ++i2){
                    if(text[i] == tabl[i2])
                        k1 = i2;                    
                }
                k1+=at;
                if(k1 >= n-1)
                    k1 = k1-n+1;//если в последней строчке
                detext[i] = tabl[k1];
                detext[i+1] = tabl[k1];
            }
            // 1 случай: код 1 символа меньше второго
            else if(k1 < k2){
                // в одной строке
                if(k2-k1 < at && k2-k1 > 0 && (k1 / at == k2 / at)){
                    //Если символ последний
                    if((k1+1) % at == 0)
                        k1 -=5;
                    else
                        k1++;
                    //Если символ последний
                    if((k2+1) % at == 0)
                        k2 -=5;
                    else   
                        k2++;
                    detext[i] = tabl[k1];
                    detext[i+1] = tabl[k2];
                }
                //в одном столбце
                else if((k2-k1) % at == 0){
                    k1+=at;
                    k2+=at;
                    if(k1 >= n-1)
                        k1 = k1-n+1;                   
                    if(k2 >= n-1)
                        k2 = k2-n+1;    
                    detext[i] = tabl[k1];
                    detext[i+1] = tabl[k2];
                }           
                // не в строке и не встолбце
                else{
                    if((k1 % at) < (k2 % at)){
                        int b1 = k1 + ((k2-k1)/at)*at;
                        int b2 = k1 + ((k2-k1)%at);
                        detext[i] = tabl[b2];
                        detext[i+1] = tabl[b1];
                    }
                    if((k1 % at) > (k2 % at)){
                        int b1 = (k1/at)*at + (k2%at);
                        int b2 = (k2/at)*at + (k1%at);
                        detext[i] = tabl[b1];
                        detext[i+1] = tabl[b2];
                    }
                }
            }
            //наоборот
            else if(k1 > k2){
                // в одной строке
                if(k1-k2 < at && k1-k2 > 0 && (k1 / at == k2 / at)){
                    //Если символ последний
                    if((k1+1) % at == 0)
                        k1 -=5;
                    else
                        k1++;
                    //Если символ последний
                    if((k2+1) % at == 0)
                        k2 -=5;
                    else   
                        k2++;
                    detext[i] = tabl[k1];
                    detext[i+1] = tabl[k2];
                }
                // в одном столбце
                else if((k1-k2) % at == 0){
                    k1+=at;
                    k2+=at;
                    if(k1 >= n-1)
                        k1 = k1-n+1;
                    if(k2 >= n-1)
                        k2 = k2-n+1;
                    detext[i] = tabl[k1];
                    detext[i+1] = tabl[k2];
                }
                // не в строке и не встолбце
                else{
                    if((k1 % at) > (k2 % at)){
                        int b1 = k2 + ((k1-k2)/at)*at;
                        int b2 = k2 + ((k1-k2)%at);
                        detext[i] = tabl[b1];
                        detext[i+1] = tabl[b2];
                    }
                    else if((k1 % at) < (k2 % at)){
                        int b1 = (k1/at) * at + (k2%at);
                        int b2 = k2/at * at + (k1%at);   
                        detext[i] = tabl[b1];
                        detext[i+1] = tabl[b2];
                    }
                }
            }
        }
        //Если остался только 1 символ или 2 одинаковых, то есть будут два одинаковых
        else{         
            for(i2 = 0; i2 < n-1; ++i2){
                if(text[i] == tabl[i2])
                    k1 = i2;
            }
            k1+=at;
            if(k1 >= n-1)
                k1 = k1-n+1;//если в последней строчке
            detext[i] = tabl[k1];
            break;
        }
        i+=2;
    }
    return detext;
}

//Шифрование
string **BigrammRU(string **text, string **tabl){
    int n = 0;
    
    //Длинна таблицы
    int i = 0, i2;
    while(tabl[n] != NULL){
        n++;
    }
    n++;
    int at = sqrt(n);//Размер таблицы(коли-во столбцов)
    //подсчет длинны
    while(text[i] != NULL)
        ++i;
    int N = i+1;//для '\0'
    string **detext = (string**)malloc(sizeof(string*) * N);//новый тект
    detext[N-1] = NULL;
    //printf("N = %d\n",N);
    i = 0;
    int k1, k2;
    while(text[i] != NULL){
        //Если имеется два символа
        if(text[i+1] != NULL){
            for(i2 = 0; i2 < n-1; ++i2){
                if(text[i]->c1 == tabl[i2]->c1 && text[i]->c2 == tabl[i2]->c2)
                    k1 = i2;
                if(text[i+1]->c1 == tabl[i2]->c1 && text[i+1]->c2 == tabl[i2]->c2)
                    k2 = i2;
            }
            //printf("k1 = %d, k2 = %d>\n", k1, k2);
            if(k1 == k2){
                for(i2 = 0; i2 < n-1; ++i2){
                    if(text[i]->c1 == tabl[i2]->c1 && text[i]->c2 == tabl[i2]->c2)
                        k1 = i2;                    
                }
                k1+=at;
                if(k1 >= n-1)
                    k1 = k1-n+1;//если в последней строчке
                detext[i] = (string*)malloc(sizeof(string) * N);
                detext[i]->c1 = tabl[k1]->c1;
                detext[i]->c2 = tabl[k1]->c2;
                detext[i]->ru_en = tabl[k1]->ru_en;
                
                detext[i+1] = (string*)malloc(sizeof(string) * N);
                detext[i+1]->c1 = tabl[k1]->c1;
                detext[i+1]->c2 = tabl[k1]->c2;
                detext[i+1]->ru_en = tabl[k1]->ru_en;
                
                
            }
            // 1 случай: код 1 символа меньше второго
            else if(k1 < k2){
                // в одной строке
                if(k2-k1 < at && k2-k1 > 0 && (k1 / at == k2 / at)){
                    //Если символ последний
                    if((k1+1) % at == 0)
                        k1 -=5;
                    else
                        k1++;
                    //Если символ последний
                    if((k2+1) % at == 0)
                        k2 -=5;
                    else   
                        k2++;
                    detext[i] = (string*)malloc(sizeof(string) * N);
                    detext[i]->c1 = tabl[k1]->c1;
                    detext[i]->c2 = tabl[k1]->c2;
                    detext[i]->ru_en = tabl[k1]->ru_en;
                
                    detext[i+1] = (string*)malloc(sizeof(string) * N);
                    detext[i+1]->c1 = tabl[k2]->c1;
                    detext[i+1]->c2 = tabl[k2]->c2;
                    detext[i+1]->ru_en = tabl[k2]->ru_en;
                }
                //в одном столбце
                else if((k2-k1) % at == 0){
                    k1+=at;
                    k2+=at;
                    if(k1 >= n-1)
                        k1 = k1-n+1;                   
                    if(k2 >= n-1)
                        k2 = k2-n+1;    
                    detext[i] = (string*)malloc(sizeof(string) * N);
                    detext[i]->c1 = tabl[k1]->c1;
                    detext[i]->c2 = tabl[k1]->c2;
                    detext[i]->ru_en = tabl[k1]->ru_en;
                
                    detext[i+1] = (string*)malloc(sizeof(string) * N);
                    detext[i+1]->c1 = tabl[k2]->c1;
                    detext[i+1]->c2 = tabl[k2]->c2;
                    detext[i+1]->ru_en = tabl[k2]->ru_en;
                }           
                // не в строке и не встолбце
                else{
                    if((k1 % at) < (k2 % at)){
                        int b1 = k1 + ((k2-k1)/at)*at;
                        int b2 = k1 + ((k2-k1)%at);
                        //detext[i] = tabl[b2];
                        //detext[i+1] = tabl[b1];
                        detext[i] = (string*)malloc(sizeof(string) * N);
                        detext[i]->c1 = tabl[b2]->c1;
                        detext[i]->c2 = tabl[b2]->c2;
                        detext[i]->ru_en = tabl[b2]->ru_en;
                
                        detext[i+1] = (string*)malloc(sizeof(string) * N);
                        detext[i+1]->c1 = tabl[b1]->c1;
                        detext[i+1]->c2 = tabl[b1]->c2;
                        detext[i+1]->ru_en = tabl[b1]->ru_en;
                    }
                    if((k1 % at) > (k2 % at)){
                        int b1 = (k1/at)*at + (k2%at);
                        int b2 = (k2/at)*at + (k1%at);
                        //detext[i] = tabl[b1];
                        //detext[i+1] = tabl[b2];
                        detext[i] = (string*)malloc(sizeof(string) * N);
                        detext[i]->c1 = tabl[b1]->c1;
                        detext[i]->c2 = tabl[b1]->c2;
                        detext[i]->ru_en = tabl[b1]->ru_en;
                
                        detext[i+1] = (string*)malloc(sizeof(string) * N);
                        detext[i+1]->c1 = tabl[b2]->c1;
                        detext[i+1]->c2 = tabl[b2]->c2;
                        detext[i+1]->ru_en = tabl[b2]->ru_en;
                    }
                }
            }
            //наоборот
            else if(k1 > k2){
                // в одной строке
                if(k1-k2 < at && k1-k2 > 0 && (k1 / at == k2 / at)){
                    //Если символ последний
                    if((k1+1) % at == 0)
                        k1 -=5;
                    else
                        k1++;
                    //Если символ последний
                    if((k2+1) % at == 0)
                        k2 -=5;
                    else   
                        k2++;
                    detext[i] = (string*)malloc(sizeof(string) * N);
                    detext[i]->c1 = tabl[k1]->c1;
                    detext[i]->c2 = tabl[k1]->c2;
                    detext[i]->ru_en = tabl[k1]->ru_en;
                
                    detext[i+1] = (string*)malloc(sizeof(string) * N);
                    detext[i+1]->c1 = tabl[k2]->c1;
                    detext[i+1]->c2 = tabl[k2]->c2;
                    detext[i+1]->ru_en = tabl[k2]->ru_en;
                    //detext[i] = tabl[k1];
                    //detext[i+1] = tabl[k2];
                }
                // в одном столбце
                else if((k1-k2) % at == 0){
                    k1+=at;
                    k2+=at;
                    if(k1 >= n-1)
                        k1 = k1-n+1;
                    if(k2 >= n-1)
                        k2 = k2-n+1;
                    //detext[i] = tabl[k1];
                    //detext[i+1] = tabl[k2];
                    detext[i] = (string*)malloc(sizeof(string) * N);
                    detext[i]->c1 = tabl[k1]->c1;
                    detext[i]->c2 = tabl[k1]->c2;
                    detext[i]->ru_en = tabl[k1]->ru_en;
                
                    detext[i+1] = (string*)malloc(sizeof(string) * N);
                    detext[i+1]->c1 = tabl[k2]->c1;
                    detext[i+1]->c2 = tabl[k2]->c2;
                    detext[i+1]->ru_en = tabl[k2]->ru_en;
                }
                // не в строке и не встолбце
                else{
                    if((k1 % at) > (k2 % at)){
                        int b1 = k2 + ((k1-k2)/at)*at;
                        int b2 = k2 + ((k1-k2)%at);
                        //detext[i] = tabl[b1];
                        //detext[i+1] = tabl[b2];
                        detext[i] = (string*)malloc(sizeof(string) * N);
                        detext[i]->c1 = tabl[b1]->c1;
                        detext[i]->c2 = tabl[b1]->c2;
                        detext[i]->ru_en = tabl[b1]->ru_en;
                
                        detext[i+1] = (string*)malloc(sizeof(string) * N);
                        detext[i+1]->c1 = tabl[b2]->c1;
                        detext[i+1]->c2 = tabl[b2]->c2;
                        detext[i+1]->ru_en = tabl[b2]->ru_en;

                    }
                    else if((k1 % at) < (k2 % at)){
                        int b1 = (k1/at) * at + (k2%at);
                        int b2 = k2/at * at + (k1%at);   
                        //detext[i] = tabl[b1];
                        //detext[i+1] = tabl[b2];
                        detext[i] = (string*)malloc(sizeof(string) * N);
                        detext[i]->c1 = tabl[b1]->c1;
                        detext[i]->c2 = tabl[b1]->c2;
                        detext[i]->ru_en = tabl[b1]->ru_en;
                
                        detext[i+1] = (string*)malloc(sizeof(string) * N);
                        detext[i+1]->c1 = tabl[b2]->c1;
                        detext[i+1]->c2 = tabl[b2]->c2;
                        detext[i+1]->ru_en = tabl[b2]->ru_en;
                        
                    }
                }
            }
        }
        //Если остался только 1 символ или 2 одинаковых, то есть будут два одинаковых
        else{         
            for(i2 = 0; i2 < n-1; ++i2){
                if(text[i]->c1 == tabl[i2]->c1 && text[i]->c2 == tabl[i2]->c2 )
                    k1 = i2;
            }
            k1+=at;
            if(k1 >= n-1)
                k1 = k1-n+1;//если в последней строчке
            //detext[i] = tabl[k1];
            detext[i] = (string*)malloc(sizeof(string) * N);
            detext[i]->c1 = tabl[k1]->c1;
            detext[i]->c2 = tabl[k1]->c2;
            detext[i]->ru_en = tabl[k1]->ru_en;

            break;
        }
        i+=2;
    }
    return detext;
}




