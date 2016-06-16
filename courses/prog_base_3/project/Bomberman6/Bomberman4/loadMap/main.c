#include "loadMap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int map_count(sqlite3 * db){
    int lll;
    sqlite3_stmt * stmt = NULL;
    const char * sql = "SELECT COUNT(*) FROM Maps;";
    lll = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(lll == SQLITE_ERROR)
        return 0;
    lll = sqlite3_step(stmt);
    if(lll == SQLITE_ERROR)
        return 0;
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}
char * map_getlvl_db(sqlite3 * db, unsigned int id){
    int lll  = 0;
    int rc = 0;
    int count = 0;
    char * str;
    sqlite3_stmt * stmt;
    char * sql = "SELECT  * FROM Maps WHERE key = ?";
    char * sql_count = "SELECT COUNT(*) FROM Maps WHERE key = ?;";
    rc = sqlite3_prepare_v2(db, sql_count, strlen(sql_count), &stmt, NULL);
    do{
        rc = sqlite3_bind_double(stmt, 1, id);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ERROR)
            break;
        count = sqlite3_column_int(stmt, 0);
        if(count == 0){
            printf("not found\n");
            return NULL;
        }
        sqlite3_finalize(stmt);
    }while(0);
    do{
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 1, id);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_step(stmt);
        str = sqlite3_column_text(stmt, 1);
    }while(lll);

    sqlite3_finalize(stmt);
    return str;
}
char * map_getlvl(int num){
    sqlite3 * db = NULL;
    int rc = 0;
    const char * dbFile = "..\\Save.db";

    rc = sqlite3_open(dbFile, &db); // open connection to DB
    if (SQLITE_OK != rc){
        printf("Can't open file `%s`\n", dbFile);
        return 1;
    }
    printf("OK: Database connection established!\n");
    char * buf = map_getlvl_db(db, num);
    printf("%s", buf);
    sqlite3_close(db);
    sqlite3_free(db);
    return buf;
}
