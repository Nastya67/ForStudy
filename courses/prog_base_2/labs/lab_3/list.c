#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct list_s{
    event_t ** ev;
    int size;
};

list_t * list_new(void) {
    list_t * self = malloc(sizeof(struct list_s));
    self->size = 0;
    self->ev = malloc(0);
    return self;
}

void list_free(list_t * self) {
    free(self->ev);
    free(self);
}

void list_push_back(list_t * self, event_t * ptr) {
    self->size++;
    self->ev = realloc(self->ev, sizeof(void *) * self->size);
    self->ev[self->size - 1] = ptr;
}

event_t * list_pop_back(list_t * self) {
    self->size--;
    event_t * ret = self->ev[self->size];
    self->ev = realloc(self->ev, sizeof(void *) * self->size);
    return ret;
}

int list_getSize(list_t * self) {
    return self->size;
}

event_t * list_getEl(list_t * self, int index) {
    return self->ev[index];
}
