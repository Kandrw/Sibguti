#include <stdio.h>
#include <stdlib.h>
//Струтура хранения символа, с2 - хранит код если символ двухбайтный(русский)
typedef struct string{
    unsigned char c1, c2;
}string;
//Струтура хранения символа, с2 - хранит код если символ двухбайтный(русский)
//для возможности обхода без индексов
typedef struct string_t{
    unsigned char c1, c2;
    struct string_t *next;
}string_t;
//структура словаря
typedef struct dict{
    string **ru, **en;//слово на русском и на английском
    struct dict *next;//следующая стуртура со словами
}dict;
//Чтение текста из файла и преобразование его в стуктуру string**
string **Readtext(char *F){
    FILE *file = fopen(F, "r");
    if(file == NULL)
        return NULL;
    unsigned int c;//для присваивания к беззнаковому типу 
    int cs;
    int len = 0, con = 0;
    //Подсчет длинны
    while((cs = getc(file)) != EOF){
        c = cs;
        if(con == 1){
            len++;
            con = 0;
        }
        else if(c == 208 || c == 209 || c == 210)
            con = 1;
        else
            len++;
    }
    fseek(file,0L,SEEK_SET);//перевод каретки в начало файла 
    string ** str = (string**)malloc(sizeof(string*) * (len+1));
    str[len] = NULL;
    int i = 0; con = 0;
    //Повторное чтение файла но уже с данные записываются
    while((cs = getc(file)) != EOF){
        c = cs;
        if(con == 1){
            str[i]->c2 = c;//второй байт кириллицы
            i++;
            con = 0;
        }
        //если кириллица
        else if(c == 208 || c == 209 || c == 210){
            con = 1;
            str[i] = (string*)malloc(sizeof(string));
            str[i]->c1 = c;
        }
        //однобайтный символ
        else{
            str[i] = (string*)malloc(sizeof(string));
            str[i]->c1 = c;
            str[i]->c2 = 0;
            i++;
        }
    }
    return str;
}
//Чтение словаря из файла и запись в структуру
dict *ReadDict(char *FN){
    FILE *file = fopen(FN, "r");
    if(file == NULL){
        printf("Файл со словарем не найден: %s\n", FN);
        return NULL;
    }
    //1 чтение файла: подсчет слов в словаре
    unsigned int c;
    int cs;
    int lenD = 0;
    int k1;
    while((cs = getc(file)) != EOF){
        c = cs;
        if(k1 == 3){
            k1 = 0;
            lenD += 2;
        }
        else if(c == ' ' || c == '-'){//Разделение слов в словаре(" - ")
            k1++;
        }
        else{
            k1 = 0;
        }
    }
    int *Dr = (int*)malloc(sizeof(int) * lenD);//Хранение длинны каждого слова в файле
    fseek(file,0L,SEEK_SET);
    //2 чтение файла: подсчет длинны каждого слова в словаре
    k1 = 0;
    int lenstr = 0, k2 = 0;
    int i = 0;
    while((cs = getc(file)) != EOF){
        c = cs;
        if(k1 == 2 || c == '\n'){
            k1 = 0;
            k2 = 0;
            if(lenstr == 0){//если длинна слова равна 0
                printf("Неверная структура словаря\n");
                fclose(file);
                return NULL;
            }
            Dr[i] = lenstr;
            i++;
            lenstr = 0;
        }
        else if(c == ' ' || c == '-')
            k1++;
        else{
            k1 = 0;
            if(k2 == 1){
                lenstr++;
                k2 = 0;
            }
            else if(c == 208 || c == 209 || c == 210){
                k2 = 1;

            }
            else{
                lenstr++;
            }
        }
    }
    Dr[i] = lenstr;//длинна последнего слова
    fseek(file,0L,SEEK_SET);
    //3 чтение файла: заполение структуры словаря
    dict *head = (dict*)malloc(sizeof(dict));//начало словаря
    head->en = NULL;
    head->ru = NULL;
    head->next = NULL;
    dict *ptr = head;//перемещение по словарю
    i = 0; k1 = 0; k2 = 0;
    int k3 = 1, i2 = 0;
    //k1 - разделение(" - " или '\n') между словами
    //k2 - для русских символов
    //k3 - для русского(1) или английского слова(2)
    ptr->ru = (string**)malloc(sizeof(string*) * (Dr[0]+1));//выделение памяти под первое слово
    ptr->ru[Dr[0]] = NULL;
    while((cs = getc(file)) != EOF){
        c = cs;
        //разделитель в файле
        if(k1 >= 2 || c == '\n'){
            k1 = 0;
            k2 = 0;
            i++;
            i2 = 0;
            //Если перенос строки то выделение памяти(для англ слова позднее)
            if(c == '\n'){
                k3 = 1;
                ptr->next = (dict*)malloc(sizeof(dict));
                ptr->next->en = NULL;
                ptr->next->ru = (string**)malloc(sizeof(string*) * (Dr[i] + 1));
                ptr->next->ru[Dr[i]] = NULL;
                ptr->next->next = NULL;
                ptr = ptr->next;
            }
            //для англ слова
            else{
                ptr->en = (string**)malloc(sizeof(string*) * (Dr[i]+1));
                ptr->en[Dr[i]] = NULL;
                k3 = 2;
            }
        }
        else if(c == ' ' || c == '-')
            k1++;
        else{
            k1 = 0;
            if(k2 == 1){
                if(k3 == 2){
                    ptr->en[i2]->c2 = c;
                }
                else{
                    ptr->ru[i2]->c2 = c;
                }
                i2++;
                k2 = 0;
            }
            //Если символ с двумя байтами
            //Предусмотрена возможность перевода наоборот(с англ на русский)
            else if(c == 208 || c == 209 || c == 210){
                k2 = 1;
                if(k3 == 2){
                    ptr->en[i2] = (string*)malloc(sizeof(string));
                    ptr->en[i2]->c1 = c;
                }
                else{
                    ptr->ru[i2] = (string*)malloc(sizeof(string));
                    ptr->ru[i2]->c1 = c;
                }
            }
            //символ однобайтовый
            else{
                if(k3 == 2){
                    ptr->en[i2] = (string*)malloc(sizeof(string));
                    ptr->en[i2]->c1 = c;
                    ptr->en[i2]->c2 = 0;
                }
                else{
                    ptr->ru[i2] = (string*)malloc(sizeof(string));
                    ptr->ru[i2]->c1 = c;
                    ptr->ru[i2]->c2 = 0;
                }
                i2++;
            }
        }
    }
    return head;
}
//вывод текста(в программе не используется)
void print(string **mass){
    int i = 0;
    while(mass[i] != NULL){
        if(mass[i]->c2 == 0)
            printf("%c", mass[i]->c1);
        else
            printf("%c%c", mass[i]->c1, mass[i]->c2); 
        i++;
    }
    printf("\n");
}
//вывод неполного текста(для отладки, в программе не используется)
void printT(string **mass, int st, int end){
    int i = st;
    while(i < end){
        if(mass[i]->c2 == 0)
            printf("%c", mass[i]->c1);
        else
            printf("%c%c", mass[i]->c1, mass[i]->c2); 
        i++;
    }
    printf("\n");
}
//вывод текста
void print_t(string_t *str){
    string_t *ptr = str;
    while(ptr != NULL){
        if(ptr->c2 == 0)
            printf("%c", ptr->c1);
        else
            printf("%c%c", ptr->c1, ptr->c2); 
        ptr = ptr->next;
    }
    printf("\n");
}
//вывод словаря(не используется)
void prit_dict(dict *head){
    dict *ptr = head;
    while(ptr != NULL){
        print(ptr->ru); printf(" - "); print(ptr->en);
        printf("\n");
        ptr = ptr->next;
    }
}
//Поиск слова в словаре
string **SearchDict(string **str, int start, int end, dict *D){//текст, откуда, до куда, словарь
    dict *ptr = D;
    int i, i2;
    int c;
    //Перебор словаря
    while(ptr != NULL){
        i = 0;
        i2 = start;
        c = 1;
        while(ptr->ru[i] != NULL && i2 < end){
            if(!(ptr->ru[i]->c1 == str[i2]->c1 && ptr->ru[i]->c2 == str[i2]->c2)){
                c = 0;
                break;
            }
            ++i;
            ++i2;
        }
        //слово найдено
        if(c == 1 && i2 != start && i2 == end && ptr->ru[i] == NULL)
            return ptr->en;
        ptr = ptr->next;
    }
    return NULL;
}
//Перевод текста по словарю
string_t *Translate(dict *D, string **text){
    string_t *head = (string_t*)malloc(sizeof(string_t));//первый символ переведеного слова
    string_t *ptr = head;//хранение последней позиции с переведеном тексте(для присоедние символов)
    string **en = NULL;
    int i = 0, i2 = 0, i3;
    //i - обход текста и конец слова которое подается в словарь
    //i2 - начало слова которое подается в словарь
    //i3 - для обхода переведенного слова(или если же не удалось перевести слово, то записывается оно) и запись в перевденый текст
    while(text[i] != NULL){
        //разделители слов в тексте
        if(text[i]->c1 == ' ' || text[i]->c1 == '.' || text[i]->c1 == ',' || text[i]->c1 == '\n'){
            en = SearchDict(text, i2, i, D);
            //слово удалось перевести
            if(en != NULL){
                i3 = 0;
                //запись в переведный текст
                while(en[i3] != NULL){
                    ptr->next = (string_t*)malloc(sizeof(string_t));
                    ptr->next->c1 = en[i3]->c1;
                    ptr->next->c2 = en[i3]->c2;
                    ptr = ptr->next;
                    ++i3;
                }
            }
            //слово не удалось перевести
            else{
                i3 = i2;
                //запись в переведынй текст то что не удлось перевести
                while(i3 < i){
                    ptr->next = (string_t*)malloc(sizeof(string_t));
                    ptr->next->c1 = text[i3]->c1;
                    ptr->next->c2 = text[i3]->c2;
                    ptr = ptr->next;
                    ++i3;
                }
            }
            //запись разделителей в тексте
            ptr->next = (string_t*)malloc(sizeof(string_t));
            ptr->next->c1 = text[i]->c1;
            ptr->next->c2 = text[i]->c2;
            ptr = ptr->next;
            i2 = i+1;
        }
        i++;
    }
    //корень переведеного текста не хранит информации поэтому он удаляется и вместо него записывается следующий
    ptr->next = NULL;
    ptr = head;
    head = head->next;
    free(ptr);
    return head;
}

int main(int argc, char *argv[]){
    system("chcp 65001");//смена кодировки для вывода кириллице в консоль
    //Если аргументов консоле достаточно
    if(argc >= 3){
        string **str = Readtext(argv[1]);
        if(str == NULL){
            printf("Файл с текстом не найден: %s\n", argv[1]);
            return 1;
        }
        dict *D = ReadDict(argv[2]);
        if(D == NULL){  
            return 1;
        }
        string_t *t_str = Translate(D, str);
        if(t_str == NULL){
            return 1;
        }
        //Если также введен файл для записи
        if(argc >= 4){
            FILE *file = fopen(argv[3], "w");
            string_t *ptr = t_str;
            //запись в файл
            while(ptr != NULL){
                if(ptr->c2 == 0){
                    putc(ptr->c1, file);
                }
                else{
                    putc(ptr->c1, file);
                    putc(ptr->c2, file);
                }
                ptr = ptr->next;

            }
            fclose(file);
            printf("Текст записан в файл %s\n", argv[3]);
        }
        //иначе вывод переведеного текста в консоль
        else{
            printf("Файл для записи не введен\n");
            printf("Переведеный текст:\n");
            print_t(t_str);
        }
        return 0;
    }
    else{
        printf("Недостаточно аргументов в командной строке\n");
        printf("Аргументы: \n\tфайл с текстом\n\tфайл со словарем\n\tкуда записывается перевод(необязательно)\n");
        return 1;
    }
}