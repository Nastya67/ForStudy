
#ifndef MOD_H_INCLUDED
#define MOD_H_INCLUDED

typedef struct arr_s arr_t;

arr_t * arr12(int size_arr);      // constructor
void arr_free(arr_t * self);    // destructor
void arr_rand(arr_t * self);
float arr_some(arr_t * self, int index);
void arr_change(arr_t * self, int index, double value);

#endif // MOD_H_INCLUDED
