typedef struct key{
    char *slovo;//кодовое слово
    char *kvad;//Квадрат полибия
    int a;//Размер код слова и строки квадрата

}key;
//Предопределения функций, для многофайловости
key *GenerateKey(char *sl);
char* Polibi(char *text, key *K);