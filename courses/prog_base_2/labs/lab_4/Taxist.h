#ifndef TAXIST_H_INCLUDED
#define TAXIST_H_INCLUDED

typedef struct taxist_s taxist_t;

taxist_t * tax_new();
struct list * list_new();
int list_size(struct list * tax);
void tax_add(struct list * tax, taxist_t * self);
void tax_del(struct list * tax, int N);
taxist_t * get_one_tax(struct list * tax, int N);
void tax_init(taxist_t * tax, char * name, char * surname, int exp, double tar, char * date);
void tax_repl_name(taxist_t * tax, char * name);
void tax_repl_surname(taxist_t * tax, char * surname);
void tax_repl_exp(taxist_t * tax, int exp);
void tax_repl_tariff(taxist_t * tax, double tar);
void tax_repl_date(taxist_t * tax, char * date);
void tax_to_xml(taxist_t * tax, char * buf);
void list_to_xml(struct list * tax, char * buf);
void tax_parse(struct list * list, int buf_size, char text[buf_size]);
void tax_free(taxist_t * self);


#endif // TAXIST_H_INCLUDED
