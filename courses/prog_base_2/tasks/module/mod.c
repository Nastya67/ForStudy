#include "mod.h"
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 5

struct arr_s {
    float * arr;
    int size;
};

arr_t * arr_new(int size_arr) {
    arr_t * self = malloc(sizeof(arr_t));
    self->arr = malloc(size_arr * sizeof(float));
    self->size = size_arr;
    arr_rand(self);
    return self;
}
void arr_free(arr_t * self){
    free(self->arr);
    free(self);
}
void arr_rand(arr_t * self){
    int i;
    for(i = 0; i < self->size; i++){
        self->arr[i] = (float)(rand()%10000)/100;
    }
}
float arr_some(arr_t * self, int index){
    if(index < self->size && index >= 0){
        return self->arr[index];
    }
    else
        return 0.0;
}
void arr_change(arr_t * self, int index, double value){
    int i;
    if(index < self->size && index >= 0){
        self->arr[index] = value;
    }
}

