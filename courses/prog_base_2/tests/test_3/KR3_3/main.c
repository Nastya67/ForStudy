#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "database.h"

int main(int argc, char * argv[]){
    /*if(argc == 1){
        printf("Data received\n");
        return 1;
    }
    else if(argc > 2){
        printf("Too much data\n");
        return 1;
    }*/
    char arg[] = "DB.db";
    sqlite3 * db = NULL;
    int rc = 0;

    //rc = sqlite3_open(argv[1], &db); // open connection to DB
    rc = sqlite3_open(arg, &db); //
    if (SQLITE_OK != rc){
        //printf("Can't open file `%s`\n", argv[1]);
        printf("Can't open file `%s`\n", arg);
        return 1;
    }
    printf("OK: Database connection established!\n");
    //db_connection(db, argv[1]);
    //db_create(db);
    db_insert(db, "a", "b", "c", 1, "e");
    return 0;
}
