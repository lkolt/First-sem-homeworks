// BLOCK 1: VAR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UNKNOWN -1
#define ld 0
#define st 1
#define ldc 2
#define add 3
#define sub 4
#define cmp 5
#define jump 6
#define br 7
#define hlt 8
#define size_m 262144
#define maxn_s 255

struct instruction{
    int type;
    int jmp;
    int val;
};

struct search{
    char *str;
    int id;
};

// size_m = 262144 = 2^18 - size of memory & stack
// maxn_s = 255 - max size of string
int stack[size_m];
int top = 0;
int memory[size_m];
struct instruction arr[size_m];
int id = 0;
char *mark_arr[size_m];
struct search jmp_arr[size_m];
int cnt_jmp = 0;
char *com_string[9] = {"ld", "st", "ldc", "add", "sub", "cmp", "jmp", "br", "hlt"};

// BLOCK 2: additional functions

inline int pop(){       // pop out of stack
    top--;

    return stack[top];
}

inline void push(int val){ // add into stack
    stack[top] = val;
    top++;

    return;
}

void free_mark(){         // free memory
    int i;
    for (i = 0; i < id; i++){
        free(mark_arr[i]);
    }
    for (i = 0; i < cnt_jmp; i++){
        free(jmp_arr[i].str);
    }

    return;
}

int delete_spaces(int j, char str[maxn_s], int size){ // move to first non-space symbol
    while (str[j] == ' ' && j < size){
        j++;
    }

    return j;
}

int define_type(char *str){    // command -> int
    int i = 0;
    for (i = 0; i < 9; i++){
        if (strcmp(str, com_string[i]) == 0){
            return i;
        }
    }

    return -1;
}

void add_to_arr(int type, int value){   // command -> instructions
    arr[id].type = type;
    arr[id].val = value;
    arr[id].jmp = -1;
    id++;

    return;
}

void print(){
    int i;
    printf("SUCCESS. STACK:\n");
    for (i = top - 1; i >= 0; i--){
        printf("%d\n", stack[i]);
    }
    return;
}

// BLOCK 3: BASE FUNCTIONS

int add_instruct(char *mark, int tp, int value, char *find_mark){
    mark_arr[id] = mark;

    if ((tp == ld || tp == st) && value < 0){  // address < 0
        return 1;
    }

    add_to_arr(tp, value);     // add new instruction
    if (tp == jump || tp == br){   // add find mark
        jmp_arr[cnt_jmp].str = find_mark;
        jmp_arr[cnt_jmp].id = id - 1;
        cnt_jmp++;
    }

    return 0;
}

int read(){
    while (1){
        char *str = (char*)malloc(sizeof(char) * maxn_s);
        if (str == NULL){
            return 1;
        }

        gets(str);        // get our string

        if (strcmp(str, "ret") == 0){    // return
            free(str);
            return 0;
        }

        int size = strlen(str);
        int j = delete_spaces(0, str, size);
        if (j == size || str[j] == ';' || size == 0){    // comment or empty line
            free(str);
            continue;
        }

        int i = 0;
        char *mark = (char*)malloc(sizeof(char) * maxn_s);
        if (mark == NULL){ // out of memory
            free(str);
            return 1;
        }
        char *find_mark = (char*)malloc(sizeof(char) * maxn_s);
        if (find_mark == NULL){
            free(str); free(mark);
            return 1;
        }
        char *command = (char*)malloc(sizeof(char) * maxn_s);
        if (command == NULL){
            free(str); free(mark); free(find_mark);
            return 1;
        }
        int value = 0;                          // data
        mark[0] = '\0';
        find_mark[0] = '\0';
        command[0] = '\0';

        while (j < size && isalpha(str[j])){    // read command or mark
            command[i] = str[j];
            i++; j++;
        }
        command[i] = '\0';

        if (j < size && str[j] == ':'){       // if it was mark
            i = 0;
            while (command[i] != '\0'){
                mark[i] = command[i];
                i++;
            }
            mark[i] = '\0';

            j++; i = 0;
            j = delete_spaces(j, str, size);   // read instruction
            while (j < size && isalpha(str[j])){
                command[i] = str[j];
                i++; j++;
            }
            command[i] = '\0';
        }

        int tp = define_type(command);
        if (tp == UNKNOWN){                      // if cant understand instruction
            free(str); free(mark); free(find_mark); free(command);
            return 1;
        }

        if (tp == jump || tp == br){  // catch mark for find
            j = delete_spaces(j, str, size);
            i = 0;
            while (j < size && isalpha(str[j])){
                find_mark[i] = str[j];
                i++; j++;
            }
            find_mark[i] = '\0';
            if (find_mark[0] == '\0'){
                free(str); free(mark); free(find_mark); free(command);
                return 1;
            }
        } else if (tp == ld || tp == st || tp == ldc){    // catch number
            j = delete_spaces(j, str, size);
            int is_negative = 0;
            if (str[j] == '-'){
                is_negative = 1;
                j++;
            }
            while (j < size && isdigit(str[j])){    // read data
                value = value * 10 + str[j] - '0';
                j++;
            }
            if (is_negative == 1){
                value *= -1;
            }
        }
        j = delete_spaces(j, str, size);
        if (j != size && str[j] != ';'){        // if line does not end
            free(str); free(mark); free(find_mark); free(command);
            return 1;
        }
        free(str);
        free(command);
        if (add_instruct(mark, tp, value, find_mark) == 1){  // if we cant understand the instruction
            printf("\nINSTRUCTION ERROR\n");
            free(str); free(mark); free(find_mark); free(command);
            return 1;
        }
    }

    return 1;
}

int jmp(){                   // try to jmp -> id
    int i; int j;
    for (i = 0; i < cnt_jmp; i++){
        int k = 0;
        for (j = 0; j < id; j++){
            if (strcmp(jmp_arr[i].str, mark_arr[j]) == 0){
                arr[jmp_arr[i].id].jmp = j;
                k = 1;
                break;
            }
        }
        if (k == 0){
            return 1;
        }
    }

    return 0;
}

int solve(){
    int PI = 0;
    while (PI < id){
        int tp = arr[PI].type;
        int val = arr[PI].val;

        if (tp == ld){          // ld
            push(memory[val]);
        }

        if (tp == st){          // st
            if (top == 0){
                return 1;
            }
            memory[val] = pop();
        }

        if (tp == ldc){          // ldc
            push(val);
        }

        if (tp == add){          // add
            if (top < 1){
                return 1;
            }
            int a = pop();
            int b = pop();
            push(a + b);
        }

        if (tp == sub){          // sub
            if (top < 1){
                return 1;
            }
            int a = pop();
            int b = pop();
            push(a - b);
        }

        if (tp == cmp){          // cmp
            if (top < 1){
                return 1;
            }
            int a = pop();
            int b = pop();
            if (a == b){
                push(0);
            } else if (a < b){
                push(-1);
            } else {
                push(1);
            }
        }

        if (tp == jmp){        // jmp
            PI = arr[PI].jmp;
            continue;
        }

        if (tp == br){        // br
            if (top == 0){
                return 1;
            }
            if (pop() != 0){
                PI = arr[PI].jmp;
                continue;
            }
        }

        if (tp == hlt){        // hlt
            return 0;
        }

        PI++;
    }

    return 0;
}

int main(){
    if (read() == 1){
        printf("\nREADING ERROR\n");
        free_mark();
        return 0;
    }

    if (jmp() == 1){
        printf("\nMARK ERROR\n");
        free_mark();
        return 0;
    }

    free_mark();

    if (solve() == 1){
        printf("\nSOLVE ERROR\n");
        return 0;
    }

    print();

    return 0;
}
