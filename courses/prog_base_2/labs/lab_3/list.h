#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct event_s{
    void * receiver;
    void * callback;
} event_t;

typedef struct list_s list_t;
list_t * list_new(void);
void list_free(list_t * self);
void list_push_back(list_t * self, event_t * ptr);
event_t * list_pop_back(list_t * self);
int list_getSize(list_t * self);
event_t * list_getEl(list_t * self, int index);

#endif // LIST_H_INCLUDED
