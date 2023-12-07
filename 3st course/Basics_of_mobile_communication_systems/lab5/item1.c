#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SHIFT 8
#define NB ( ( (N) / SHIFT) + ( (N % SHIFT) > 0 ? 1:0) )

typedef unsigned char u_char;

//Вывести количество битов в байте
void print_bit_char(u_char a, int count_bit){
    int i;
    for(i = count_bit-1; i >= 0; --i)
        printf("%d", ((a & (u_char)pow(2, i)) > 0?1:0));
    printf(" ");
}
//Срез в битовой последовательности
u_char srez(u_char *data, int st, int en){
    u_char c1 = 0;
    while(st > SHIFT){
        
        st -= SHIFT;
        en -= SHIFT;
        data++;
    }
    c1 =( (*data >> (st )) | ( ( (*(1 + data) << (SHIFT - st) ) ))) ;
    c1 &= ((u_char)(pow(2, (en - st)) - 1) );
    return c1;
}
//сдвиг на байты
void shift_data(u_char *data, int len_byte){
    u_char shift = 0, sh2;
    int i;
    for(i = 0; i < len_byte - 1; ++i){
        sh2 = *(data + 1);
        *(data + 1) = *(data);
        *(data) = shift;
        shift = sh2;
        data += 2;
    }
}
//сдвиг на биты(можно более 8 бит)
void shift_bit_data(u_char *data, int len_byte, int nbit){
    u_char shift = 0, sh2, mask;
    int i, en;
    while(nbit >= SHIFT){
        shift_data(data, len_byte);
        nbit -= SHIFT;
    }
    if(nbit == 0)
        return;
    en = SHIFT - nbit;
    mask = (u_char)(pow(2, nbit)) - 1;
    mask = mask << en;
    for(i = 0; i < len_byte - 1; ++i){
        sh2 = mask & *(data);
        *(data) = *(data) << nbit;
        *(data) |= shift;
        shift = sh2 >> en;
        ++data;
    }
}
//Сгенерировать пакет с данными
void gen_package(u_char *p, int n){
    int i, i2;
    int n_b = n / SHIFT;
    //printf("nb = %d\n", n_b);
    for(i = 0; i < n_b; ++i){
        *p = (u_char)(rand() % 256);
        ++p;
    }
    if( n % SHIFT != 0){
        *p = (u_char)(rand() % 256) & ( (u_char)(pow(2, n % SHIFT)) - 1);
        ++p;
    }
}
//Вывести всю битовую последовательность(более 8 бит)
void print_bit(u_char *p, int count_bit){
    int i, i2;
    int n = count_bit / SHIFT;
    p += n;
    if(count_bit % SHIFT != 0){
        print_bit_char(*p, count_bit % SHIFT);
        --p;
    }
    for(i = n; i > 0; --i){
        print_bit_char(*p, SHIFT);
        --p;
    }
    printf("\n");
}
//Генерация полинома
void gen_polinom(u_char *p, int n){
    *(p) = (u_char)(175);
}
//получить бит
int get_bit(u_char *package, int pos){
    u_char mask;
    while(pos > SHIFT){
        pos -= SHIFT;
        package++;
    }
    mask = (u_char)(pow(2, pos));
    if(*package & mask){
        return 1;
    }
    return 0;
}
//генерация CRC
u_char CRC_generate(u_char *package, u_char *polinom, int nbit){
    u_char shift = 0, sh2, byte;
    int i, i2;
    //printf("nbit = %d\n", nbit);
    shift = srez(package, nbit-SHIFT, nbit);
    u_char tt = 128 & shift;
    while( tt == 0){
        nbit -= 1;
        shift = srez(package, nbit-SHIFT, nbit);
        tt = (u_char)128 & shift;
    }
    byte = srez(polinom, 0, 9);
    int con = 0;
    for(i = nbit - SHIFT - 1; i >= 0; --i){
#ifdef DEBUG 
            print_bit_char(shift, SHIFT); //printf("\n");
#endif
            if(con){
                shift ^=(u_char)0;
            }else{
                shift ^=byte;
            }
            if(!get_bit(&shift, 7)){
                con = 1;
            }
            else{
                con = 0;
            }
            sh2 = srez(package, i, i + 1);
#ifdef DEBUG  
            printf(" ^ ");
            print_bit_char(byte, SHIFT);
            printf(" = ");
            print_bit_char(shift, SHIFT);
            printf("\n");
            //print_bit_char(shift, SHIFT);printf("\n\n");
#endif
            if(i == -1){
                break;
            }
                
            shift = (shift << 1 ) | sh2;
        
    }
    printf("CRC:  ");
    print_bit_char(shift, SHIFT);
    printf("\n");
    return shift;
}
int main(){
    srand(time(NULL));
    u_char package[NB + 1];
    u_char polinom[NB];
    u_char crc;
    memset(polinom, 0, sizeof(package));
    memset(package, 0, sizeof(polinom));
    gen_package(package, N);
    printf("Data: ");
    print_bit(package, N);
    gen_polinom(polinom, N);
    printf("Polinom: ");
    print_bit_char(*polinom, SHIFT); printf("\n");
    shift_bit_data(package, NB, 7);
    printf("Data + 0(%d):  ", SHIFT - 1);
    print_bit(package, N);
    crc = CRC_generate(package, polinom, N + SHIFT);
    u_char *tt = package;
    *tt = (*tt & 128) | crc;
    printf("Data + CRC:  ");
    print_bit(package, N);
    printf("Test error:\n");
    crc = CRC_generate(package, polinom, N + SHIFT);
    if(crc == 0){
        printf("Error not found\n");
    }
    else{
        printf("Error crc!\n");
    }
    printf("End item1\n");
    return 0;
}







