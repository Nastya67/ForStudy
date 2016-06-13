#include "database.h"
#include <string.h>
#include <stdio.h>

void db_connection(sqlite3 * db, char * name){
    sqlite3_stmt * stmt = NULL;
    int rc = 0;
    char * sql = "CREATE DATABASE [IF NOT EXISTS] ? CHARACTER SET utf8  COLLATE utf8_general_ci;";
    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    do{
        if(rc == SQLITE_ERROR)
            break;
        rc = sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_STATIC);
        if(rc == SQLITE_ERROR)
            break;
    }while(0);
    sqlite3_finalize(stmt);
    printf("ok!0\n");
}
void db_create(sqlite3 * db){
    sqlite3_stmt * stmt = NULL;
    int rc = 0;
    char * sql = "CREATE TABLE Student1 (`name`TEXT, `surname`	TEXT, `patronymic`	TEXT, `birthday`	INTEGER, `place`	TEXT,`num`	INTEGER PRIMARY KEY AUTOINCREMENT);";
    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    rc = sqlite3_step(stmt);
        if(rc == SQLITE_ERROR)
            return NULL;

    sqlite3_finalize(stmt);
    printf("ok!1\n");
}
void db_insert(sqlite3 * db, char * name, char * surname, char * patronymic, int year, char * place){
    int rc  = 0;
    sqlite3_stmt * stmt = NULL;
    char * sql = "INSERT INTO Student (name, surname, patronymic, birthday, place) "
                 "VALUES (?, ?, ?, ?, ?);";
    do{
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_text(stmt, 1, name, strlen(name), SQLITE_STATIC);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_text(stmt, 2, surname, strlen(surname), SQLITE_STATIC);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_text(stmt, 3, patronymic, strlen(patronymic), SQLITE_STATIC);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_int(stmt, 4, year);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_bind_text(stmt, 5, place, strlen(place), SQLITE_STATIC);
    if(rc == SQLITE_ERROR)
        break;
    rc = sqlite3_step(stmt);
    if(rc == SQLITE_ERROR)
        break;

    }while(0);
    sqlite3_finalize(stmt);
}
