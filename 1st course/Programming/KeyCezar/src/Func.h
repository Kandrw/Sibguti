//Структура для хранения русского или англ символа
//Если русский символ, то код хранится в s1 и s2
//Если англ, то код хранится в s1, s2 = 0 всегда
typedef struct char2{
    int s1, s2;
}char2;

char2 **char_to_char2(char *s);
char2 **alphabet(int RU_EN);
//Проверка наличия символа в строке
int found(char2 **text, int c1, int c2, int start, int end);
char2 **alphabet_key(char2 **alp1, char2 **key, int k);
//Вывод массива указателей структуры char2
void print_char2(char2 **A);
char2 **OpenFile(char *fn);