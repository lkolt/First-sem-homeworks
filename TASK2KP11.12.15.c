void TASK2(){

    char *num1 = "01";
    char *num2 = "11";

    int i = 0;
    int dif = 0;
    while (num1[i] != '\0' && num2[i] != '\0'){ // in end of num using '\0'
        if (num1[i] - num2[i] != 0)
            dif = num1[i] - num2[i];
        i++;
    }

    if (num1[i] == '\0' && num2[i] != '\0'){
        printf("-1");
    } else if (num1[i] != '\0' && num2[i] == '\0'){
        printf("1");
    } else if (dif > 0){
        printf("1");
    } else if (dif < 0){
        printf("-1");
    } else {
        printf("0");
    }

    return;
}
