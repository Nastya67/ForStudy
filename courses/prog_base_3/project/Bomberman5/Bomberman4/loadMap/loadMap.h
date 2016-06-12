#ifndef LOADMAP_H_INCLUDED
#define LOADMAP_H_INCLUDED

#include <sqlite3.h>


char * map_getlvl(int num);
char * map_getlvl_db(sqlite3 * db, unsigned int id);
int map_count(sqlite3 * db);

#endif // LOADMAP_H_INCLUDED
