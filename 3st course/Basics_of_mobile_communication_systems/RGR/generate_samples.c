#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "operation_bit.h"

int main(int argc, char *argv[]){
    int N;
    u_char byte;
    FILE *inpt, *out;
    int status;
    int i, i2;
    int bit;
    if(argc < 4){
        printf("Not found argv: <data> <N sample> <new_sample>\n");
        return -1;
    }
    printf("argv: %s %s %s\n", argv[1], argv[2], argv[3]);
    N = atoi(argv[2]);
    inpt = fopen(argv[1], "r");
    if(!inpt){
        printf("Not found file %s\n", argv[1]);
        return -1;
    }
    out = fopen(argv[3], "w");

    while(1){
        status = fread(&byte, 1, 1, inpt);
        if(status <= 0){
            break;
        }
        for(i = 0; i < SHIFT; ++i){
            bit = get_bit(&byte, i + 1);
            //printf("%d ", bit);
            for(i2 = 0; i2 < N; ++i2){
                fprintf(out,"%d", bit);
            }
        }
        //printf("\n");
    }
    fclose(out);
    fclose(inpt);
    printf("generate sample x%d\n", N);
    return 0;
}


