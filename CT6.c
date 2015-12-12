#include <stdio.h>
#include <stdlib.h>

// TASK 6

void TASK6(){

    int n, i;
    char ch[256];
    for (i = 0; i < 256; i++){
        ch[i] = '\0';
    }

    scanf("%d", &n);
    for (i = 0; i < n; i++){
        char s[256];
        scanf("%s", s);
        int j = 0;
        while (s[j] != '\0'){
            ch[j] ^= s[j];
            j++;
        }
    }
    printf("%s\n", ch);

    return;
}

// END OF TASK 6
