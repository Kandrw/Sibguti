//структура для возврата данных из алгоритма
typedef struct _info{
    int N;//размер набора
    int iteration;//количество итераций
    int *arrayS;//набор
}info;
int *Create(int len, int m1, int m2);
int dchar(char *s);

int sum_arr(int *D, int n);
int *join_array(int *A, int n1, int *B, int n2);
void fast_sort(int* s_arr, int first, int last, int *yp[], int *psize, int *iter);
int search_bin(int *s2, int n, int el);

