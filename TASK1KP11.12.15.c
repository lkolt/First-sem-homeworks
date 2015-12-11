void TASK1(){

    char ch[256];
    char e;
    printf("Enter text:\n");
    scanf("%s", ch);
    printf("Enter symbol:\n");
    scanf("%c", &e);
    scanf("%c", &e);

    int i = 0;
    while (ch[i] != '\0'){
        if (ch[i] != e){
            printf("%c", ch[i]);
        }
        i++;
    }

    return;
}
