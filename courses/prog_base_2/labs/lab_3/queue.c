#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include <windows.h>
#include <string.h>
#include "list.h"

#define MAX_SIZE 10

struct user_s{
    char * name;
};

user_t * user_new(char * name){
    user_t * self = malloc(sizeof(user_t));
    self->name = name;
    return self;
}
char * user_name(user_t * us){
    return us->name;
}
void user_free(user_t * us){
    free(us->name);
    free(us);
}


struct queue_s{
    int value;
    queue_t * next;
};
struct Oqueue{
    queue_t * head;
    queue_t * tail;
    int size;
    void * full_sb;
    void * empty_sb;
    cb_fn full_cb;
    cb_fn empty_cb;
    list_t * multi;
};
queue_osnova * new_queue_osnova(){
    queue_osnova * self = malloc(sizeof(struct Oqueue));
    self->size = 0;
    self->head = malloc(sizeof(queue_t));
    self->tail = malloc(sizeof(queue_t));
    self->head = NULL;
    self->tail = NULL;
    self->multi = list_new();
    return self;
}
queue_t * queue_add(queue_osnova * osnova, int value){
    queue_t * self = malloc(sizeof(queue_t));
    self->next = malloc(sizeof(queue_t));
    self->next = NULL;
    self->value = value;

    if(osnova->size == 0){
        osnova->head = self;
    }
    else if(osnova->size > 0 && osnova->size < MAX_SIZE){
        osnova->tail->next = self;
    }
    else if(osnova->size >= MAX_SIZE){
        osnova->full_cb(osnova->full_sb, osnova);
        osnova->tail->next = self;
    }
    osnova->tail = self;
    osnova->size++;
    return self;
}
int queue_delete(queue_osnova * osnova){
    queue_t * curr = osnova->head;
    osnova->head = osnova->head->next;
    int value = curr->value;
    free(curr);
    osnova->size--;
    if(osnova->size == 0)
        osnova->empty_cb(osnova->empty_sb, osnova);
    return value;
}
int queue_value(queue_osnova * osnova, int num){
    queue_t * curr = osnova->head;
    int i;
    for(i = 0; i < num-1; i++){
        curr = curr->next;
    }
    return curr->value;
}
int queue_size(queue_osnova * osnova){
    return osnova->size;
}
void queue_print(queue_osnova * osnova){
   // system("cls");
    queue_t * curr = osnova->head;
    int i;
    for(i = 0; i < osnova->size; i++){
        printf("%i\n", curr->value);
        curr = curr->next;
    }
    //printf("-------\nsize: %i\n-------\n", queue.size);
}
void queue_subscribe_full (queue_osnova * osnova, void * listener, cb_fn cb){
    osnova->full_sb = listener;
    osnova->full_cb = cb;
}
void queue_subscribe_empty (queue_osnova * osnova, void * listener, cb_fn cb){
    osnova->empty_sb = listener;
    osnova->empty_cb = cb;
}
queue_osnova * random(queue_osnova * q1, queue_osnova * q2){
    switch(rand()%2){
        case 0: return q1;
        case 1: return q2;
        default : return NULL;
    }
}
void queue_full(void * osnova1, queue_osnova * osnova2){
    if(queue_size((queue_osnova*)osnova1) < 9)
        queue_add((queue_osnova*)osnova1, queue_delete(osnova2));
    else{
        int i;
        printf("Overflow\nDeleting...\n");
        Sleep(1000);
        for(i = 0; i < list_getSize(osnova2->multi); i++){
            event_t * ev = list_getEl(osnova2->multi, i);
            cb_fn fanc = ev->callback;
            fanc(ev->receiver, osnova2);
        }
    }
}
void queue_empty(void * osnova1, queue_osnova * osnova2){
    if(queue_size((queue_osnova*)osnova1) >= 2)
        queue_add(osnova2, queue_delete((queue_osnova*)osnova1));
    else{
        queue_empty_spesial((queue_osnova*)osnova1, osnova2);
    }
}
void queue_empty_spesial(queue_osnova * osnova1, queue_osnova * osnova2){
    printf("Total empty\nFilling...\n");
    Sleep(1000);
    system("cls");
    int i;
    for(i = 0; i < 3; i++){
        queue_add(osnova2, rand()%50);
        queue_add(osnova1, rand()%50);
    }
}
void queue_subscribe_multi(queue_osnova * osnova, void * listener, cb_fn cb){
    event_t * ev = (event_t*)malloc (sizeof(event_t));
    ev->receiver = listener;
    ev->callback = cb;
    list_push_back(osnova->multi, ev);
}
void queue_overflow(void * osnova1, queue_osnova * osnova2){
    int i;
    for(i = 0; i < 3; i++){
        queue_delete(osnova2);
        queue_delete((queue_osnova*)osnova2->full_sb);
    }
    printf("User %s received a message overflow\n", user_name((user_t*)osnova1));
    Sleep(1000);
}
