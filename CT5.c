#include <stdio.h>
#include <stdlib.h>

// TASK 5
// VECTOR:
struct st_vec{                            //list
    int count;
    char ch[256];
    long long hash;
    struct st_vec *next;
}; typedef struct st_vec vector;

vector *add_vec(vector *top, char *x){

    vector *nw = (vector*)malloc(sizeof(vector));
    top->next = nw;
    nw->next = NULL;
    strcpy(nw->ch, x);
    return nw;
}

void quit(vector *cur){

    while (cur != NULL){
        vector *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    return;
}
// END OF VECTOR

// HASHMAP:
// BLOCK 1: structs and auxiliary function

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

// BLOCK 2: functions

void create(int(*func)(char*), int sz){            // create hashmap

    int i;
    tbl.size = sz;
    tbl.arr = (array*)malloc(sz * sizeof(array));
    tbl.callback = func;
    for (i = 0; i < sz; i++){
        tbl.arr[i].v = malloc(1 * sizeof(vector));
        tbl.arr[i].v->next = NULL;
        tbl.arr[i].v->count = 0;
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

void add(char *ch, int x){                                      //add a string in hashmap

    vector *cur = find(ch);
    if (cur->next == NULL){ // new elem
        vector *nw = (vector*)malloc(sizeof(vector));
        cur->next = nw;
        nw->next = NULL;
        nw->count = x;
        nw->hash = call_hash_func(tbl.callback, ch);;
    } else {
        cur = cur->next;
        cur->count += x;
    }

    return;
}

int count(char *ch){

    vector *cur = find(ch);
    if (cur->next == NULL){
        return 0;
    } else {
        cur = cur->next;
        return cur->count;
    }

    return 0;
}

// END OF HASHMAP

void print(vector *cur){

    while (cur != NULL){
        printf("%s -> ", cur->ch);
        printf("%d\n", count(cur->ch));
        cur = cur->next;
    }
    return;
}

void TASK5(){

    vector *head = (vector*)malloc(sizeof(vector));
    head->next = NULL;
    vector *top;
    top = head;
    create(hash_func_stable, 10231);

    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        char s[256];
        scanf("%s", s);
        if (count(s) == 0){
            top = add_vec(top, s);
        }
        add(s, 1);
    }
    print(head->next);
    quit(head);
    del();

    return;
}

// END OF TASK 5

int main(){

    TASK5();
    return 0;
}
