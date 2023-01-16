#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Polibi.h"
#include "DePolibi.h"
//Сравнение строк
int str_comp(char s1[], char s2[]){
    for (int i = 0; ; i++){
        if (s1[i] != s2[i])
            return s1[i] < s2[i] ? -1 : 1;
        if (s1[i] == '\0')
            return 0;
    }
}
//Главная функция
int main(int argc, char *argv[]){
    //Аргументы вводом
    if(argc == 1){
        int LM = 100;//макс длинна
        int i = 0;
        char *text = (char*)malloc(sizeof(char) * LM);//Что зашифровать
        printf("Input text: ");
        fgets(text, LM, stdin);//Чтение
        while(text[i] != '\0'){//при использование fgets вместо '\0' в конце код символа 10, эта штуковина это исправляет 
            if(text[i] == 10){
                text[i] = '\0';
                break;
            }
            i++;
        }
        char *kodslovo =  (char*)malloc(sizeof(char) * 7);//Код слово
        i = 0;
        printf("Input kod slovo(bez povtoreni): ");
        fgets(kodslovo, 7, stdin);
        while(kodslovo[i] != '\0'){
            if(kodslovo[i] == 10){
                kodslovo[i] = '\0';
                break;
            }
            i++;
        }
        key *K = GenerateKey(kodslovo);//Создание ключа из код слова
        if(K == NULL)
            return 1;
        printf("Open text: %s\n", text);
        char *shifrtext = Polibi(text, K);
        printf("Zashifr text: %s\n", shifrtext);
        char *rasshifrtext = DePolibi(shifrtext, K);
        printf("Rasshifr text: %s\n", rasshifrtext);
        if(str_comp(text, rasshifrtext) == 0){
            printf("text == rashifrtext\n");
        }
        else{
            printf("text != rashifrtext\n");
        }
    }
    //Если в командной строке есть аргументы (имя файла откуда читать, куда записывать(если есть), код слово(если есть))
    else{
        FILE *file;
        file = fopen(argv[1],"r" );//Открытие файла
        if(file == NULL){
            printf("Not found file\n");
            return 1;
        }
        char p;
        int n = 0, i =0;
        //Длинна слова в файле
        while((p = getc(file)) != EOF){
            n++;
        }
        if(n <= 0){
            printf("File pyst\n");
            fclose(file);
            return 1;
        }
        char *text = (char*)malloc(sizeof(char) * n);//Слово для зашифр
        i = 0;
        fseek(file,0L,SEEK_SET);//коретка в конец файла, для повторного чтения
        //Чтение
        while((p = getc(file)) != EOF){
            text[i] = p;
            ++i;
        }
        fclose(file);
        key *K = NULL;
        //Если в консоле нет кодового слова
        if(argc == 3){
            char *kodslovo =  (char*)malloc(sizeof(char) * 7);
            i = 0;
            printf("Input kod slovo(bez povtoreni): ");
            fgets(kodslovo, 7, stdin);//То вводим код слово
            while(kodslovo[i] != '\0'){
                if(kodslovo[i] == 10){
                    kodslovo[i] = '\0';
                    break;
                }
                i++;
            }
            K = GenerateKey(kodslovo);
        }
        //Иначе берем из консоли
        else{
            K = GenerateKey(argv[3]);
        }
        if(K == NULL){
            return 1;
        }
        printf("Open text: %s\n", text);
        char *shifrtext = Polibi(text, K);
        
        printf("Zashifr text: %s\n", shifrtext);
        char *rasshifrtext = DePolibi(shifrtext, K);
        printf("Rasshifr text: %s\n", rasshifrtext);
        if(str_comp(text, rasshifrtext) == 0){
            printf("text == rashifrtext\n");
        }
        else{
            printf("text != rashifrtext\n");
        }
        //Если в консоле введено имя файла куда записывать
        if(argc > 2){
            file = fopen(argv[2], "w");
            i = 0;
            while(shifrtext[i] != '\0'){
                putc(shifrtext[i], file);
                i++;
            }
            fclose(file);
            printf("Write file shifrtext\n");
        }
    }
}
