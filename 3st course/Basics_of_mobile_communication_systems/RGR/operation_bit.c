#include "operation_bit.h"
#include "header.h"

//Вывести количество битов в байте
void print_bit_char2(u_char a, int count_bit, FILE *out){
    int i;
    for(i = 0; i < count_bit; ++i){
        fprintf(out, "%d", ((a & (u_char)pow(2, i)) > 0?1:0));
    }
    //fprintf(out, " ");
}
void print_bit_char(u_char a, int count_bit, FILE *out){
    int i;
    for(i = count_bit-1; i >= 0; --i){
        fprintf(out, "%d", ((a & (u_char)pow(2, i)) > 0?1:0));
    }
    //fprintf(out, " ");
}
//Вывести всю битовую последовательность(более 8 бит)
void print_bit(u_char *p, int count_bit, FILE *out){
    int i, i2;
    int n = count_bit / SHIFT;
    //p += n;
    //printf("\t+++++\n");
    for(i = n; i > 0; --i){
        print_bit_char(*p, SHIFT, out);
        //print_bit_char(*p, SHIFT, stdout); printf("  %d %c\n", *p, *p);
        ++p;
        printf(" ");
    }
    if(count_bit % SHIFT != 0){
        print_bit_char(*p, count_bit % SHIFT, out);
        //print_bit_char(*p, SHIFT, stdout); printf("  %d %c [1]\n", *p, *p);
        ++p;
        printf(" ");
    }
    printf("\n");
}
//Вывести всю битовую последовательность(более 8 бит)
void print_bit2(u_char *p, int count_bit, FILE *out){
    int i, i2;
    int n = count_bit / SHIFT;
    p += n;
    if(count_bit % SHIFT != 0){
        print_bit_char(*p, count_bit % SHIFT, out);
        //print_bit_char(*p, SHIFT, stdout); printf("  %d %c [1]\n", *p, *p);
        --p;
    }
    for(i = n; i > 0; --i){
        print_bit_char(*p, SHIFT, out);
        //print_bit_char(*p, SHIFT, stdout); printf("  %d %c\n", *p, *p);
        --p;
    }
    printf("\n");
}

//Срез в битовой последовательности
u_char srez1(u_char *data, int st, int en){
    u_char c1 = 0;
    while(st > SHIFT){
        
        st -= SHIFT;
        en -= SHIFT;
        data++;
    }
    c1 =( (*data >> (st)) );// | ( ( (*(1 + data) << (SHIFT - st) ) ))) ;
    print_bit_char(c1, SHIFT, stdout); printf("  c1 1\n");
    print_bit_char(( ( (*(1 + data) << (SHIFT - st) ))), SHIFT, stdout); printf("  c1 2\n");
    
    c1 &= ((u_char)(pow(2, (en - st)) - 1) );
    return c1;
}
u_char srez2(u_char *data, int st, int en){
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
u_char srez3(u_char *data, int st, int en){
    u_char c1 = 0;
    while(st > SHIFT){
        
        st -= SHIFT;
        en -= SHIFT;
        data++;
    }
    printf("%d - %d\n", st, en);
    c1 = *data << st;  
    print_bit_char(*data, SHIFT, stdout); printf("  <<  %d  ", st);
    print_bit_char(c1, SHIFT, stdout); printf("  st\n");

    if(en + st > SHIFT){
        en -= (SHIFT - st);
        printf("en2 = %d\n", en);
        ++data;
    }

    c1 = *data >> (SHIFT - en);  
    print_bit_char(*data, SHIFT, stdout); printf("  >>  (8 - %d)  ", en);
    print_bit_char(c1, SHIFT, stdout); printf("  en\n");


    printf("\n");
    return c1;
}

u_char srez(u_char *data, int st, int en){
    u_char c1 = 0, mask;
    while(st >= SHIFT){
        
        st -= SHIFT;
        en -= SHIFT;
        data++;
    }
    if(en > SHIFT + 1){
        //en = SHIFT;
    }
#ifdef DEBUG_SREZ
    printf("%d - %d\n", st, en);
#endif
    c1 = (*data << st);  
#ifdef DEBUG_SREZ
    print_bit_char(*data, SHIFT, stdout); printf("  <<  %d  ", st);
    print_bit_char(c1, SHIFT, stdout); printf("  st\n");
#endif
    //if(en - st > SHIFT){
    if( (SHIFT - st) < (en - st) ){
        
        en -= (SHIFT - st);
#ifdef DEBUG_SREZ
        printf("en2 = %d\n", en);
#endif
        ++data;
        //mask = *data >> (SHIFT - en + 1); 
        mask = *data >> (SHIFT - st);
        //mask = *data >> 4;
        //mask = mask >> (en + 1 - SHIFT) ; 
        // (u_char)pow(2, en + 1 - SHIFT)
        //mask = ((u_char)(pow(2,en - st) - 1) << (SHIFT - en));
        //print_bit_char(*data, SHIFT, stdout); printf("  >>  (8 - %d)  ", en);
#ifdef DEBUG_SREZ
        print_bit_char(*data, SHIFT, stdout); printf("  >>  %d  ", (SHIFT - st));
        print_bit_char(mask, SHIFT, stdout); printf("  en\n");
#endif
        //u_char m2  =  ((u_char)(pow(2, (en))) - 1);

        //print_bit_char(m2, SHIFT, stdout); printf("  m2\n");
        c1 |= mask;
        //printf("\n[2]Test: %d, %d, %d\n", SHIFT - en, en - st, SHIFT - en + st);
        return c1;
    }
    //mask = (u_char)(~(u_char)(pow(2,en) - 1)) >> en;
    mask = ((u_char)(pow(2,en - st) - 1) << (SHIFT - en));
#ifdef DEBUG_SREZ
    print_bit_char(mask, SHIFT, stdout); printf("  mask\n");
#endif
    c1 = mask & *data;
    //printf("\nTest: %d, %d, %d\n", SHIFT - en, en - st, SHIFT - en  + st);
    //printf("%d - %d\n", st, en);
    //print_bit_char(c1, SHIFT, stdout); printf("  c1\n");
    c1 = c1 >> ( SHIFT - en );

    //printf("\n");
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
        print_bit_char(*data, SHIFT, stdout); printf("  %d-\n\n", nbit);
        nbit -= SHIFT;
    }
    if(nbit == 0)
        return;
    en = SHIFT - nbit;
    mask = (u_char)(pow(2, nbit)) - 1;
    mask = mask << en;
    //print_bit_char(mask, SHIFT, stdout); printf("  mask\n");
    for(i = 0; i < len_byte - 1; ++i){
        //print_bit_char(*data, SHIFT, stdout); printf("  %d\n", i);
        
        sh2 = mask & *(data);
        //print_bit_char(sh2, SHIFT, stdout); printf("  %d sh\n", i);
        *(data) = *(data) << nbit;
        *(data) |= shift;
        shift = sh2 >> en;
        //print_bit_char(*data, SHIFT, stdout); printf("  %d\n", i);
        //printf("\n");
        ++data;
    }
}


//получить бит
int get_bit(u_char *package, int pos){
    u_char mask;
    while(pos > SHIFT){
        pos -= SHIFT;
        package++;
    }
    mask = (u_char)(pow(2, SHIFT - pos));
    //print_bit_char(mask, SHIFT, stdout);printf("  mask\n");
    if(*package & mask){
        return 1;
    }
    return 0;
}
//Изменить бит по позиции
int set_bit(u_char *package, int pos, int val){
    u_char mask;
    while(pos >= SHIFT){
        pos -= SHIFT;
        package++;
    }
    //printf("pos = %d\n", pos);
    mask = (u_char)(pow(2, SHIFT - pos));
    //print_bit_char(mask, SHIFT, stdout);printf("  mask\n");
    if(val){
        *package |= mask;
    }
    else{
        *package &= (~mask); 
    }
}