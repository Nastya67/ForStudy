#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

typedef struct user_s user_t;

user_t * user_new(const char * name, const char * surname, const char * diagnoz, int age);
void user_free(user_t * self);
const char * user_getName(user_t * self);
const char * user_getSurname(user_t * self);
const char * user_getDiagnoz(user_t * self);
int user_getAge(user_t * self);

#endif // USER_H_INCLUDED
