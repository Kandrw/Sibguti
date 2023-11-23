#include <iostream>
#include <cmath>

#define SIZE_SEQ (pow(2, 5) - 1)

void print_bit(int a, int count_bit){
    int i;
    for(i = count_bit-1; i >= 0; --i)
        std::cout<<((a & (int)pow(2, i)) > 0?1:0);
    std::cout<<"\n";
}

int mutual_correlation(int seq_orig, int seq_new){
    int i;
    int sum = 0;
    print_bit(seq_orig, SIZE_SEQ);
    print_bit(seq_new, SIZE_SEQ);
    
    for(i = 0; i < SIZE_SEQ; ++i){
        sum += (seq_orig & 1) * (seq_new & 1);
        seq_orig >>= 1;
        seq_new >>= 1;
    }
    std::cout<<"mutual correlation = "<<sum<<"\n";
}


int main(){
    char file_seq_9_14[] = "sequence_9_14.txt";
    char file_seq_10_9[] = "sequence_10_9.txt";
    FILE *file = fopen(file_seq_9_14, "r");
    int seq_orig, seq_new;
    
    if(!file){
        std::cout<<"file "<<file_seq_9_14<<" not found\n";
        return -1;
    }
    if(fread((char*)&seq_orig, 4, 1, file) != 1){
        std::cout<<"Incorrect data: "<<file_seq_9_14;
        fclose(file);
        return -1;
    }
    fclose(file);
    file = fopen(file_seq_10_9, "r");
    if(!file){
        std::cout<<"file "<<file_seq_10_9<<" not found\n";
        return -1;
    }
    if(fread((char*)&seq_new, 4, 1, file) != 1){
        std::cout<<"Incorrect data: "<<file_seq_10_9<<"\n";
        fclose(file);
        return -1;
    }
    fclose(file);
    mutual_correlation(seq_orig, seq_new);

    std::cout<<"End item4\n";
    return 0;
}








