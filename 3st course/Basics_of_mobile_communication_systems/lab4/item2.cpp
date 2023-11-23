#include <iostream>
#include <cmath>

#define SIZE_SEQ (pow(2, 5) - 1)

void print_bit(int a, int count_bit){
    int i;
    for(i = count_bit-1; i >= 0; --i)
        std::cout<<((a & (int)pow(2, i)) > 0?1:0);
    std::cout<<"\n";
}
void print_bit_format(int a, int count_bit){
    int i;
    for(i = count_bit-1; i >= 0; --i)
        std::cout<<"|  "<<((a & (int)pow(2, i)) > 0?1:0)<<"  ";
}
int shift(int a, int s){
    return ((a & s) >> (int)log2(s));
}
int auto_correlation(int seq_orig, int seq_shift, int count_bit){
    int c = 0, o = 0;//Совпадают, отличаются
    int i;
    for(i = count_bit - 1; i >= 0; --i){
        if(shift(seq_orig, pow(2, i)) == shift(seq_shift, pow(2, i)))
            c++;
        else
            o++;
    }
    return c - o;
}
void item2(int len_seq, char *filename){
    int seq_orig;
    FILE *file = fopen(filename, "r");
    if(!file){
        std::cout<<"file "<<filename<<" not found\n";
        return;
    }
    int status = fread((char*)&seq_orig, 4, 1, file);
    if(!status){
        std::cout<<"Incorrect data\n";
        return;
    }
    fclose(file);
    std::cout<<"data = ";
    print_bit(seq_orig, SIZE_SEQ);
    int i;
    int seq_shift = seq_orig, bit, cor;
    std::cout<<"Shift ";
    for(i = 0; i < SIZE_SEQ; ++i){
        printf("| b%2d ", i);
    }
    std::cout<<" | Autocorrelation\n";
    for(i = 0; i <= SIZE_SEQ; ++i){
        printf("  %2d  ", i);
        cor = auto_correlation(seq_orig, seq_shift, SIZE_SEQ);
        print_bit_format(seq_shift, SIZE_SEQ);
        if(cor == SIZE_SEQ)
            std::cout<<"| 1"<<"\n";
        else
            std::cout<<"| "<<cor<<"/"<<SIZE_SEQ<<"\n";
        bit = seq_shift & 1;
        seq_shift = (seq_shift >> 1) | ( (bit << ((int)SIZE_SEQ) - 1));
    }
}
int main(){
    char file_seq[] = "sequence.txt";

    item2(SIZE_SEQ, file_seq);
    std::cout<<"End item2\n";
    return 0;
}

