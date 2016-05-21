#include <stdio.h>
#include <stdlib.h>
#include "list/list.h"
#include "User.h"
#include "clinic.h"


int main(){
    clinic_t * clinic = clinic_new();

    room_t * rooms = clinic_getRoom(clinic, 1);
    clinic_addUserToRoom(clinic, 1, user_new("Nastya", "Hrad", "net", 17));
    printf("%i", room_getSize(rooms));

    clinic_free(clinic);
    return 0;
}
