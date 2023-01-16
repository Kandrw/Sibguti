#include <stdlib.h>
#include <stdio.h>
#include "Func.h"

char2 **char_to_char2(char *s){
    int i = 0, n;
    unsigned char c;
    int k1 = 0;
    while(s[i] != '\0'){
        c = s[i];
        if(c == 208 || c == 209 || c == 210){
            i +=2 ;
        }
        else{
            i++;
        }
    }
    n = i+1;
    char2 **S = (char2**)malloc(sizeof(char2*) * n);
    S[n-1] = NULL;
    i = 0;
    while(s[i] != '\0'){
        c = s[i];
        if(c == 208 || c == 209 || c == 210){
            S[i] = (char2*)malloc(sizeof(char2));
            S[i]->s1 = c;
            c = s[i+1];
            S[i]->s1 = c;
            i+=2;
        }
        else{
            S[i] = (char2*)malloc(sizeof(char2));
            S[i]->s1 = c;
            S[i]->s2 = 0;
            ++i;
        }
    }
    
    return S;
}
char2 **alphabet(int RU_EN){
    char2 **alp1 = NULL;
    int N;
    char *al;
    char *ru = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя\n ,.?!";
    char *en = "abcdefghijklmnopqrstuvwxyz\n ,.?!";
    if(RU_EN == 1){
        al = ru;
    }
    else{
        al = en;
    }
    unsigned char c;
    N = 0;
    int i = 0;
    while(al[i] != '\0'){
        c = al[i];
        if(c == 208 || c == 209 || c == 210){
            N++;
            i+=2;
        }
        else{
            i++;
            N++;
        }
    }
    N++;
    alp1 = (char2**)malloc(sizeof(char2*) * N);
    alp1[N-1] = NULL;
    i = 0;
    int i2 = 0;
    while(al[i] != '\0'){
        c = al[i];
        //printf("i = %d\n", i);
        if(c == 208 || c == 209 || c == 210){
            alp1[i2] = (char2*)malloc(sizeof(char2));
            alp1[i2]->s1 = c;
            c = al[i+1];
            alp1[i2]->s2 = c;
            i += 2;
            ++i2;
        }
        else{
            alp1[i2] = (char2*)malloc(sizeof(char2));
            alp1[i2]->s1 = c;
            alp1[i2]->s2 = 0;
            i++;
            ++i2;
        }
    }
    return alp1;

}

//Проверка наличия символа в строке
int found(char2 **text, int c1, int c2, int start, int end){
    int i = start;
    //printf("s = %d, e = %d\n", start, end);
    while(i < end){
        if(text[i]->s1 == c1 && text[i]->s2 == c2){
            return 1;
        }
        ++i;
    }
    return 0;
}

char2 **alphabet_key(char2 **alp1, char2 **key, int k){
    char2 **alp2 = NULL;
    int N = 0;
    while(alp1[N] != NULL){
        N++;
    }
    N++;
    alp2 = (char2**)malloc(sizeof(char2*) * N);
    alp2[N-1] = NULL;
    int i = k, i2 = 0;
    while(key[i2] != NULL && i2 < N-1){
            if(found(alp2, key[i2]->s1, key[i2]->s2, k, i) == 0){
                alp2[i] = (char2*)malloc(sizeof(char2));
                alp2[i]->s1 = key[i2]->s1;
                alp2[i]->s2 = key[i2]->s2;
                ++i; 
            }
            ++i2;
    }
    int nk = 0;
    while(key[nk] != NULL)
        nk++;
    i2 = 0;
    while(i < N-1){
        if(found(key, alp1[i2]->s1, alp1[i2]->s2, 0, nk) == 0){
            alp2[i] = (char2*)malloc(sizeof(char2));
            alp2[i]->s1 = alp1[i2]->s1;
            alp2[i]->s2 = alp1[i2]->s2;
            i++;
        }
        i2++;
    }
    i = 0; i2 = 0;
    while(i < k){
        if(found(alp2, alp1[i2]->s1, alp1[i2]->s2, k, N-1) == 0){
            alp2[i] = (char2*)malloc(sizeof(char2));
            alp2[i]->s1 = alp1[i2]->s1;
            alp2[i]->s2 = alp1[i2]->s2;
            i++;
        }
        ++i2;
    }
    return alp2;
}


//Вывод массива указателей структуры char2
void print_char2(char2 **A){
    int i = 0;
    while(A[i] != NULL){
        if(A[i]->s2 == 0){
            printf("%c", A[i]->s1);
        }
        else{
            printf("%c%c", A[i]->s1,A[i]->s2);
        }
        ++i;
    }
    printf("\n");
}
char2 **OpenFile(char *fn){
    FILE *file = fopen(fn, "r");
    if(file == NULL){
        printf("Файл(%s) не найден\n", fn);
        return NULL;
    }
    char c;
    int k1 = 0;
    int N = 0;
    unsigned char c2;
    
    while((c = getc(file)) != EOF){
        c2 = c;
        if(k1 == 1){
            N++;
            k1 = 0;
        }
        else if(c2 == 208 || c2 == 209 || c2 == 210){
            k1 = 1;
        }
        else{
            N++;
        }
    }
    char2** T = (char2**)malloc(sizeof(char2*) * (N+1));
    T[N] = NULL;
    fseek(file,0L,SEEK_SET);
    int i = 0;
    
    while((c = getc(file)) != EOF){
        c2 = c;
        
        if(k1 == 1){
            T[i]->s2 = c2;
            i++;
            k1 = 0;
        }
        else if(c2 == 208 || c2 == 209 || c2 == 210){
            T[i] = (char2*)malloc(sizeof(char2));
            T[i]->s1 = c2;
            k1 = 1;
        }
        else{
            T[i] = (char2*)malloc(sizeof(char2));
            T[i]->s1 = c2;
            T[i]->s2 = 0;
            i++;
        }
    }
    
    fclose(file);
    return T;
}
