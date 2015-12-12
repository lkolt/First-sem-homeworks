#include <stdio.h>
#include <stdlib.h>

// TASK 1
size_t my_strlen(char *src){

    int len = 0;
    while (*src != '\0'){
        len++;
        src++;
    }

    return len;
}
// END OF TASK 1

// TASK 2
int my_strcmp(char *s1, char *s2){

    int dif = 0;
    while (*s1 != '\0' && *s2 != '\0' && dif == 0){
        dif = *s1 - *s2;
        s1++;
        s2++;
    }
    if (dif == 0){
        if (*s1 == '\0' && *s2 != '\0'){
            return -1;
        } else if (*s1 != '\0' && *s2 == '\0'){
            return 1;
        } else {
            return 0;
        }
    }

    return dif;
}
// END OF TASK 2

// TASK 3
void my_strcpy(char *dst, char *src){

    while (*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    return;
}
// END OF TASK 3

// TASK 4
void my_strctt(char *dst, char *src){

    while (*dst != '\0'){
        dst++;
    }

    while (*src != '\0'){
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';

    return;
}
// END OF TASK 4