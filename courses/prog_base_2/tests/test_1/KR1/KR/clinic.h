#ifndef CLINIC_H_INCLUDED
#define CLINIC_H_INCLUDED
#include "list/list.h"

typedef struct clinic_s clinic_t;
typedef struct room_s room_t;

clinic_t * clinic_new();
void clinic_free(clinic_t * self);

room_t * room_new(int size);
void room_free(room_t * self);




#endif // CLINIC_H_INCLUDED
