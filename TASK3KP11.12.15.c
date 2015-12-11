void TASK3(){

    FILE *fi = fopen("input.txt", "r");
    if (fi == NULL){
        printf("FILE NOT FOUND");
        return;
    }

    char ch = fgetc(fi);
    if (ch == EOF){
        fclose(fi);
        return;
    }
    char last = ch;
    int f = 0;
    while (ch = fgetc(fi)){

        if (ch == EOF){
            fclose(fi);
            return;
        }
        if (f != 0){
            printf("%c", ch);
        }

        if (ch == '/' && last == '/'){
            f = 1;
        }

        if (ch == '\n'){
            f = 0;
        }

        last = ch;
    }

    fclose(fi);
    return;
}
