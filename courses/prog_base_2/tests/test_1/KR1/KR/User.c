#include "User.h"
#include "clinic.h"

typedef struct user_s {
    const char * name;
    const char * surname;
    const char * diagnoz;
    int age;
} ;

user_t * user_new(const char * name, const char * surname, const char * diagnoz, int age) {
    user_t * self = malloc(sizeof(user_t));
    self->name = name;
    self->surname = surname;
    self->diagnoz = diagnoz;
    self->age = age;
    return self;
}

void user_free(user_t * self) {
    free(self->diagnoz);
    free(self->name);
    free(self->surname);
    free(self);
}

const char * user_getName(user_t * self) {
    return self->name;
}
const char * user_getSurname(user_t * self) {
    return self->surname;
}
const char * user_getDiagnoz(user_t * self) {
    return self->diagnoz;
}
int user_getAge(user_t * self){
    return self->age;
}
