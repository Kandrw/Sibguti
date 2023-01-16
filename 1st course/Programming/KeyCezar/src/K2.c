#include <stdlib.h>
#include <stdio.h>
#include "Func.h"
#include "KeyCezar.h"
#include "DeKeyCezar.h"


int main(int argc, char *argv[]){
    system("chcp 65001");
    int LIM = 100;
    int r1 = 100;
    if(argc < 4){
        printf("Недостаточно аргументов в командной строке\n");
        printf("Аргументы: \n\tимя файла с текстом\n\tимя файла с ключем\n\tпозиция(если нет то 0)\n\tкуда записывается зашифрованый текст(не обязательно)\n");
        return 1;
    }
    else{   
        int RU_EN;
        printf("Введите 1 если работа с файлы содержат русские символы или 2 если английские:\t\n");
        scanf("%d%*c", &RU_EN);
        printf("\n");
        char2 **text = OpenFile(argv[1]);
        if(text == NULL){
            return 1;
        }
        printf("Текст: ");
        print_char2(text);
        char2 **key = OpenFile(argv[2]);
        printf("Ключевая фраза: ");
        print_char2(key);
        printf("Алфавит: ");
        char2 **alp1 = NULL, **alp2 = NULL; 
        alp1 = alphabet(RU_EN);
        
        print_char2(alp1);
        int k = 0;
        if(argc >= 4){
            k = atoi(argv[3]);
            if(k <= 0 || k > 33){
                printf("Значение не подходит(по умолчанию 0): %s\n", argv[3]);
                k = 0;
            }
        }
        alp2 = alphabet_key(alp1, key, k );
        printf("Алфавит-ключ: ");
        print_char2(alp2);
        printf("Зашифрованный текст: ");
        char2 **text2 = KeyCezar(alp1, alp2, text);
        print_char2(text2);
        printf("Расшифрованный текст: ");
        char2 **text3 = DeKeyCezar(alp1, alp2, text2);
        print_char2(text3);


    }
    printf("Exit\n");
    return 0;
}


