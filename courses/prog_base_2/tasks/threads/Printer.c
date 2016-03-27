#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include "printer.h"
#define ITERATION 10

struct printer_s{
    thread_t *thread;
};

static void * printer_print(void * argss){
    shared_t *args = (shared_t *)argss;
    int i;
    while (1) {
        mutex_lock(args->mu);
        for(i = 0; i < ITERATION; i++){
            printf("%s\n", args->str);
        }
        mutex_unlock(args->mu);
    }
    return NULL;
}

printer_t * printer_constructor(shared_t * data){
    printer_t * self = malloc(sizeof(printer_t));
    self->thread = thread_create_args(printer_print, data);
    return self;
}
void printer_destructor (printer_t * self) {
    thread_free(self->thread);
    free (self);
}
void printer_join (printer_t *printer){
    thread_join(printer->thread);
}

