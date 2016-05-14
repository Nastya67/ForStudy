#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#define MAX_SIZE 7

typedef struct queue_s queue_t;
typedef struct Oqueue queue_osnova;

queue_osnova * new_queue_osnova();
queue_t * queue_new(queue_osnova * osnova, int value);
void queue_print(queue_osnova * osnova);
int queue_value(queue_osnova * osnova, int num);
void queue_delete(queue_osnova * osnova);

#endif // QUEUE_H_INCLUDED
