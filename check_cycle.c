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
