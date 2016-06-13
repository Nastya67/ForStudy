#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <sqlite3.h>

void db_connection(sqlite3 * db, char * name);

#endif // DATABASE_H_INCLUDED
