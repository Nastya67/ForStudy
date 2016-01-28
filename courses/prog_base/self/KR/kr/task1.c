#include <stdio.h>
#include <stdlib.h>
//25 variant;
int main()
{
    int N, i, j, min;
    printf("size = ");
    scanf("%i", &N);
    int arr1[N], arr2[N], sum[N];
    for(i = 0; i < N; i++){
        arr1[i] = rand()%100 - 50;
        arr2[i] = rand()%100 - 50;
        sum[i] = arr1[i] + arr2[i];
        if(sum[i] > 0){
            printf("%4i ", sum[i]);
        }
    }
    min = 100;
    for(i = 0; i < N; i++){
        if(sum[i] > 0 && min > sum[i]){
            min = sum[i];
        }
    }
    printf("\n%i", min);
    return 0;
}
