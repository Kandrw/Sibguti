#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "header.h"
#include "operation_bit.h"


int main(int argc, char *argv[]){
    u_char buf[256];
    if(argc < 3){
        printf("Not found argv: <bytes> <new_str>\n");
        return -1;
    }
    FILE *out, *inpt;
    inpt = fopen(argv[1], "r");
    if(!inpt){
        printf("Not found: %s\n", argv[1]);
        return -1;
    }
    out = fopen(argv[2], "w");
    int status = 1;
    int size = 0;
    while(status > 0){
        //status = fread(data, SIZE_BUF, sizeof(u_char), file);
        status = fread(buf, sizeof(u_char), sizeof(buf), inpt);
        if(status == -1){
            perror("fread");
            fclose(inpt);
            fclose(out);
            return -1;
        }
        print_bit(buf, SHIFT * status, out);
        size += status;
    }
    
    printf("bytes(%d) to string\n", size * SHIFT);
    return 0;
}






