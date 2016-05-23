#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct user_s user_t;

user_t * user_new(char * name);
char * user_name(user_t * us);
void user_free(user_t * us);

typedef struct queue_s queue_t;
typedef struct Oqueue queue_osnova;

queue_osnova * new_queue_osnova();
queue_t * queue_add(queue_osnova * osnova, int value);
int queue_delete(queue_osnova * osnova);
int queue_value(queue_osnova * osnova, int num);
int queue_size(queue_osnova * osnova);
void queue_print(queue_osnova * osnova);
queue_osnova * random(queue_osnova * q1, queue_osnova * q2);

typedef void (*cb_fn)(void * listener, queue_osnova * q);

void queue_subscribe_full (queue_osnova * osnova, void * listener, cb_fn cb);
void queue_subscribe_empty (queue_osnova * osnova, void * listener, cb_fn cb);
void queue_full(void * osnova1, queue_osnova * osnova2);
void queue_empty(void * osnova1, queue_osnova * osnova2);
void queue_overflow(void * osnova1, queue_osnova * osnova2);

#endif // QUEUE_H_INCLUDED
