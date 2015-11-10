#include<stdio.h>
#include<stdlib.h>

int sum(int size, int arr[size][size]);

int main(){
    int i, j, size, summa;
    puts("enter the size of the matrix");
    scanf("%i", &size);
    int arr[size][size];
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            arr[i][j] = rand()%10;
        }
    }

    for (i = 0; i < size; i++) {
        printf("{");
        for (j = 0; j < size; j++) {
            printf("%5i, ", arr[i][j]);
        }
        printf("}\n");
        if ( i < size - 1)
            printf("\n  ");
    }
    summa = sum(size, arr);
    printf("sum = ");
    printf("%i", summa);
    return 0;
}

int sum(int size, int arr[size][size]){
    int x = 0, i, j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if((i +j) >= (size)){
               x = x + arr[i][j];
            }
        }
    }
    return x;
}

