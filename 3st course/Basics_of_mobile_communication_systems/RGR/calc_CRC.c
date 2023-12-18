#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "header.h"
#include "operation_bit.h"
#define OUT_CRC
//#define DEBUG
//#define ONLY_CALC_CRC

//Генерация полинома
void gen_polinom(u_char *p, int n){
    *(p) = (u_char)(175);
}
//#define DEBUG_CRC
//генерация CRC
u_char CRC_generate(u_char *package, u_char *polinom, int nbit){
    u_char shift = 0, sh2, byte;
    int i, i2;
    int con = 0;
    shift = srez(package, 0, SHIFT);
    u_char tt = 128 & shift;
    i = 0;
    while( tt == 0){
        i += 1;
        shift = srez(package, i, i + 7) << 1;
        tt = (u_char)128 & shift;

    }
    byte = srez(polinom, 0 + nbit - 16 - SHIFT, 9 + nbit - 16- SHIFT);
#ifdef DEBUG_CRC
    print_bit_char(byte, SHIFT, stdout); printf("  byte\n");
    print_bit_char(shift, SHIFT, stdout); printf("  start\n");
#endif
    for(; i <= nbit; ++i){
#ifdef DEBUG_CRC  
            print_bit_char(shift, SHIFT, stdout);
#endif
            if(con){
                shift ^=(u_char)0;
            }else{
                shift ^=byte;
            }
            if(!get_bit(&shift, 1)){
                con = 1;
            }
            else{
                con = 0;
            }
            sh2 = srez(package, i, i + 1);
#ifdef DEBUG_CRC  
            printf(" ^ ");
            print_bit_char(byte, SHIFT, stdout);
            printf(" = ");
            print_bit_char(shift, SHIFT, stdout);
            printf(" + "); print_bit_char(sh2, SHIFT, stdout);
            printf("\n");
#endif
            shift = (shift << 1 ) | sh2;
        
    }
#ifdef OUT_CRC
    printf("CRC:  ");
    print_bit_char(shift, SHIFT, stdout);
    printf("\n");
#endif 
    return shift;
}



int main(int argc, char *argv[]){

#ifdef ONLY_CALC_CRC
    u_char data[SIZE_BUF * 2];
    u_char polinom[SHIFT];
    u_char crc = 0;
    memset(data, 0, sizeof(data));
    gen_polinom(polinom, SHIFT);

    if(argc < 2){
        printf("Not found file argv\n");
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("File not found: %s\n", argv[1]);
        return -1;
    }
    int status = 1;
    int size = 0;
    while(status > 0){
        //status = fread(data, SIZE_BUF, sizeof(u_char), file);
        status = fread(data + size, sizeof(u_char), SIZE_BUF, file);
        
        printf("-- %d --\n", status);
        if(status == -1){
            perror("fread");
            fclose(file);
            return -1;
        }
        size += status;
    }
    fclose(file);
    printf("size = %d\n", size);
    print_bit(data, size * SHIFT, stdout);
    printf("Polinom: ");
    print_bit_char(*polinom, SHIFT, stdout); printf("\n");
    printf("Data:  \n");
    print_bit(data, size * SHIFT, stdout);
    crc = CRC_generate(data, polinom, (size-1) * SHIFT + 7);

    if(!crc){
        printf("Correct data!\n");
        *(data + size - 1) = 0;
        printf("Data: %s\n", (char*)data);
    }
    else{
        printf("Incorrect data\n");
        *(data + size - 1) = 0;
        printf("Data: %s\n", (char*)data);
    }

    return 0;
#endif
#ifndef ONLY_CALC_CRC
    u_char data[SIZE_BUF * 2];
    u_char polinom[SHIFT];
    u_char crc = 0;
    memset(data, 0, sizeof(data));
    gen_polinom(polinom, SHIFT);

    if(argc < 2){
        printf("Not found file argv\n");
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    if(!file){
        printf("File not found: %s\n", argv[1]);
        return -1;
    }
    int status = 1;
    int size = 0;
    while(status > 0){
        //status = fread(data, SIZE_BUF, sizeof(u_char), file);
        status = fread(data + size, sizeof(u_char), SIZE_BUF, file);
        
        printf("-- %d --\n", status);
        if(status == -1){
            perror("fread");
            fclose(file);
            return -1;
        }
        size += status;
    }
    fclose(file);
    printf("size = %d\n", size);
    print_bit(data, size * SHIFT, stdout);

   
    printf("Polinom: ");
    print_bit_char(*polinom, SHIFT, stdout); printf("\n");
    printf("Data + 0(%d):  \n", SHIFT - 1);
    print_bit(data, size * SHIFT + 7, stdout);

    crc = CRC_generate(data, polinom, size * SHIFT + 7);
    *(data + size) = crc;
    
    printf("Data + CRC:  \n");
    print_bit(data, size * SHIFT + SHIFT, stdout);
    if(argc > 2){
        file = fopen(argv[2], "w");
        fwrite((void*)data, size + 1, 1, file);
        fclose(file);
        printf("data + crc - save %s\n", argv[2]);
    }
    printf("end cals_crc\n");   
    return 0;
#endif
}







