#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Func.h"
#include "Bigramm.h"
#include "DeBigramm.h"




int main(int argc, char *argv[]){
    system("chcp 65001");
    
    if(argc < 2){//Через кослось нечего не вводилось
        int MAXLEN = 100;//длинна макс введеной строки
        int i = 0;
        char *text = (char*)malloc(sizeof(char) * MAXLEN);
        printf("Input text: ");
        fgets(text, MAXLEN, stdin);
        while(text[i] != '\0'){
            if(text[i] == 10){
                text[i] = '\0';
                break;
            }
            i++;
        }
        
        printf("Not Bigramm: %s\n", text);
        printf("Input key text: ");
        char *fr = (char*)malloc(sizeof(char) * 20);
        scanf("%s%*c", fr);
        printf("\n");
        
       
        char *tabl = CreateEN(fr);
        printf("tabl = %s\n", tabl);
        char *detext = Bigramm(text, tabl);
        printf("Bigramm: %s\n", detext);
        char *text2 = DeBigramm(detext, tabl);
        printf("DeBigramm: %s\n\n", text2);
        if(str_comp(text, text2) == 0){
            printf("Not Bigramm = Debigram\n");
        }
        else{
            printf("Not Bigramm != Debigram\n");
        }
    }
    else{
        int RE;
        printf("Input RU(1) or EN(0): ");
        scanf("%d%*c", &RE);
        printf("\n");
        FILE *file;
        file = fopen(argv[1],"r" );
        if(file == NULL){
            printf("Not found file\n");
            return 1;
        }
        char p;
        int n = 0, i =0;
        while((p = getc(file)) != EOF){
            n++;
        }
        //printf("n = %d\n", n);
        if(n <= 0){
            printf("File pyst\n");
            fclose(file);
            return 1;
        }
        char *text = (char*)malloc(sizeof(char) * (n+1));
        text[n] = '\0';
        i = 0;
        fseek(file,0L,SEEK_SET);
        while((p = getc(file)) != EOF){
            text[i] = p;
            ++i;
        }
        printf("text = %s\n", text);
        fclose(file);
        char *fr = NULL;
        if(argc >= 3){
            fr = argv[2];    
        }
        if(RE == 1){
            if(fr == NULL){
                printf("Error: имя файла с ключем не введено\n");
                return 1;
            }
            file = fopen(fr, "r");
            if(file == NULL){
                printf("Файл с ключем не найден\n");
                return 1;
            }
            char c;
            int N = 0;
            while((c = getc(file)) != EOF){
                ++N;
            }
            ++N;
            fseek(file,0L,SEEK_SET);
            char *key = (char*)malloc(sizeof(char) * N);
            key[N-1] = '\0';
            int i = 0;
            while((c = getc(file)) != EOF){
                key[i] = c;
                ++i;
            }
            string **tstr = char_to_str(text);
            string **tabl = CreateRU(key);
            print_tabl(tabl);
            string **detext = BigrammRU(tstr, tabl);
            printf("Bigramm: ");
            
            print_str(detext);
            
            string **text2 = DeBigrammRU(detext, tabl);
            printf("DeBigramm: ");
            print_str(text2);
            if(srv_str(tstr, text2) == 0){
                printf("Not Bigramm = Debigram\n");
            }
            else{
                printf("Not Bigramm != Debigram\n");
            }  
            if(argc >= 4){
                file = fopen(argv[3], "w");
                i = 0;
                while(detext[i] != NULL){
                    if(detext[i]->ru_en == 1){
                        putc(detext[i]->c1, file);
                        putc(detext[i]->c2, file);
                    }
                    else{
                        putc(detext[i]->c1, file);
                    }
                    ++i;
                }
                fclose(file);
                printf("Write file\n");

            } 

        }
        else{
            char *tabl = CreateEN(fr);
            printf("tabl = %s\n", tabl);
            printf("Not Bigramm: %s\n",text);
            char *detext = Bigramm(text, tabl);
            printf("Bigramm: %s\n", detext);
            char *text2 = DeBigramm(detext, tabl);
            printf("DeBigramm: %s\n", text2);
            if(str_comp(text, text2) == 0){
                printf("Not Bigramm = Debigram\n");
            }
            else{
                printf("Not Bigramm != Debigram\n");
            }   
            if(argc >= 4){
                file = fopen(argv[3], "w");
                i = 0;
                while(detext[i] != '\0'){
                    putc(detext[i], file);
                    ++i;
                }
                fclose(file);
                printf("Write file\n");

            }
        }



    }
    

    printf("End\n");
}


