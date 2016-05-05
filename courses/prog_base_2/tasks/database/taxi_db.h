#ifndef TAXI_DB_H_INCLUDED
#define TAXI_DB_H_INCLUDED

#include <sqlite3.h>
#define DB_BUFFER_LENGTH 100

typedef struct taxists_s taxists_t;

taxists_t * tax_new(int id);
void tax_free(taxists_t * self);
void tax_del(sqlite3 * db);
void tax_insert(sqlite3 * db, taxists_t * tax);
void tax_update(sqlite3 * db, taxists_t * tax, int id);
int tax_count(sqlite3 * db);
void tax_print(taxists_t * tax);
taxists_t * tax_get(sqlite3 * db, unsigned int id);
void tax_fill(sqlite3_stmt * stmt, taxists_t * tax);
taxists_t * tax_select(sqlite3 * db, double K, int P);


#endif // TAXI_DB_H_INCLUDED
