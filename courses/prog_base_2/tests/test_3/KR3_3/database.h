#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <sqlite3.h>

void db_connection(sqlite3 * db, char * name);
void db_create(sqlite3 * db);
void db_insert(sqlite3 * db, char * name, char * surname, char * patronymic, int year, char * place);

#endif // DATABASE_H_INCLUDED
