#ifndef TOURNIQUET_H_INCLUDED
#define TOURNIQUET_H_INCLUDED

typedef struct turn_s turn_t;

turn_t * turn_new();
void turn_free(turn_t * self);
int turn_expect(int size, turn_t * self[size]);
int turn_who(turn_t * self);

#endif // TOURNIQUET_H_INCLUDED
