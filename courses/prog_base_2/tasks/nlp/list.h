#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct nod_s nod_t;
typedef struct list_s list_t;

list_t * list_new();
nod_t * nod_new(void * value);
void list_addLast(list_t * list, nod_t * nod);

void list_free(list_t * list);
void nod_free(nod_t * nod);

#endif // LIST_H_INCLUDED
