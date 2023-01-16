#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Func.h"
//Алгоритм "Разделяй и властвуй"
info* MITM(int *data, int N, int S){
    int iteration = 0;
    int iter_mch1_st2;
    int i, i2, i3;
    //1 часть массива
    int t1 = N/2;//до куда проверять массив
    int size1 = pow(2, t1)-1;//количество вариантов
    int *size_var1 = malloc(sizeof(int) * size1);//размер набора
    int *varinats1[size1];//наборы
    int *sums_variants1 = malloc(sizeof(int) * size1);//сумма наборов
    int st1 = 1, st2 = st1;//смещение
    int *p1;
    size_var1[0] = 1;
    p1 = malloc(sizeof(int) * 1);
    p1[0] = data[0];
    varinats1[0] = p1;
    sums_variants1[0] = data[0];
    i = 1;
    while(i < t1){
        p1 = malloc(sizeof(int) * 1);
        p1[0] = data[i];
        varinats1[st2] = p1;
        size_var1[st2] = 1;
        sums_variants1[st2] = data[i];
        iteration += 1;
        if(sums_variants1[st2] == S){
            info *inf = (info*)malloc(sizeof(info));
            inf->N = 1;
            inf->iteration = st2;
            inf->arrayS = p1;
            //Освобождение памяти
            free(sums_variants1);
            free(size_var1);
            for(i2 = 0; i2 < st2; ++i2)
                free(varinats1[i2]);
            return inf;
        }
        ++st2;
        for(i2 = 0; i2 < st1; ++i2){
            p1 = (int*)malloc(sizeof(int) * (size_var1[i2] + 1));
            p1[0] = data[i];
            size_var1[st2] = size_var1[i2] + 1;
            for(i3 = 0; i3 < size_var1[i2]; ++i3)
                p1[i3 + 1] = varinats1[i2][i3];
            sums_variants1[st2] = sum_arr(p1, size_var1[st2]);
            iteration += size_var1[st2];
            if(sums_variants1[st2] == S){
                info *inf = (info*)malloc(sizeof(info));
                inf->N = size_var1[st2];
                inf->iteration = st2;
                inf->arrayS = p1;
                //Освобождение памяти
                free(sums_variants1);
                free(size_var1);
                for(i2 = 0; i2 < st2; ++i2)
                    free(varinats1[i2]);
                return inf;
            }
            varinats1[st2] = p1;
            ++st2;
        }
        st1 = st2;
        ++i;
    }
    iter_mch1_st2 = st2;
    int fsi = 0;
    fast_sort(sums_variants1, 0, size1-1, varinats1, size_var1, &fsi);
    //2 часть массива
    int t2 = N-t1;
    int size2 = pow(2, t2);
    int *size_var2 = malloc(sizeof(int) * size2);
    int *varinats2[size2];
    int *sums_variants2 = malloc(sizeof(int) * size2);
    st1 = 1; st2 = st1;
    p1 = malloc(sizeof(int) * 1);
    p1[0] = data[t1];
    size_var2[0] = 1;
    varinats2[0] = p1;
    sums_variants2[0] = data[t1];
    i = 1;
    int s_bin_res;
    while(i < t2){
        p1 = malloc(sizeof(int) * 1);
        p1[0] = data[i + t1];
        varinats2[st2] = p1;
        size_var2[st2] = 1;
        sums_variants2[st2] = data[i + t1];
        //Проверка суммы S во второй части массива 
        if(data[i + t1] == S){
            info *inf = (info*)malloc(sizeof(info));
            inf->N = 1;
            inf->iteration = st2 + iter_mch1_st2;
            inf->arrayS = p1;
            //Освобождение памяти
            free(sums_variants1);
            free(size_var1);
            free(sums_variants2);
            free(size_var2);
            for(i2 = 0; i2 < st2; ++i2)
                free(varinats1[i2]);
            for(i2 = 0; i2 < size1; ++i2)
                free(varinats2[i2]);
            return inf;
        }
        s_bin_res = search_bin(sums_variants1, size1, S-sums_variants2[st2]);
        //Проверка суммы S-s2 в 1-ой части массива, где s2-сумма текущего набора из 2 части массива
        if(s_bin_res > -1){
            info *inf = (info*)malloc(sizeof(info));
            inf->N = size_var1[s_bin_res] + size_var2[st2];
            inf->iteration = st2 + iter_mch1_st2;
            inf->arrayS = join_array(varinats1[s_bin_res], size_var1[s_bin_res], varinats2[st2], size_var2[st2]);
            //Освобождение памяти
            free(sums_variants1);
            free(size_var1);
            free(sums_variants2);
            free(size_var2);
            for(i2 = 0; i2 < st2; ++i2)
                free(varinats2[i2]);
            for(i2 = 0; i2 < size1; ++i2)
                free(varinats1[i2]);
            return inf;
        }
        ++st2;
        //Обход смещения, то есть из текущего элемента массива[i] и предыдущих наборов создаются новые наборы 
        for(i2 = 0; i2 < st1; ++i2){
            p1 = (int*)malloc(sizeof(int) * (size_var2[i2] + 1));
            p1[0] = data[i + t1];
            size_var2[st2] = size_var2[i2] + 1;
            for(i3 = 0; i3 < size_var2[i2]; ++i3)
                p1[i3 + 1] = varinats2[i2][i3];
            sums_variants2[st2] = sum_arr(p1, size_var2[st2]);
            //Проверка суммы(S) в 2-ой части массива
            if(sums_variants2[st2] == S){
                info *inf = (info*)malloc(sizeof(info));
                inf->N = size_var2[st2];
                inf->iteration = st2* size_var2[st2] + iter_mch1_st2;
                inf->arrayS = p1;
                //Освобождение памяти
                free(sums_variants1);
                free(size_var1);
                free(sums_variants2);
                free(size_var2);
                for(i2 = 0; i2 < st2-1; ++i2)
                    free(varinats2[i2]);
                for(i2 = 0; i2 < size1; ++i2)
                    free(varinats1[i2]);
                return inf;
            }
            s_bin_res = search_bin(sums_variants1, size1, S-sums_variants2[st2]);
            varinats2[st2] = p1;
            //Проверка суммы(S-s2) в 1-ой части массива
            if(s_bin_res > -1){
                info *inf = (info*)malloc(sizeof(info));
                inf->N = size_var1[s_bin_res] + size_var2[st2];
                inf->iteration = (st2 * size_var2[st2]) + iter_mch1_st2;
                inf->arrayS = join_array(varinats1[s_bin_res], size_var1[s_bin_res], varinats2[st2], size_var2[st2]);//склеивание набора
                //Освобождение памяти
                free(sums_variants1);
                free(size_var1);
                free(sums_variants2);
                free(size_var2);
                for(i2 = 0; i2 < st2-1; ++i2)
                    free(varinats2[i2]);
                for(i2 = 0; i2 < size1; ++i2){
                    if(i2 != s_bin_res)
                        free(varinats1[i2]);
                }
                return inf;
            }
            ++st2;
        }
        st1 = st2;
        ++i;
    }
    //Освобождение памяти
    free(sums_variants1);
    free(size_var1);
    free(sums_variants2);
    free(size_var2);
    for(i2 = 0; i2 < size1-1; ++i2)
        free(varinats1[i2]);
    for(i2 = 0; i2 < size2-1; ++i2)
        free(varinats2[i2]);
    return NULL;
}