#include <stdio.h>
#include <stdlib.h>
//Создание массива с нужными параметрами
int *Create(int len, int m1, int m2){
    int i;
    int *data = malloc(sizeof(int) * len);
    for(i = 0; i < len; ++i)
        data[i] = rand() % (m2-m1) + m1;
    return data;
}
//замена char(10) на '\0'
int dchar(char *s){
    int i = 0;
    while(s[i] != '\0'){
        if(s[i] == 10){
            s[i] = '\0';
            return 1;
        }
        ++i;
    }
    return 0;
}
//сумма массива
int sum_arr(int *D, int n){
    int i, s = 0;
    for(i = 0; i < n; ++i)
        s += D[i];
    return s;
}
//Бинарный поиск
int search_bin(int *s2, int n, int el){
    int low, high, middle;
    low = 0;
    high = n - 1;
    while (low <= high){
        middle = (low + high) / 2;
        if (el < s2[middle])
            high = middle - 1;
        else if (el > s2[middle])
            low = middle + 1;
        else 
            return middle;
    }
    return -1;
}
//Быстрая сортировка
void fast_sort(int* s_arr, int first, int last, int *yp[], int *psize, int *iter){
    int i = first, j = last, x = s_arr[(first + last) / 2];
    int p1, *p2, p3;
    do {
        while (s_arr[i] < x){
            i++;
        }
        while (s_arr[j] > x){
            j--;   
        }
        if(i <= j) {
            if (s_arr[i] > s_arr[j]){
                p1 = s_arr[i];
                s_arr[i] = s_arr[j];
                s_arr[j] = p1;
                p2 = yp[i]; yp[i] = yp[j]; yp[j] = p2;
                p3 = psize[i]; psize[i] = psize[j]; psize[j] = p3;
                *iter += 1;   
            }
            i++;
            j--;
        }
        
    } while (i <= j);
    if (i < last){
        fast_sort(s_arr, i, last, yp, psize, iter);
    }
    if (first < j){
        fast_sort(s_arr, first, j, yp, psize, iter);
    }
}
//Склиивание двух массивов и возврат нового
int *join_array(int *A, int n1, int *B, int n2){
    int i;
    int *C = malloc(sizeof(int) * (n1+n2));
    for(i = 0; i < n1; ++i)
        C[i] = A[i];
    for(i = 0; i < n2; ++i)
        C[i+n1] = B[i];
    return C;
}