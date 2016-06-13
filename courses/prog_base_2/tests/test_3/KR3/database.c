#include "database.h"
#include <string.h>

void db_connection(sqlite3 * db, char * name){
    sqlite3_stmt * stmt = NULL;
    int rc = 0;
    char * sql = "CREATE DATABASE [IF NOT EXISTS] ? CHARACTER SET utf8  COLLATE utf8_general_ci;";
    rc = sqlite3_prepare_v2(db, sql_count, strlen(sql_count), &stmt, NULL);
    do{
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_STATIC);
        if(rc == SQLITE_ERROR)
            break;
    }while(0);
    sqlite3_finalize(stmt);

}

