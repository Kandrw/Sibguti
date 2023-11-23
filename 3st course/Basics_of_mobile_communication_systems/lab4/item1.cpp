#include <iostream>
#include <cmath>
void print_bit(int a, int count_bit){
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
void generate_sequence(int sx, int sy, int count_bit, char *savefile){
    int i;
    int n = pow(2, count_bit);
    int x, y;
    int res;
    int res_bits = 0;
    FILE *file = fopen(savefile, "w");
    std::cout<<"x = ";
    print_bit(sx, count_bit);
    std::cout<<"y = ";
    print_bit(sy, count_bit);
    std::cout<<"sequence = ";
    for(i = n - 1; i > 0; --i){
        rule_gen(&sx, &x, count_bit, 2, 4, shift, 'x');
        rule_gen(&sy, &y, count_bit, 4, 8, shift, '\t');
        res = x ^ y;
        std::cout<<res;
        res_bits = res_bits | (res << (i - 1) );
    }
    fwrite((char*)&res_bits, 4, 1, file);
    std::cout<<"\n";
    print_bit(res_bits, 31);
    fclose(file);
} 
int main(){
    char file_seq_9_14[] = "sequence_9_14.txt";
    generate_sequence(9, 14, 5, file_seq_9_14);
    std::cout<<"\tEnd item1\n";
    char file_seq_10_9[] = "sequence_10_9.txt";
    generate_sequence(10, 9, 5, file_seq_10_9);
    std::cout<<"\tEnd item3\n\n";
    return 0;
}
