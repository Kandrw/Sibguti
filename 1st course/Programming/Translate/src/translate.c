#include <stdio.h>
#include <stdlib.h>
typedef struct string{
    unsigned char c1, c2;
}string;
typedef struct string_t{
    unsigned char c1, c2;
    struct string_t *next;
}string_t;
typedef struct dict{
    string **ru, **en;
    struct dict *next;
}dict;
string **Readtext(char *F){
    FILE *file = fopen(F, "r");
    if(file == NULL)
        return NULL;
    unsigned int c;
    int cs;
    int len = 0, con = 0;
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
    fseek(file,0L,SEEK_SET);
    string ** str = (string**)malloc(sizeof(string*) * (len+1));
    str[len] = NULL;
    int i = 0; con = 0;
    while((cs = getc(file)) != EOF){
        c = cs;
        if(con == 1){
            str[i]->c2 = c;
            i++;
            con = 0;
        }
        else if(c == 208 || c == 209 || c == 210){
            con = 1;
            str[i] = (string*)malloc(sizeof(string));
            str[i]->c1 = c;
        }
        else{
            str[i] = (string*)malloc(sizeof(string));
            str[i]->c1 = c;
            str[i]->c2 = 0;
            i++;
        }
    }
    return str;
}
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
        else if(c == ' ' || c == '-'){
            k1++;
        }
        else{
            k1 = 0;
        }
    }
    if(lenD > 10000){
        printf("Словарь слишком большой\n");
        fclose(file);
        return NULL;
    }
    int *Dr = (int*)malloc(sizeof(int) * lenD);
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
            if(lenstr == 0){
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
    Dr[i] = lenstr;
    fseek(file,0L,SEEK_SET);
    //3 чтение файла: заполение структуры словаря
    dict *head = (dict*)malloc(sizeof(dict));
    head->en = NULL;
    head->ru = NULL;
    head->next = NULL;
    dict *ptr = head;
    i = 0; k1 = 0; k2 = 0;
    int k3 = 1, i2 = 0;
    //k1 - разделение(" - " или '\n') между словами
    //k2 - для русских символов
    //k3 - для русского(1) или английского слова(2)
    ptr->ru = (string**)malloc(sizeof(string*) * (Dr[0]+1));
    ptr->ru[Dr[0]] = NULL;
    while((cs = getc(file)) != EOF){
        c = cs;
        if(k1 >= 2 || c == '\n'){
            k1 = 0;
            k2 = 0;
            i++;
            i2 = 0;
            if(c == '\n'){
                k3 = 1;
                ptr->next = (dict*)malloc(sizeof(dict));
                ptr->next->en = NULL;
                ptr->next->ru = (string**)malloc(sizeof(string*) * (Dr[i] + 1));
                ptr->next->ru[Dr[i]] = NULL;
                ptr->next->next = NULL;
                ptr = ptr->next;
            }
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
void prit_dict(dict *head){
    dict *ptr = head;
    while(ptr != NULL){
        print(ptr->ru); printf(" - "); print(ptr->en);
        printf("\n");
        ptr = ptr->next;
    }
}
string **SearchFile(string **str, int start, int end, dict *D){
    dict *ptr = D;
    int i, i2;
    int c;
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
        if(c == 1 && i2 != start && i2 == end && ptr->ru[i] == NULL)
            return ptr->en;
        ptr = ptr->next;
    }
    return NULL;
}

string_t *Translate(dict *D, string **text){
    string_t *head = (string_t*)malloc(sizeof(string_t));
    string_t *ptr = head;
    string **en = NULL;
    int i = 0, i2 = 0, i3;
    int st1 = 0, st2 = 0;
    while(text[i] != NULL){
        if(text[i]->c1 == ' ' || text[i]->c1 == '.' || text[i]->c1 == ',' || text[i]->c1 == '\n'){
            en = SearchFile(text, i2, i, D);
            if(en != NULL){
                i3 = 0;
                while(en[i3] != NULL){
                    ptr->next = (string_t*)malloc(sizeof(string_t));
                    ptr->next->c1 = en[i3]->c1;
                    ptr->next->c2 = en[i3]->c2;
                    ptr = ptr->next;
                    ++i3;
                }
            }
            else{
                i3 = i2;
                while(i3 < i){
                    ptr->next = (string_t*)malloc(sizeof(string_t));
                    ptr->next->c1 = text[i3]->c1;
                    ptr->next->c2 = text[i3]->c2;
                    ptr = ptr->next;
                    ++i3;
                }
            }
            ptr->next = (string_t*)malloc(sizeof(string_t));
            ptr->next->c1 = text[i]->c1;
            ptr->next->c2 = text[i]->c2;
            ptr = ptr->next;
            i2 = i+1;
        }
        i++;
    }
    ptr->next = NULL;
    ptr = head;
    head = head->next;
    free(ptr);
    return head;
}

int main(int argc, char *argv[]){
    system("chcp 65001");
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
        if(argc >= 4){
            FILE *file = fopen(argv[3], "w");
            string_t *ptr = t_str;
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