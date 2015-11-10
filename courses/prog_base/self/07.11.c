#include<stdio.h>
#include<stdlib.h>

int main(){
    puts("enter the size of the matrix");
    int size, i, j;
    scanf("%i", &size);
    int arr[size][size];
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            arr[i][j] = 0;
        }
    }
    somef(size, arr);
    for (i = 0; i < size; i++) {
        printf("{");
        for (j = 0; j < size; j++) {
            printf("%5i, ", arr[i][j]);
        }
        printf("}\n");
        if ( i < size - 1)
            printf("\n  ");
    }

    return 0;
}

void somef(int size, int arr[size][size]){
    int i, j, n = 1;
    for(i = 0; i < size; i++){
       for(j = 0; j < size; j++){

            if(i <= j && (i + j) < size ){
                arr[i][j] = n;
                n++;
            }
            if(i >= j && (i +j) >= (size-1)){
                arr[i][j] = n;
                n++;
            }
       }
    }
}


