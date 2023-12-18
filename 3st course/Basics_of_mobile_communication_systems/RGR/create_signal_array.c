#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation_bit.h"











int main(int argc, char *argv[]){

    int N;
    //u_char *signal;
    u_char bit;
    FILE *inpt, *out;
    int status;
    int i, i2;
    int pos;
    if(argc < 4){
        printf("Not found argv: <data> <POS[0-N]> <new_signal>");
        return -1;
    }
    //N = atoi(argv[2]);
    pos = atoi(argv[2]);
    printf("position = %d\n", pos);
    inpt = fopen(argv[1], "r");
    if(!inpt){
        printf("Not found file %s\n", argv[1]);
        return -1;
    }
    //signal = malloc(N);
    i = 0;
    while(1){
        status = fscanf(inpt, "%c", &bit);
        if(status < 1){
            break;
        }
        i++;
    }
    printf("N = %d\n", i);
    N = i;
    if(pos >= N){
        printf("Position >= %d: %d\n", N, pos);
        return -1;
    }
    fseek(inpt,0L,SEEK_SET);
    out = fopen(argv[3], "w");
    for(i = 0; i < pos; ++i){
        fprintf(out, "0");
    }
    while(1){
        status = fscanf(inpt, "%c", &bit);
        if(status < 1){
            break;
        }
        fprintf(out, "%c", bit);
        i++;
    }
    for(; i < 2 * N; ++i){
        fprintf(out, "0");
    }
    printf("i = %d\n", i);
    fclose(out);
    fclose(inpt);
    printf("Create signal: %d\n");
    return 0;
}


