#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "header.h"
#include "operation_bit.h"

void replace_enter(char *str){
    int i = 0;
    while('\0' != str[i]){
        if(str[i] == '\n'){
            str[i] = '\0';
            break;
        }
        ++i;
    }
}

void coder_ASCII(){

}
int input_name(char *data, int n){

    printf("Input name: ");
    fgets(data, n, stdin);
    replace_enter(data);
    return 0;
}



int write_data_file(char *data, int n, char *filename){
    FILE *file = fopen(filename, "w");
    if(!file){
        perror("write_data_file");
        return -1;
    }
    //print_bit((u_char*)data, n * SHIFT, file);
    fwrite(data, n, sizeof(char), file);
    fclose(file);
    return 0;
}
int main(int argc, char *argv[]){
    char data[SIZE_BUF];
    memset(data, 0, sizeof(data));

    input_name(data, sizeof(data));
    //memcpy(data, "Andrey Karpenko", 16);
    printf("data: %s - %d\n", data, strlen(data));
    if(argc < 2){
        printf("No file has been entered to save\n");

        return -1;        
    }
    print_bit(data, strlen(data) * SHIFT, stdout);
    write_data_file(data, strlen(data), argv[1]);
    return 0;
}


