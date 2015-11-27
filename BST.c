#include <stdio.h>
#include <stdlib.h>

struct BST{
    int x;
    struct BST *l;
    struct BST *r;
}; typedef struct BST tree;

struct stable_tree{
    tree *head;
} T;

void init(){

    tree *head;
    head = (tree*)malloc(sizeof(tree));
    if (head == NULL){
        printf("Nothing memory\n");
        return;
    }
    head->l = head->r = NULL;
    head->x = 0;
    T.head = head;

    return;
}

tree *new_point(int x){

    tree *tmp = (tree*)malloc(sizeof(tree));
    if (tmp == NULL){
        printf("Nothing memory\n");
        return;
    }
    tmp->x = x;
    tmp->l = tmp->r = NULL;

    return tmp;
}

void add(int x){

    tree *head = T.head;
    if (head->r == NULL){
        head->r = new_point(x);
        return;
    }

    tree *cur = head->r;
    while (1){
        if (cur->x < x){
            if (cur->r == NULL){
                cur->r = new_point(x);
                return;
            }
            cur = cur->r;
        } else {
            if (cur->l == NULL){
                cur->l = new_point(x);
                return;
            }
            cur = cur->l;
        }
    }

    return;
}

void erase(int x){

    tree *head = T.head;
    tree *cur = head->r;
    tree *last = head;
    int way = 1;
    while (1){
        if (cur == NULL){
            printf("Nothing to erase!!!\n");
            return;
        }

        if (x == cur->x){
            if (cur->r == NULL){
                cur->r = cur->l;
                cur->l = NULL;
            }
            if (way == 1){
                last->r = cur->r;
            } else {
                last->l = cur->r;
            }
            if (cur->r == NULL){
                free(cur);
                return;
            }

            tree *tmp = cur->r;
            while (tmp->l != NULL){
                tmp = tmp->l;
            }
            tmp->l = cur->l;
            free(cur);
            return;
        }
        last = cur;
        if (cur->x > x){
            cur = cur->l;
            way = 0;
        } else {
            cur = cur->r;
            way = 1;
        }
    }

    return;
}

int check(int x){

    tree *head = T.head;
    if (head->r == NULL){
        return 0;
    }

    tree *cur = head->r;
    while (1){
        if (cur == NULL){
            return 0;
        }
        if (cur->x == x){
            return 1;
        }
        if (cur->x > x){
            cur = cur->l;
        } else {
            cur = cur->r;
        }
    }
}

void print_min(tree *cur){

    if (cur == NULL){
        return;
    }

    print_min(cur->l);
    printf("%d ", cur->x);
    print_min(cur->r);

    return;
}

void print_max(tree *cur){

    if (cur == NULL){
        return;
    }

    print_max(cur->r);
    printf("%d ", cur->x);
    print_max(cur->l);

    return;
}

void print_debug(tree *cur, int k){

    if (cur == NULL){
        return;
    }

    print_debug(cur->l, k + 1);
    int i;
    for (i = 0; i < k; i++){
        printf(" ");
    }
    printf("%d\n", cur->x);
    print_debug(cur->r, k + 1);

    return;
}

void print(int r){

    tree *head = T.head;
    if (head->r == NULL){
        return;
    }

    tree *cur = head->r;
    if (r == 0){
        print_min(cur);
    }
    if (r == 1){
        print_max(cur);
    }
    if (r == 2){
        print_debug(cur, 0);
    }
    printf("\n");

    return;
}

void del(tree *cur){

    if (cur == NULL){
        return;
    }
    del(cur->l);
    del(cur->r);
    free(cur);

    return;
}

int main(){

    init();

    while (1){
        char c;
        int x;
        scanf("%c %d", &c, &x);
        if (c == 'a'){
            add(x);
        }

        if (c == 'r'){
            erase(x);
        }

        if (c == 'c'){
            check(x);
        }

        if (c == 'p'){
            print(x);
        }

        if (c == 'q'){
            del(T.head);
            break;
        }
    }

    return 0;
}
