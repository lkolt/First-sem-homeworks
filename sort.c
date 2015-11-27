#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void sort1(int *data, int size){   //count sort   O(n)

    const int max_int = 65536;
    const int shift = max_int / 2;

    int i;
    int *cnt = malloc(max_int * sizeof(int)); //array for numbers
    if (cnt == NULL){
        printf("So small memory =(");
        return;
    }

    for (i = 0; i < size; i++){
        cnt[data[i] + shift]++;
    }

    for (i = 0; i < max_int; i++){
        while (cnt[i] != 0){
            printf("%d ", i - shift);
            cnt[i]--;
        }
    }
    printf("\n");

    free(cnt);

    return;
}

int *merge_sort(int *data, int *buffer, int left, int right){

    if (left == right - 1){
        buffer[left] = data[left];
        return buffer;
    }

    int mid = (left + right) / 2;
    int *l_buf = merge_sort(data, buffer, left, mid);
    int *r_buf = merge_sort(data, buffer, mid, right);

    int *cur;
    if (l_buf == data){
        cur = buffer;
    } else {
        cur = data;
    }

    int l = left, r = mid, i = left;
    while (l < mid && r < right){
        if (l_buf[l] < r_buf[r]){
            cur[i] = l_buf[l];
            l++;
        } else {
            cur[i] = r_buf[r];
            r++;
        }
        i++;
    }

    while (l < mid) {
        cur[i] = l_buf[l];
        l++;
        i++;
    }

    while (r < right){
        cur[i] = r_buf[r];
        r++;
        i++;
    }

    return cur;
}

void sort2(int *data, int size){                  // merge_sort     O(n * log(n))

    int *buffer = malloc(size * sizeof(int));     // buffer for merge_sort
    if (buffer == NULL){
        printf("So small memory =(");
        return;
    }

    data = merge_sort(data, buffer, 0, size);

    int i;
    for (i = 0; i < size; i++){
        printf("%d ", data[i]);
    }
    printf("\n");

    return;
}

void sort3(int *data, int size)      // O(n * n)
{
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size - 1; j++){
            if (data[j] > data[j + 1]){
                int tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }

    for (i = 0; i < size; i++){
        printf("%d ", data[i]);
    }
    printf("\n");
    return;
}


int main(){

    const double start = clock();
    int n = 20;
    printf("Size of test: %d\n", n);

    int *data;
    data = (int*)malloc(n * sizeof(int));
    if (data == NULL){
        printf("Too large size");
        return 0;
    }


    const unsigned int t_rand = (unsigned int)time(NULL) / 2;
    srand(t_rand);
    int i;
    for (i = 0; i < n; i++){
        data[i] = rand();
    }

    sort2(data, n);     //type of sort
    free(data);

    double fin = (clock() - start) / CLOCKS_PER_SEC;
    printf("time: %.5f", fin);

    return 0;
}
