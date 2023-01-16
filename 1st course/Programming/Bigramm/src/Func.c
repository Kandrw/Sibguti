
#include <stdio.h>
#include <stdlib.h>
#include "Func.h"

int Search(char *text, int st, int end, char c ){
    int i = st;
    for(; i < end; ++i){
        if(text[i] == c)
            return 1;
    }
    return 0;
}
int Search2(char *text, char c1, char c2){
    int i = 0;
    while(text[i] != '\0'){
        if(text[i] < 0){
            if(text[i] == c1 && text[i+1] == c2){
                return 1;
            }
            i+=2;
        }
        else{
            if(text[i] == c1)
                return 1;
            ++i;
        }
        
    }
    return 0;
}
char *CreateEN(char *fr){
    char *en = "abcdefghijklm\nnopqrstuvwxyz .,!?:;()";
    int y = 0;
    while(en[y] != '\0'){
        y++;
    }
    printf("y = %d\n",y);
        if(fr == NULL)
            return en;
        char *tabl = (char*)malloc(sizeof(char) * 37);
        tabl[36] = '\0';
        int i, i2;
        i = 0;
        while(fr[i] != '\0'){
            tabl[i] = fr[i];
            ++i;
        }
        i2 = 0;
        while(en[i2] != '\0' && i < 36){
            if(Search(tabl, 0, i, en[i2]) == 0){
                tabl[i] = en[i2];
                ++i;
            }
            i2++;
        }
        return tabl;
}
string **CreateRU(char *fr){
    char *ru = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя ,\n";
    string **RU = (string**)malloc(sizeof(string*) * 37);
    RU[36] = NULL;
        
    int i = 0, i2 = 0, k1 = 0;
    unsigned char c, c2;
    if(fr == NULL){
        while(ru[i] != '\0'){
            c = ru[i];
            if(k1 == 1){
                RU[i2]->c2 = c;
                ++i2;
                k1 = 0;
            }
            else if(c ==208 || c == 209 || c == 210){
                k1 = 1;
                RU[i2] = (string*)malloc(sizeof(string));
                RU[i2]->c1 = c;
                RU[i2]->ru_en = 1;
            }
            else{
                RU[i2] = (string*)malloc(sizeof(string));
                RU[i2]->c1 = c;
                RU[i2]->c2 = 0;
                RU[i2]->ru_en = 0;
                ++i2;
            }
            ++i;
        }
        printf("N = %d\n",i);
        return RU;
    }
    else{
        while(fr[i] != '\0'){
            c = fr[i];
            if(k1 == 1){
                RU[i2]->c2 = c;
                ++i2;
                k1 = 0;
            }
            else if(c == 208 || c == 209 || c == 210){
                RU[i2] = (string*)malloc(sizeof(string));
                RU[i2]->c1 = c;
                RU[i2]->ru_en = 1;
                k1 = 1;
            }
            else{
                RU[i2] = (string*)malloc(sizeof(string));
                RU[i2]->c1 = c;
                RU[i2]->c2 = 0;
                RU[i2]->ru_en = 0;
                ++i2;
            }
            i++;
        }
        int i3 = 0;
        i = 0;
        while(ru[i3] != '\0'){
            c = ru[i3];
            c2 = ru[i3+1];
            if(c == 208 || c == 209 || c == 210){
                if(Search2(fr,ru[i3], ru[i3+1]) == 0){
                    RU[i2] = (string*)malloc(sizeof(string));
                    RU[i2]->c1 = c;
                    RU[i2]->c2 = c2;
                    RU[i2]->ru_en = 1;
                    ++i2;
                }
                i3+=2;
            }
            else{
                if(Search2(fr,ru[i3], 0) == 0){
                    RU[i2] = (string*)malloc(sizeof(string));
                    RU[i2]->c1 = c;
                    RU[i2]->c2 = 0;
                    RU[i2]->ru_en = 0;
                    ++i2;
                }
                ++i3;
            }
        }
        return RU;
    }
}
//Сравнение строк
int str_comp(char s1[], char s2[]){
    for (int i = 0; ; i++){
        if (s1[i] != s2[i])
            return s1[i] < s2[i] ? -1 : 1;
        if (s1[i] == '\0')
            return 0;
    }
}
string** char_to_str(char *t){
    int n = 0, r = 0;
    unsigned char c, c2;
    while(t[r] != '\0'){
        c = t[r];
        if(c == 208 || c == 209 || c == 210){
            n++;
            r+=2;
        }
        else{
            n++;
            r++;
        }

    }
    n++;
    string **S = (string**)malloc(sizeof(string*)*n);
    
    int k1 = 0, i = 0, i2 = 0;
    
    while(t[i] != '\0'){
        c = t[i];
        if(t[i+1] != '\0')
            c2 = t[i+1];
        if(c == 208 || c == 209 || c == 210){
            S[i2] = (string*)malloc(sizeof(string)*n);
            S[i2]->c1 = c;
            S[i2]->c2 = c2;
            S[i2]->ru_en = 1;
            ++i2; 
            i+=2;
        }
        else{
            S[i2] = (string*)malloc(sizeof(string)*n);
            S[i2]->c1 = c;
            S[i2]->c2 = 0;
            S[i2]->ru_en = 0;
            ++i2; 
            i++;
        }
    }
    S[n-1] = NULL;
    return S;
}
void print_str(string **S){
    int i = 0;
    while(S[i] != NULL){
        if(S[i]->ru_en == 1)
            printf("%c%c",S[i]->c1, S[i]->c2);
        else
            printf("%c", S[i]->c1);
        ++i;
    }
    printf("\n");
}
void print_tabl(string **S){
    int i = 0;
    while(S[i] != NULL){
        if(S[i]->ru_en == 1)
            printf("%c%c",S[i]->c1, S[i]->c2);
        else
            printf("%c", S[i]->c1);
        
        ++i;
        if(i % 6 == 0)
            printf("\n");
    }
    printf("\n");
}
int srv_str(string **s1, string **s2){
    for(int i = 0; ; ++i){
        if(s1[i] == NULL && s2[i] == NULL)
            return 0;
        if(s1[i]->c1 != s2[i]->c1 || s1[i]->c2 != s2[i]->c2){
            return 1;
        }
        
    }
    return 1;

}