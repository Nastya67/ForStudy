#include "Load.h"
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

char * load_proc(int * lvl, char * name, int * life, float * speed, int * boomb){
    sqlite3 * db = NULL;
    int rc = 0;
    const char * dbFile = "..\\Save.db";

    rc = sqlite3_open(dbFile, &db); // open connection to DB
    if (SQLITE_OK != rc){
        printf("Can't open file `%s`\n", dbFile);
        return NULL;
    }
    printf("OK: Database connection established!\n");
    int lll  = 0;

    int id = 1;
    sqlite3_stmt * stmt;
    char * sql = (char*)"SELECT  * FROM Play WHERE Id = ?";
    do{
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 1, id);
        if(rc == SQLITE_ERROR)
            break;
        sqlite3_step(stmt);
    }while(lll);
    *lvl = sqlite3_column_int(stmt, 2);
    *life = sqlite3_column_int(stmt, 3);
    *speed = sqlite3_column_double(stmt, 4);
    *boomb = sqlite3_column_int(stmt, 5);
    name = (char*)sqlite3_column_text(stmt, 1);

    char * tmp = (char*)sqlite3_column_text(stmt, 1);

    char s[10] = "";
    strcpy(s, tmp);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_free(db);
    return tmp;
}
