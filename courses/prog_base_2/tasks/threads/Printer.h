#ifndef PRINTER_H_INCLUDED
#define PRINTER_H_INCLUDED

#include "thread.h"
#include "mutex.h"

typedef struct printer_s printer_t;

typedef struct shared_s {
    char * str;
    mutex_t * mu;
} shared_t;

printer_t * printer_costructor (shared_t args);
void printer_destructor (printer_t *printer);
void printer_join (printer_t *printer);

#endif // PRINTER_H_INCLUDED
