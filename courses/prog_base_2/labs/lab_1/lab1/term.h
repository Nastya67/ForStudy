#ifndef TERM_H_INCLUDED
#define TERM_H_INCLUDED

#define STUDENT 3
#define TEACHER 5
#define PERSONAL 7

typedef struct term_s term_t;

term_t * term_new(int status);
void term_free(term_t * self);
void term_count(int size, term_t * self[size], int who);
void term_print(int size, term_t * self[size]);
int term_status(term_t * self);

#endif // TERM_H_INCLUDED
