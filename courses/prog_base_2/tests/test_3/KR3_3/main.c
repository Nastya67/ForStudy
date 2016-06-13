#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "database.h"

int main(int argc, char * argv[]){
    if(argc == 1){
        printf("Data received\n");
        return 1;
    }
    else if(argc > 2){
        printf("Too much data\n");
        return 1;
    }
    sqlite3 * db = NULL;
    int rc = 0;
    //const char * dbFile = "Taxi.db";

    rc = sqlite3_open(argv[1], &db); // open connection to DB
    if (SQLITE_OK != rc){
        printf("Can't open file `%s`\n", argv[1]);
        return 1;
    }
    printf("OK: Database connection established!\n");
    db_connection(db);

    return 0;
}
