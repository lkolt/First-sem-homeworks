#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// BLOCK 1: structs and auxiliary function

struct st_vec{                            //list
    int count;
    long long hash;
    struct st_vec *next;
}; typedef struct st_vec vector;

struct hash_array{                        // list of list
    vector *v;
}; typedef struct hash_array array;

struct hash_table{                        // hashmap
    int size;                             // size of hashmap
    array *arr;                           // array of list
    int (*callback)(char*);               // hash function
}; typedef struct hash_table table;
table tbl;

int hash_func_const(char *ch){               // constant hash function

    return 11;
}

int hash_func_count(char *ch){               // sum alphabet hash function

    int sum = 0;
    while (*ch){
        sum += *ch;
        ch++;
    }

    return sum;
}

int hash_func_stable(char *ch){              // stable hash function

    const int P = 239;            // prime > size of alphabet
    long long hash = 0;
    while (*ch){
        hash = hash * P + *ch;
        ch++;
    }

    return hash;
}

typedef int (*callback_param_func)(char *param);            //call hash_function from hashmap
int call_hash_func(callback_param_func func, char *param){
    return func(param);
}

void clean_vector(vector *cur){                       // free vector

    while (cur != NULL){
        vector *tmp = cur;
        cur = cur->next;
        free(tmp);
    }

    return;
}

vector *find(char *ch){                                    //find position string in hashmap

    long long Hsh = call_hash_func(tbl.callback, ch);
    int pos = (Hsh % tbl.size + tbl.size) % tbl.size;
    vector *cur = tbl.arr[pos].v;

    while (cur->next != NULL){
        vector *tmp = cur->next;
        if (tmp->hash == Hsh){
            break;
        }
        cur = cur->next;
    }

    return cur;
}

int min(int a, int b){  // min(a, b)

    if (a < b){
        return a;
    } else {
        return b;
    }
}

int max(int a, int b){  // max(a, b);

    if (a > b){
        return a;
    } else {
        return b;
    }
}

int check_symb(char c){

    if (((c >= 'a') && (c <= 'z')) || ((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'A'))){
        return 1;
    }
    return 0;
}

// BLOCK 2: functions

void create(int(*func)(char*), int sz){            // create hashmap

    int i;
    tbl.size = sz;
    tbl.arr = (array*)malloc(sz * sizeof(array));
    tbl.callback = func;
    for (i = 0; i < sz; i++){
        tbl.arr[i].v = malloc(1 * sizeof(vector));
        (tbl.arr[i].v)->next = NULL;
        (tbl.arr[i].v)->count = 0;
    }

    return;
}

void del(){                                           // free hashmap

    int i;
    int size = tbl.size;
    for (i = 0; i < size; i++){
        clean_vector(tbl.arr[i].v);
    }
    free(tbl.arr);

    return;
}

void add(char *ch){                                      //add a string in hashmap

    vector *cur = find(ch);
    if (cur->next == NULL){ // new elem
        vector *nw = (vector*)malloc(sizeof(vector));
        cur->next = nw;
        nw->next = NULL;
        nw->count = 1;
        nw->hash = call_hash_func(tbl.callback, ch);;
    } else {
        cur = cur->next;
        cur->count++;
    }

    return;
}

void erase(char *ch){  // delete one string ch out of hashmap

    vector *cur = find(ch);
    if (cur->next == NULL){
        printf("Ooops, no found this string =(\n");
    } else {
        cur = cur->next;
        if (cur->count == 0){
            printf("We cant remove this, because we haven't it =(\n");
        } else {
            cur->count--;
        }
    }

    return;
}

void count(char *ch){

    vector *cur = find(ch);
    printf("The number of occurrences: ");
    if (cur->next == NULL){
        printf("0\n");
    } else {
        cur = cur->next;
        printf("%d\n", cur->count);
    }

    return;
}

void statistic(){

    int i = 0;
    int number_cells = 0;
    int number_elem = 0;
    int sum_len_chain = 0;
    int max_len_chain = 0;
    int min_len_chain = 1e9;
    int max_elem = 0;
    int mid_len_chain = 0;
    for (i = 0; i < tbl.size; i++){
        vector *cur = tbl.arr[i].v;
        int cur_len = 0;
        while (cur != NULL){
            cur_len++;
            number_elem += cur->count;
            max_elem = max(max_elem, cur->count);
            cur = cur->next;
        }
        cur_len--;

        if (cur_len > 0){
            number_cells++;
            min_len_chain = min(min_len_chain, cur_len);
        }

        sum_len_chain += cur_len;
        max_len_chain = max(max_len_chain, cur_len);

    }
    if (number_cells != 0){
        mid_len_chain = sum_len_chain / number_cells;
    }
    if (min_len_chain == 1e9){
        min_len_chain = -1;
    }

    printf("Number of using cells: %d\n", number_cells);
    printf("Number of elements: %d\n", number_elem);
    printf("Average length of chains: %d\n", mid_len_chain);
    printf("Minimal length of chains: %d\n", min_len_chain);
    printf("Maximal length of chains: %d\n", max_len_chain);
    printf("Maximal element: %d\n", max_elem);

    return;
}

int main()
{
    double start = clock();

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    const int size = 50511; // size of hashmap;
    create(hash_func_stable, size);

    char ch[100];
    while (scanf("%s", ch) != EOF){
        size_t len = strlen(ch) - 1;
        while (len >= 0 && !check_symb(ch[len])){
            ch[len] = '\0';
            len--;
        }
        add(ch);
    }
    statistic();
    del();
    printf("%f", (clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
