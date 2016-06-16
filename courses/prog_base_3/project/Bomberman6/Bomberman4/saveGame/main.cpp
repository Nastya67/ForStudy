#include "main.h"
#include <stdio.h>
#include <string.h>

//#include <sqlite3.h>

void pl_insert(char *name, int lvl, int life, double speed, int boomb){
    sqlite3 * db = NULL;
    int rc = 0;
    const char * dbFile = "..\\Save.db";

    rc = sqlite3_open(dbFile, &db); // open connection to DB
    if (SQLITE_OK != rc){
        printf("Can't open file `%s`\n", dbFile);
        //return NULL;
    }
    printf("OK: Database connection established!\n");
    //return db;
    //int rc  = 0;
    sqlite3_stmt * stmt = NULL;
    char * sql = "UPDATE Play SET nameFileSprite = ?, cur_lvl = ?, cur_life = ?, speed = ?, num_boomb = ? "
                    "WHERE id = 1";
                 //"VALUES (?, ?, ?, ?, ?);";
    do{
        rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_STATIC);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 2, lvl);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 3, life);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_double(stmt, 4, speed);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 5, boomb);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ERROR)
            break;
        }while(0);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        sqlite3_free(db);
}


extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved){
    switch (fdwReason){
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
