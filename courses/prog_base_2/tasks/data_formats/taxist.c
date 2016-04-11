#include "taxist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct taxist_s{
    char name[10];
    char surname[15];
    int years_old;
    double average_speed;
    char got_a_drivers_license_place[20];
    char got_a_drivers_license_time[12];
};

taxist_t * tax_new(){
    taxist_t * self = malloc(sizeof(taxist_t));
    return self;
}
char * tax_name(taxist_t * self, char * name){
    if(NULL != name)
        strcpy(self->name, name);
    return self->name;
}
char * tax_surname(taxist_t * self, char * surname){
    if(NULL != surname)
        strcpy(self->surname, surname);
    return self->surname;
}
char * tax_got_a_drivers_license_place(taxist_t * self, char * place){
    if(NULL != place)
        strcpy(self->got_a_drivers_license_place, place);
    return self->got_a_drivers_license_place;
}
char * tax_got_a_drivers_license_time(taxist_t * self, char * time){
    if(NULL != time)
        strcpy(self->got_a_drivers_license_time, time);
    return self->got_a_drivers_license_time;
}
int tax_years_old(taxist_t * self, int years){
    if(years != 0)
        return self->years_old = years;
    return self->years_old;
}
float tax_average_speed(taxist_t * self, float speed){
    if(0 != speed)
        return self->average_speed = speed;
    return self->average_speed;
}
void tax_print(taxist_t * self[3]){
    int i;
    for(i = 0; i < 3; i++){
        printf("Taxist %i\n", i+1);
        printf("\t%15s: %s\n", "name", self[i]->name);
        printf("\t%15s: %s\n", "surname", self[i]->surname);
        printf("\t%15s: %i\n", "years old", self[i]->years_old);
        printf("\t%15s: %f\n", "average speed", self[i]->average_speed);
        printf("\t%15s %s (%s)\n", "got a drivers license in", self[i]->got_a_drivers_license_place, self[i]->got_a_drivers_license_time);
    }
}
void tax_free(taxist_t * self){
    free(self);
}
