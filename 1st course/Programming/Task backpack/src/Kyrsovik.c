#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Func.h"
#include "MITM.h"
#include "naive_alg.h"
void print_info(info *D);
void print_arr(int *data, int len);
int str_to_int(char *str);
int input_number();
//Вызов алгоритмов
int RUN(int *data, int N, int S){
    info *D = NULL;
    if(N == 1){
        printf("Warning: array of a single number\n");//массив из одного числа
        if(S == data[0]){
            printf("S = data[0] = %d\n", S);
        }
        else{
            printf("S != data[0]\n");
        }
        return 1;
    }
    if(N < 19)
        D = naive_algorithm(data, N, S);
    else
        printf("Naive algorithm - Error: N > 18\n");
    if(D != NULL){
        printf("Naive algorithm:\n");
        print_info(D);
    }
    else
        printf("Not found info\n");//невозможно составить комбинацию или слишком много чисел
    free(D);
    if(N < 37)
        D = MITM(data, N, S);
    else
        printf("Meet-in-the-middle - Error: len > 36\n");

    if(D != NULL){
        printf("\nMeet-in-the-middle:\n");
        print_info(D);
    }
    else
        printf("Not found info\n");//невозможно составить комбинацию или слишком много чисел
    free(D);
    return 0;
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    int *data = NULL;
    int N, S;
    //Обработка аргументов командной строки
    if(argc > 2){
        int i, x;
        N = argc-2;
        data = malloc(sizeof(int) * N);
        S = str_to_int(argv[1]);
        if(S <= 0)
            return 1;
        for(i = 0; i < N; ++i){
            x = str_to_int(argv[i+2]);
            if(x <= 0)
                return 1;
            data[i] = x;
        }
        printf("\n");
    }
    else{
        char w;
        printf("Open file or create?(1/0)\n");
        scanf("%c%*c",&w);
        printf("\n");
        //Чтение из файла
        if(w == '1'){
            int i, x;
            printf("Input name file: ");
            FILE *file;
            char rk[10];
            char name_file[100];
            fgets(name_file, 100, stdin);printf("\n");
            dchar(name_file);
            file = fopen(name_file, "r");
            if(file == NULL){
                printf("Error: not found file\n");//файла нет или он не открылся
                return 1;
            }
            i = 0;
            //Чтение только 1 и 2 строки где хранятся количество цифр и число S
            while(fscanf(file, "%s", &rk) != EOF){
                x = str_to_int(rk);
                if(x <= 0){
                    fclose(file);
                    return 1;
                }
                if(i == 0)
                    N = x;
                else if(i == 1)
                    S = x;
                ++i;
                if(i > 1)
                    break;
            }
            data = (int*)malloc(sizeof(int) * N);
            i = 0;
            while(fscanf(file, "%s", &rk) != EOF){
                x = str_to_int(rk);
                if(x <= 0){
                    fclose(file);
                    free(data);
                    return 1;
                }
                data[i] = x;
                ++i;
                if(i == N)
                    break;
            }
            if(i < N){
                printf("Error: The numbers in the file are less than the specified number\n");//Чисел в файле меньше указанного числа
                fclose(file);
                free(data);
                return 1;
            }
            printf("Data read\n");
            fclose(file);
        }
        //Создание случайного массива
        else{
            printf("Input N: ");
            N = input_number();
            if(N == -1){
                return 1;
            }
            if(N > 1000){
                printf("Error: the array is too large, N > 1000, N = %d\n", N);
                return 1;
            }
            printf("Input S: ");
            S = input_number();
            if(S == -1){
                return 1;
            }
            printf("Input min: ");
            int minn = input_number();
            if(minn == -1){
                return 1;
            }
            printf("Input max: ");
            int maxn = input_number();
            if(maxn == -1){
                return 1;
            }
            if(minn >= maxn){
                printf("Error: max number <= min number\n");
                return 1;
            }
            printf("minn = %d, maxn = %d\n", minn,maxn);
            data = Create(N, minn, maxn);
        }
    }
    printf("N = %d, S = %d\n",N,S);
    print_arr(data, N);
    RUN(data, N, S);
    printf("End program\n");
}
//Вывод полей структуры
void print_info(info *D){
    printf("\tIteration: %d\n",D->iteration);
    printf("\tArray:\n\t");
    print_arr(D->arrayS, D->N);
}
//Вывод массива
void print_arr(int *data, int len){
    int i;
    for(i = 0; i < len; ++i)
        printf("%d ",data[i]);
    printf("\n");
}
//Конвертирование строки в число и обработка ошибок
int str_to_int(char *str){
    int x = atoi(str);
    if(x == 0){
        printf("Error: incorrect data, introduced: %s\n",str);//число нулевое или является строкой
        return 0;
    }
    else if(x < 0){
        printf("Error: negative number, introduced: %d\n", x);//отрицательное
        return -1;
    }   
    return x;
}
//Ввод строки и преобразование ею в число, при этом идет проверка на корректность
int input_number(){
    char *s = (char*)malloc(sizeof(char) * 20);
    fgets(s, 20, stdin);
    dchar(s);
    int x = str_to_int(s);
    free(s);
    if(x <= 0)    
        return -1;
    return x;
}