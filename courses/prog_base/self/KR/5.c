#include <stdio.h>
#include <stdlib.h>

int main(){
    const int N = 8;
    int arr[N];
    int i;
    for (i = 0; i<N; i++){
        arr[i] = rand()%6000-3000;
        if(arr[i] > 0){
            printf("%i, ", &arr[i]);
        }
    }
    return 0;
}
