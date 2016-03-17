#include <stdio.h>
#include <stdlib.h>
#include "mod.c"

int main(){
    arr_t * arr1 = arr_new(8);   //??
    printf("%.3f\n", arr_some(arr1, 1));
    arr_change(arr1, 1, 5.7);
    printf("%.3f\n", arr_some(arr1, 1));
    arr_free(arr1);
    return 0;
}
