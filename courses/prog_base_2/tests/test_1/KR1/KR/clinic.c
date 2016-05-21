#include "clinic.h"
#include "User.h"

#define NUM_ROOM 5
#define MAX_FLAT 6

struct clinic_s{
    room_t * room [NUM_ROOM];
    list_t * subscribers;
};

struct room_s{
    list_t * flat;
    int max_size;
};

clinic_t * clinic_new(){
    clinic_t * self = malloc(sizeof(clinic_t));
    int i;
    for(i = 0; i < NUM_ROOM; i++)
        self->room[i] = room_new(rand()%4 +2);
    self->subscribers = list_new();
    return self;
}
void clinic_free(clinic_t * self){
    int i;
    for(i = 0; i < NUM_ROOM; i++)
        room_free(self->room[i]);
    list_free(self->subscribers);
    free(self);
}
room_t * room_new(int size){
    room_t * self = malloc(sizeof(room_t));
    self->max_size = size;
    self->flat = list_new();
}
void room_free(room_t * self){
    list_free(self->flat);
    free(self);
}

void clinic_addUserToRoom(clinic_t * self, int room, user_t * user){
    list_push_back(self->room[room]->flat, user);
}
user_t * clinic_getUser(clinic_t * self, int room, int user){
    return list_get(self->room[room]->flat, user);
}
room_t * clinic_getListRoom(clinic_t * self){
    room_t copy[NUM_ROOM];
    int i;
    for(i = 0; i < NUM_ROOM; i++){
        copy[i] = *(self->room[i]);
    }
    return &copy;
}
room_t * clinic_getRoom(clinic_t * self, int room){
    if(room < NUM_ROOM && room > 0){
        return self->room[room];
    }
}
int room_getSize(room_t * self){
    return list_getSize(self->flat);
}
list_t * room_listFlat(room_t * self){
    list_t * copy = list_new_copy(self->flat);
    return copy;
}




