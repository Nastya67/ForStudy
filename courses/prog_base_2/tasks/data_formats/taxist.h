#ifndef TAXIST_H_INCLUDED
#define TAXIST_H_INCLUDED

typedef struct taxist_s taxist_t;

taxist_t * tax_new();
char * tax_name(taxist_t * self, char * name);
char * tax_surname(taxist_t * self, char * surname);
char * tax_got_a_drivers_license_place(taxist_t * self, char * place);
char * tax_got_a_drivers_license_time(taxist_t * self, char * time);
int tax_years_old(taxist_t * self, int years);
float tax_average_speed(taxist_t * self, float speed);
void tax_free(taxist_t * self);


#endif // TAXIST_H_INCLUDED
