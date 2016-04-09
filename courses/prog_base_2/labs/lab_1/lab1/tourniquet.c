#include <stdio.h>
#include <stdlib.h>
#include "tourniquet.h"

struct turn_s {
    int who;
    //int vkl;
};
turn_t * turn_new(){
    turn_t * self = malloc(sizeof(turn_t));
    self->who = 0;
    //self->vkl = 0;
    return self;
}
void turn_free(turn_t * self){
    free(self);
}
int turn_expect(int size, turn_t * self[size]){
    int random = rand()%size;
    scanf("%i", &self[random]->who);

    return random;
}
int turn_who(turn_t * self){
    return self->who;
}
void turn_repl_zero(turn_t * self){
    self->who = 0;
}
