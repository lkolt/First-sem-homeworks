#include <stdio.h>
#include <stdlib.h>

struct st_vec{
    int value;
    struct st_vec *next;
};

typedef struct st_vec vector;

int check_cycle(vector *head){

    vector *step1 = head;
    vector *step2 = head;
    step2 = step2->next;
    while (step1 != step2){
        step2 = step2->next;
        if (step2 == NULL){
            break;
        }
        step2 = step2->next;
        if (step2 == NULL){
            break;
        }

        step1 = step1->next;
        if (step1 == NULL){
            break;
        }
    }

    if (step1 == step2){
        return 1;
    }

    return 0;
}

void create_cycle(vector *head){
  
    vector *tmp = (vector*)malloc(sizeof(vector));
    head->next = tmp;
    vector *nw = (vector*)malloc(sizeof(vector));
    tmp->next = nw;
    nw->next = head;
    return;
}

vector *add(vector *top, int x){

    vector *nw = (vector*)malloc(sizeof(vector));
    top->next = nw;
    nw->next = NULL;
    nw->value = x;
    return nw;
}

void erase(vector *cur, int x){

    while (cur != NULL){
        vector *tmp = cur->next;
        if (tmp != NULL && tmp->value == x){
            break;
        }
        cur = cur->next;
    }

    if (cur == NULL){
        return;
    }

    vector *tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    return;
}

void print(vector *cur){

    while (cur != NULL){
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
    return;
}

void quit(vector *cur){

    while (cur != NULL){
        vector *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    return;
}

int main(){

    vector *head = (vector*)malloc(sizeof(vector));
    head->next = NULL;
    head->value = 0;
    vector *top;
    top = head;

    while (1){
        char c;
        scanf("%c", &c);

        if (c == 'a'){
            int x;
            scanf("%d", &x);
            top = add(top, x);
        }

        if (c == 'r'){
            int x;
            scanf("%d", &x);
            erase(head, x);
        }

        if (c == 'p'){
            print(head->next);
        }

        if (c == 'c'){
            if (check_cycle(head) == 1){
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }

        if (c == 'x'){
            create_cycle(top);
        }

        if (c == 'q'){
            quit(head->next);
            break;
        }
    }

    return 0;
}
