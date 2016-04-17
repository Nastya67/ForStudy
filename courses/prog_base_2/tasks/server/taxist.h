#ifndef TAXIST_H_INCLUDED
#define TAXIST_H_INCLUDED

typedef struct taxist_s taxist_t;

taxist_t * tax_new(char * text);
struct list * list_new();
void tax_add(struct list * tax, taxist_t * self);
void tax_parse(struct list * tax, char * text);
void tax_free(taxist_t * self);


#endif // TAXIST_H_INCLUDED
