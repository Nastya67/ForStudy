#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <windows.h>
#include <string.h>

#define MAX_SIZE 7

struct queue_s{
    int value;
    queue_t * next;
};
struct Oqueue{
    queue_t * head;
    queue_t * tail;
    int size;
};
queue_osnova * new_queue_osnova(){
    queue_osnova * self = malloc(sizeof(struct Oqueue));
    self->size = 0;
    self->head = malloc(sizeof(queue_t));
    self->tail = malloc(sizeof(queue_t));
    self->head = NULL;
    self->tail = NULL;
    queue_t * arr;
    int i;
    for(i = 0; i < 8; i++){
        arr = queue_new(self, rand()%20);
        //queue_print();
    }
    return self;
}

queue_t * queue_new(queue_osnova * osnova, int value){
    queue_t * self = malloc(sizeof(queue_t));
    self->next = malloc(sizeof(queue_t));
    self->next = NULL;
    self->value = 0;
    if(value > 0)
        self->value = value;

    if(osnova->size == 0){
        osnova->head = self;
    }
    else if(osnova->size > 0 && osnova->size < MAX_SIZE){
        osnova->tail->next = self;
    }
    else if(osnova->size >= MAX_SIZE){
        queue_delete(osnova);
        osnova->tail->next = self;
    }
    osnova->tail = self;
    osnova->size++;
    return self;
}
void queue_delete(queue_osnova * osnova){
    queue_t * curr = osnova->head;
    osnova->head = osnova->head->next;
    free(curr);
    osnova->size--;
}
int queue_value(queue_osnova * osnova, int num){
    queue_t * curr = osnova->head;
    int i;
    for(i = 0; i < num-1; i++){
        curr = curr->next;
    }
    return curr->value;
}
void queue_print(queue_osnova * osnova){
   // system("cls");
    queue_t * curr = osnova->head;
    int i;
    for(i = 0; i < osnova->size; i++){
        printf("day %i: %i\n", i+1, curr->value);
        curr = curr->next;
    }
    //printf("-------\nsize: %i\n-------\n", queue.size);
}

