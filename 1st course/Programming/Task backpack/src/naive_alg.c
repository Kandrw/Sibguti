#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Func.h"
//Наивный алгоритм
info* naive_algorithm(int *data, int N, int S){
    int iteration = 0;
    int i, i2, i3;
    int size = pow(2, N); //количество вариантов
    int *size_var= malloc(sizeof(int) * size);//размер каждого варианта
    int *variants[size];//хранение вариантов
    size_var[0] = 1;
    int *p1;
    p1 = malloc(sizeof(int) * 1);
    p1[0] = data[0];
    variants[0] = p1;
    i = 1;
    int sum_var;
    int st1 = 1;//колтчество вариантов которые будут повторно перебираться, для перебора всех вариантов
    int st2 = st1;// подсчет новых, для перебора в следующей итерации
    while(i < N){
        p1 = malloc(sizeof(int) * 1);
        p1[0] = data[i];
        variants[st2] = p1;
        size_var[st2] = 1;
        iteration += 1;
        if(data[i] == S){
                //сбор данных
                info *inf = (info*)malloc(sizeof(info));
                inf->N = 1;//количество набора
                inf->iteration = st2;//количество итераций
                inf->arrayS = p1;//набор
                //освобождение памяти
                free(size_var);
                for(i = 0; i < st2-1; ++i)
                    free(variants[i]);
                return inf;
        }
        ++st2;
        //Обход смещения, то есть из текущего элемента массива[i] и предыдущих наборов создаются новые наборы 
        for(i2 = 0; i2 < st1; ++i2){
            p1 = (int*)malloc(sizeof(int) * (size_var[i2] + 1));
            p1[0] = data[i];
            size_var[st2] = size_var[i2] + 1;
            //Заполнение нового набора
            for(i3 = 0; i3 < size_var[i2]; ++i3)
                p1[i3 + 1] = variants[i2][i3];
            sum_var = sum_arr(p1, size_var[i2] + 1);
            iteration += size_var[st2];
            //вариант нашелся
            if(sum_var == S){
                //printf("st2 = %d, iter = %d\n", st2, iteration);
                //сбор данных
                info *inf = (info*)malloc(sizeof(info));
                inf->N = size_var[i2] + 1;//количество набора
                inf->iteration = st2 * (size_var[i2] + 1);//количество итераций
                inf->arrayS = p1;//набор
                //освобождение памяти
                free(size_var);
                for(i = 0; i < st2-1; ++i)
                    free(variants[i]);
                return inf;
            }
            variants[st2] = p1;
            ++st2;
        }
        st1 = st2;
        ++i;
    }
    //освобождение памяти
    free(size_var);
    for(i = 0; i < size; ++i)
        free(variants[i]);
    return NULL;//набора не существует
}