#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queue_s queue_t;

void start();
queue_t * queue_new();
//int queue_dequeue(queue_t* self);
//int queue_peek(queue_t * self);
//int queue_is_empty(queue_t * self);
//size_t queue_get_count(queue_t * self);
void queue_print();
void queue_delete();

#endif // QUEUE_H_INCLUDED
