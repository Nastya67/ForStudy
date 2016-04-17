#ifndef TAXIST_H_INCLUDED
#define TAXIST_H_INCLUDED

typedef struct taxist_s taxist_t;

taxist_t * tax_new(char * text);
struct list * list_new();
void tax_add(struct list * tax, taxist_t * self);
void tax_parse(struct list * tax, char * text);
void tax_del(struct list * tax, int N);
void return_str_tax(struct list * tax, int N, char * buf);
int list_size(struct list * tax);
taxist_t * get_one_tax(struct list * tax, int N);
void tax_repl_name(struct list * tax, int N, char * name);
void tax_repl_surname(struct list * tax, int N, char * surname);
void tax_repl_age(struct list * tax, int N, int age);
void tax_repl_speed(struct list * tax, int N, double speed);
void tax_repl_place(struct list * tax, int N, char * place);
void tax_repl_time(struct list * tax, int N, char * date);


#endif // TAXIST_H_INCLUDED
