#include <iostream>
#include <cmath>
#include "operation_bit.h"

void print_bit1(int a, int count_bit){
    int i;
    for(i = count_bit-1; i >= 0; --i){
        std::cout<<((a & (int)pow(2, i)) > 0?1:0);
    }
    std::cout<<"\n";
}
int shift(int a, int s){
    return ((a & s) >> (int)log2(s));
}
int rule_gen(int *a, int *res, int len, int sr1, int sr2, int(*shift)(int, int), char tag){
    int i;
    int b, r1, r2;
    int n = pow(2, len);
    r1 = shift(*a, sr1);
    r2 = shift(*a, sr2);
    *res = shift(*a, 1);
    b = r1 ^ r2;
    b = b << (len-1);
    *a = *a >> 1;
    *a = *a | b;
}

int rule_gen2(int *a, int *res, int len, int sr1, int sr2, int(*shift)(int, int), char tag){
    int i;
    int b, r1, r2;
    int n = pow(2, len);
    r1 = shift(*a, sr1);
    r2 = shift(*a, sr2);
    *res = shift(*a, 1);
    b = r1 ^ r2;
    b = b << (len-1);
    *a = *a >> 1;
    *a = *a | b;
}
int generate_sequence_start_end(int sx, int sy, int ex, int ey, int count_bit, char *savefile, char *data, char *filename_sgold, char *filename_egold){
    int i;
    int n = pow(2, count_bit);
    int x, y;
    int res;
    int res_bits = 0;
    int status = 1;
    //int size = 0;
    u_char buf[256];
    FILE *inpt = fopen(data, "r");
    if(!inpt){
        printf("Not found %s\n", data);
        return -1;
    }
    FILE *file = fopen(savefile, "w");
    FILE *file_gold = fopen(filename_sgold, "w");
    std::cout<<"x = ";
    print_bit1(sx, count_bit);

    std::cout<<"y = ";
    print_bit1(sy, count_bit);
    //синхро-послед в начале
    for(i = n - 1; i > 0; --i){
        rule_gen(&sx, &x, count_bit, 2, 4, shift, 'x');
        rule_gen(&sy, &y, count_bit, 4, 8, shift, '\t');
        res = x ^ y;
        //std::cout<<res;
        res_bits = res_bits | (res << (i - 1) );
    }
    fwrite((char*)&res_bits, 4, 1, file);
    print_bit((u_char*)&res_bits, 31, file_gold);
    fclose(file_gold);
    std::cout<<"sequence = ";
    print_bit((u_char*)&res_bits, 31, stdout);
    while(status > 0){
        //status = fread(data, SIZE_BUF, sizeof(u_char), file);
        status = fread(buf, sizeof(u_char), sizeof(buf), inpt);
        if(status == -1){
            perror("fread");
            fclose(inpt);
            fclose(file);
            return -1;
        }
        if(status > 0)
            fwrite(buf, status, sizeof(u_char), file);
    }
    //синхро-послед в конце
    for(i = n - 1; i > 0; --i){
        rule_gen2(&ex, &x, count_bit, 3, 6, shift, 'x');
        rule_gen2(&ey, &y, count_bit, 4, 7, shift, '\t');
        res = x ^ y;
        //std::cout<<res;
        res_bits = res_bits | (res << (i - 1) );
    }
    file_gold = fopen(filename_egold, "w");
    fwrite((char*)&res_bits, 4, 1, file);
    print_bit((u_char*)&res_bits, 31, file_gold);
    fclose(file_gold);
    //std::cout<<"\n";
    fclose(file);
    fclose(inpt);
}
int generate_sequence(int sx, int sy, int count_bit, char *savefile, char *data, char *filename_gold){
    int i;
    int n = pow(2, count_bit);
    int x, y;
    int res;
    int res_bits = 0;
    int status = 1;
    //int size = 0;
    u_char buf[256];
    FILE *inpt = fopen(data, "r");
    if(!inpt){
        printf("Not found %s\n", data);
        return -1;
    }
    FILE *file = fopen(savefile, "w");
    FILE *file_gold = fopen(filename_gold, "w");
    std::cout<<"x = ";
    print_bit1(sx, count_bit);

    std::cout<<"y = ";
    print_bit1(sy, count_bit);
    
    for(i = n - 1; i > 0; --i){
        rule_gen(&sx, &x, count_bit, 2, 4, shift, 'x');
        rule_gen(&sy, &y, count_bit, 4, 8, shift, '\t');
        res = x ^ y;
        //std::cout<<res;
        res_bits = res_bits | (res << (i - 1) );
    }
    fwrite((char*)&res_bits, 4, 1, file);
    print_bit((u_char*)&res_bits, 31, file_gold);
    fclose(file_gold);
    std::cout<<"sequence = ";
    print_bit((u_char*)&res_bits, 31, stdout);
    while(status > 0){
        //status = fread(data, SIZE_BUF, sizeof(u_char), file);
        status = fread(buf, sizeof(u_char), sizeof(buf), inpt);
        if(status == -1){
            perror("fread");
            fclose(inpt);
            fclose(file);
            return -1;
        }
        if(status > 0)
            fwrite(buf, status, sizeof(u_char), file);
    }
    //std::cout<<"\n";
    fclose(file);
    fclose(inpt);
}

int main(int argc, char *argv[]){
    u_char data[SIZE_BUF * 2];
    if(argc < 5){
        printf("Not found argv: <save_gold_data_crc> <data_crc> <seq start gold> <seq end gold>\n");
        return -1;
    }
    //generate_sequence(9, 14, 5, argv[1], argv[2], argv[3]);
    generate_sequence_start_end(9, 14, 7, 12, 5, argv[1], argv[2], argv[3], argv[4]);
    
    std::cout<<"End add gold seq\n";
    
}



















