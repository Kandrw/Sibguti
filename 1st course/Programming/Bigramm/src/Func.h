typedef struct string{
    int ru_en;
    int c1, c2;
}string;
int Search(char *text, int st, int end, char c );
int Search2(char *text, char c1, char c2);
char *CreateEN(char *fr);
string **CreateRU(char *fr);
int str_comp(char s1[], char s2[]);
string** char_to_str(char *t);
void print_str(string **S);
void print_tabl(string **S);
int srv_str(string **s1, string **s2);