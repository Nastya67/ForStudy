#include "term.h"
#include "tourniquet.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


struct term_s {
    int student;
    int teacher;
    int personal;
    int status;
};

term_t * term_new(int status) {
    term_t * self = malloc(sizeof(term_t));
    self->status = status;
    switch(status){
    case STUDENT:
        //self->student = malloc(sizeof(int));
        self->student = 0;
        self->teacher = -1;
        self->personal = -1;
       // printf("iiiii %i", *(self->student));
        break;
    case TEACHER:
        //self->teacher = malloc(sizeof(int));
        self->student = -1;
        self->teacher = 0;
        self->personal = -1;
        break;
    case PERSONAL:
        //self->personal = malloc(sizeof(int));
        self->student = -1;
        self->teacher = -1;
        self->personal = 0;
        break;
    case TEACHER + STUDENT:
        //self->teacher = malloc(sizeof(int));
        //self->student = malloc(sizeof(int));
        self->student = 0;
        self->teacher = 0;
        self->personal = -1;
        break;
    case TEACHER + PERSONAL:
        //self->teacher = malloc(sizeof(int));
        //self->personal = malloc(sizeof(int));
        self->student = -1;
        self->teacher = 0;
        self->personal = 0;
        break;
    case STUDENT + PERSONAL:
       // self->student = malloc(sizeof(int));
       // self->personal = malloc(sizeof(int));
        self->student = 0;
        self->teacher = -1;
        self->personal = 0;
        break;
    case STUDENT + PERSONAL + TEACHER:
       // self->student = malloc(sizeof(int));
        //self->personal = malloc(sizeof(int));
        //self->teacher = malloc(sizeof(int));
        self->teacher = 0;
        self->student = 0;
        self->personal = 0;
    break;
    }
    return self;
}
void term_free(term_t * self){
   /* switch(self->status){
    case STUDENT:
        free(self->student);
        break;
    case TEACHER:
        free(self->teacher);
        break;
    case PERSONAL:
        free(self->personal);
        break;
    case TEACHER + STUDENT:
        free(self->teacher);
        free(self->student);
        break;
    case TEACHER + PERSONAL:
        free(self->teacher);
        free(self->personal);
        break;
    case STUDENT + PERSONAL:
        free(self->student);
        free(self->personal);
        break;
    case STUDENT + PERSONAL + TEACHER:
        free(self->student);
        free(self->personal);
        free(self->teacher);
        break;
    }*/
    free(self);
}
void term_count(int size, term_t * self[size], int who){
    int i;
    for(i = 0; i < size; i++){
        switch(who){
        case STUDENT:
            if(self[i]->status == STUDENT || self[i]->status == STUDENT + TEACHER ||
               self[i]->status == STUDENT + PERSONAL || self[i]->status == STUDENT + TEACHER + PERSONAL){
                self[i]->student++;
            }
            break;
        case TEACHER:
            if(self[i]->status == TEACHER || self[i]->status == TEACHER + STUDENT ||
               self[i]->status == TEACHER + PERSONAL || self[i]->status == STUDENT + TEACHER + PERSONAL){
                self[i]->teacher++;
            }
            break;
        case PERSONAL:
            if(self[i]->status == PERSONAL || self[i]->status == PERSONAL + STUDENT ||
               self[i]->status == TEACHER + PERSONAL || self[i]->status == STUDENT + TEACHER + PERSONAL){
                self[i]->personal++;
            }
            break;
        }
    }
}
int term_status(term_t * self){
    return self->status;
}
int term_num(term_t * self, int who){
    switch(who){
        case STUDENT: return self->student;
        case TEACHER: return self->teacher;
        case PERSONAL: return self->personal;
    }
}
void term_print(int size, term_t * self[size]){
    int i;
    system("cls");
    for(i = 0; i < size; i++){
        printf("  Terminal %i:\n", i);
    switch(self[i]->status){
    case STUDENT:
        printf("Student %i\n", self[i]->student);
        break;
    case TEACHER:
        printf("Teacher %i\n", self[i]->teacher);
        break;
    case PERSONAL:
        printf("Personal %i\n", self[i]->personal);
        break;
    case TEACHER + STUDENT:
        printf("Teacher %i\n", self[i]->teacher);
        printf("Student %i\n", self[i]->student);
        break;
    case TEACHER + PERSONAL:
        printf("Teacher %i\n", self[i]->teacher);
        printf("Personal %i\n", self[i]->personal);
        break;
    case STUDENT + PERSONAL:
        printf("Student %i\n", self[i]->student);
        printf("Personal %i\n", self[i]->personal);
        break;
    case STUDENT + PERSONAL + TEACHER:
        printf("Student %i\n", self[i]->student);
        printf("Personal %i\n", self[i]->personal);
        printf("Teacher %i\n", self[i]->teacher);
        break;
    }
    printf("\n");
    }
}
