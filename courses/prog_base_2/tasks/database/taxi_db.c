#include "taxi_db.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct taxists_s{
    unsigned int id;
    char name[15];
    char surname[15];
    int experience;
    double tariff;
    char got_license[50];
};

taxists_t * tax_new(int id){
    taxists_t * self = malloc(sizeof(taxists_t));
    strcpy(self->name, "Nastya");
    strcpy(self->surname, "Hrad");
    self->tariff = (double)(rand()%1000)/100;
    self->id = id;
    struct tm * mtime = malloc(sizeof(struct tm));
    mtime->tm_mday = rand()%20;
    mtime->tm_mon = rand()%11;
    mtime->tm_year = rand()%120;
    mtime->tm_hour = rand()%20;
    mtime->tm_min = rand()%50;
    mtime->tm_sec = rand()%59;
    char text [50];
    strcpy(text, asctime(mtime));
    strcpy(self->got_license, text);
    self->experience = 2016-1900-mtime->tm_year;
    free(mtime);
    //free(text);
    return self;
}
void tax_free(taxists_t * self){
    free(self);
}
void tax_del(sqlite3 * db){
    sqlite3_stmt * stmt = NULL;
    const char * sqlDeleteTest = "DELETE FROM Taxi WHERE id = 333;";
    int lll;
    lll = sqlite3_prepare_v2(db, sqlDeleteTest, strlen(sqlDeleteTest) + 1, &stmt, NULL);
    if(SQLITE_OK != lll){
        printf("Not prepared!\n");
    }
    lll = sqlite3_step(stmt);
    if (SQLITE_DONE != lll){
        printf("Not deleted! %i\n", lll);
    }
    sqlite3_finalize(stmt);
}
void tax_insert(sqlite3 * db, taxists_t * tax){
    int rc  = 0;
    sqlite3_stmt * stmt;
    char * sql = "INSERT INTO Taxi (id, name, surname, experience, tariff, got_license) "
                 "VALUES (?, ?, ?, ?, ?, ?);";
    do{
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_int(stmt, 1, tax->id);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_text(stmt, 2, tax->name, strlen(tax->name), SQLITE_STATIC);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_text(stmt, 3, tax->surname, strlen(tax->surname), SQLITE_STATIC);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_int(stmt, 4, tax->experience);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_double(stmt, 5, tax->tariff);
    if(rc == SQLITE_ERROR)
        break;
    if(NULL != tax->got_license)
        rc = sqlite3_bind_text(stmt, 6, tax->got_license, strlen(tax->got_license), SQLITE_STATIC);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_step(stmt);
    if(rc == SQLITE_ERROR)
        break;

    }while(0);
    sqlite3_finalize(stmt);
}
int tax_count(sqlite3 * db){
    int lll;
    sqlite3_stmt * stmt = NULL;
    const char * sql = "SELECT COUNT(*) FROM Taxi;";
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
void tax_print(taxists_t * tax){
    puts("\nTaxist");
    printf("\t %-18s: %-10i\n", "Id", tax->id);
    printf("\t %-18s: %-10s\n", "Name", tax->name);
    printf("\t %-18s: %-10s\n", "Surname", tax->surname);
    printf("\t %-18s: %-10i\n", "Experience", tax->experience);
    printf("\t %-18s: %-8.2f\n", "Tariff", tax->tariff);
    printf("\t %-18s: %-10s\n", "Got a license", tax->got_license);
}
taxists_t * tax_get(sqlite3 * db, unsigned int id){
    int lll  = 0;
    int rc = 0;
    taxists_t * tax = NULL;
    sqlite3_stmt * stmt;
    char * sql = "SELECT  * FROM Taxi WHERE Id = ?";
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
        tax = malloc(sizeof(taxists_t));
        tax->id = id;
        tax_fill(stmt, tax);
    }while(lll);
    printf("Get tax the id(%i):\n", id);
    tax_print(tax);
    sqlite3_finalize(stmt);
    return tax;
}
taxists_t * tax_select(sqlite3 * db, double K, int P){
    int rc = 0;
    int count = 0;
    sqlite3_stmt * stmt = NULL;
    char * sql = "SELECT  * FROM Taxi WHERE Tariff < ? AND Experience > ?;";
    char * sql_count = "SELECT COUNT(*) FROM Taxi WHERE tariff < ? AND experience > ?;";
    rc = sqlite3_prepare_v2(db, sql_count, strlen(sql_count), &stmt, NULL);
    do{
        rc = sqlite3_bind_double(stmt, 1, K);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 2, P);
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
    taxists_t * tax = malloc(sizeof(taxists_t)*count);
    do{
        rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_double(stmt, 1, K);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 2, P);
        if(rc == SQLITE_ERROR)
            break;
    }while(0);
    int i;
    for(i = 0; i < count; i++){
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ERROR)
            break;
        tax_fill(stmt, &tax[i]);
        tax_print(&tax[i]);
    }
    sqlite3_finalize(stmt);
    return tax;
}
void tax_fill(sqlite3_stmt * stmt, taxists_t * tax){
    tax->id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    tax->experience = sqlite3_column_int(stmt, 3);
    tax->tariff = sqlite3_column_double(stmt, 4);
    const char * date = sqlite3_column_text(stmt, 5);
    if(NULL != name)
        strcpy(tax->name, (char *)name);
    if(NULL != surname)
        strcpy(tax->surname, (char *)surname);
    memset(tax->got_license, 0, 40);
    if(NULL != date)
        strcpy(tax->got_license, date);
}
void tax_update(sqlite3 * db, taxists_t * tax, int id){
    int rc  = 0;
    sqlite3_stmt * stmt;
    char * sql = "UPDATE  Taxi "
                "SET Name = ?, Surname = ?, Experience = ?, tariff = ?, Got_license = ? "
                 "WHERE Id = 8;";
    do{
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 6, id);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_text(stmt, 1, tax->name, strlen(tax->name), SQLITE_STATIC);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_text(stmt, 2, tax->surname, strlen(tax->surname), SQLITE_STATIC);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_int(stmt, 3, tax->experience);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_double(stmt, 4, tax->tariff);
        if(rc == SQLITE_ERROR)
            break;
        if(NULL != tax->got_license)
            rc = sqlite3_bind_text(stmt, 5, tax->got_license, strlen(tax->got_license), SQLITE_STATIC);
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ERROR)
            break;
    }while(0);
    sqlite3_finalize(stmt);
    return;
}
