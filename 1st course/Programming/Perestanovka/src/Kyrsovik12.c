#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Perectanovka.h"
#include "DePerectanovka.h"
//Сравнение строк
int str_comp(char s1[], char s2[]){
    for (int i = 0; ; i++){
        if (s1[i] != s2[i])
            return s1[i] < s2[i] ? -1 : 1;
        if (s1[i] == '\0')
            return 0;
    }
}

int main(int argc, char *argv[]){
    int MaxLen = 100;//Максимальная длинна введеных слов
    //Если в консоли нет аргументов
    if(argc == 1){
        char *text = (char*)malloc(sizeof(char) * MaxLen);//Что зашифровать
        printf("Input text: ");
        scanf("%s%*c", text);
        printf("\n");
        char *key =  (char*)malloc(sizeof(char) * MaxLen);//Слово ключ
        printf("Input key(bez povtoreniy): ");
        scanf("%s%*c", key);
        printf("\n");
        char *shifrtext = Perectanovka(text, key);
        if(shifrtext == NULL){
            return 1;
        }
        printf("Shifr text: %s\n", shifrtext);
        char *detext = DePerestanovka(shifrtext, key);
        if(detext == NULL)
            return 1;
        printf("Decode text: %s\n", detext);
        if(str_comp(text, detext) == 0)
            printf("text == decode text\n");
        else
            printf("text != decode text\n");
    }
    //Если есть: файл откуда считать, ключ без повторений, куда записывать
    else{
        FILE *opf;
        opf = fopen(argv[1],"r" );//Открытие файла
        if(opf == NULL){
            printf("Not found file\n");
            return 1;
        }
        char d; int N = 0;
        //Подсчет длинны
        while((d=getc(opf)) != EOF){
            N++;
        }
        if(N < 1){
            printf("Not fount text in file\n");
            return 1;
        }
        char *text = (char*)malloc(sizeof(char) * (N+1));
        int i = 0;
        fseek(opf,0L,SEEK_SET);//коретка в конец файла, для повторного чтения
        while((d = getc(opf)) != EOF){
            text[i] = d;
            ++i;
        }
        text[i] = '\0';
        fclose(opf);
        char *key = NULL;

        if(argc == 2){
            key = (char*)malloc(sizeof(char) * MaxLen);
            printf("Input key(bez povtoreniy): ");
            scanf("%s%*c", key);
            printf("\n");
        }
        //Если в консоле введен ключ
        else{
            key = argv[2];
        }
        if(key == NULL){
            printf("Error: key\n");
            return 1;
        }
        printf("Open text: %s\n", text);
        char *shifrtext = Perectanovka(text, key);
        if(shifrtext == NULL){
            return 1;
        }
        printf("Shifr text: %s\n", shifrtext);
        char *detext = DePerestanovka(shifrtext, key);
        if(detext == NULL)
            return 1;
        printf("Decode text: %s\n", detext);
        //если введено куда записывать, не обязательно наличие файла
        if(argc > 3){
            opf = fopen(argv[3], "w");
            i = 0;
            while(shifrtext[i] != '\0'){
                putc(shifrtext[i], opf);
                i++;
            }
            fclose(opf);
            printf("Write file shifrtext\n");
        }
        if(str_comp(text, detext) == 0)
            printf("text == decode text\n");
        else
            printf("text != decode text\n");
    }
    return 0;
}











