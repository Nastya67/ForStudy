#include "list.h"
#include <string.h>

struct nod_s{
    void * value;
    nod_t * next;
};
struct list_s{
    nod_t * head;
    nod_t * tail;
    int size;
};

list_t * list_new(){
    list_t * self = malloc(sizeof(list_t));
    self->head = malloc(sizeof(nod_t));
    self->tail = malloc(sizeof(nod_t));
    self->size = 0;
    return self;
}
nod_t * nod_new(void * value){
    nod_t * self = malloc(sizeof(nod_t));
    self->value = malloc(sizeof(char)*strlen(value));
    strcpy(self->value, value);
    self->next = malloc(sizeof(nod_t));
    return self;
}
void list_addLast(list_t * list, nod_t * nod){
    if(list->size == 0){
        list->head = nod;
        list->tail = nod;
    }
    else {
        list->tail->next = nod;
        list->tail = nod;
    }
    list->size++;
}
int list_getSize(list_t * list){
    return list->size;
}
void * getNode(list_t * list, int pos){
    nod_t * curr = list->head;
    int i;
    for(i = 0; i < pos; i++){
        curr = curr->next;
    }
    return curr->value;
}
void list_free(list_t * list){
    nod_t * cur = list->head;
    nod_t * del;
    int i;
    for(i = 0; i < list->size-1; i++){
        del = cur;
        cur = cur->next;
        free(del);
    }
    free(cur);
    free(list);
}


