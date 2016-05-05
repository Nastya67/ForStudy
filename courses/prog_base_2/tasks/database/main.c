#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taxi_db.h"
#include <sqlite3.h>

int main(){
    sqlite3 * db = NULL;
    int rc = 0;
    const char * dbFile = "Taxi.db";

    rc = sqlite3_open(dbFile, &db); // open connection to DB
    if (SQLITE_OK != rc){
        printf("Can't open file `%s`\n", dbFile);
        return 1;
    }
    printf("OK: Database connection established!\n");
    //get count
    printf("count %i", tax_count(db));
    //delete 8`th element
    tax_del(db);
    //insert
    taxists_t * tax = tax_new(8);
    printf("\nTo insert:\n");
    tax_print(tax);
    printf("Insert...\n");
    tax_insert(db, tax);
    tax_get(db, 8);
    //update
    printf("Update...\n");
    taxists_t * tax2 = tax_new(13);
    tax_update(db, tax2, 8);
    tax_get(db, 8);
    //select
    double K = 90.9;
    int P = 4;
    printf("SELECT  * FROM Taxi WHERE Tariff < %.2f AND Experience > %i;\n", K, P);
    taxists_t * tax3 = tax_select(db, K, P);
    // close connection to DB
    sqlite3_close(db);
    tax_free(tax);
    tax_free(tax2);
    tax_free(tax3);
    return 0;
}
