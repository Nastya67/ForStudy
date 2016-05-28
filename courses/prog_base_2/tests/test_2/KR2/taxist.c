#include "taxist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sqlite3.h>


struct taxist_s {
    int id;
    char name[20];
    char surname[20];
    int experience;
    double tariff;
    char got_license[30];
    taxist_t * next;
};

struct list{
    taxist_t * head;
    taxist_t * tail;
    int size;
};

taxist_t * tax_new(){
    taxist_t * self = malloc(sizeof(taxist_t));
    return self;
}
struct list * list_new(){
    struct list * tax = malloc(sizeof(struct list));
    tax->size = 0;
    if(NULL == tax)
        printf("ERROR");
    return tax;
}

void tax_add(struct list * tax, taxist_t * self){
    if(tax->size > 0){
        tax->tail->next = self;
    }
    tax->tail = self;
    if(tax->size == 0){
        tax->head = self;
    }
    tax->size++;
}
void tax_del(struct list * tax, int N){
    taxist_t * curr = tax->head;
    int i;
    for(i = 0; i < N-1; i++){
        curr = curr->next;
    }
    taxist_t * tmp = curr->next;
    curr->next = tmp->next;
    free(tmp);
    tax->size--;
}

void return_str_tax(struct list * tax, char * buf){
    taxist_t * curr = tax->head;
    //int i;
   // for(i = 0; i < N; i++){
        //curr = curr->next;
   // }
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * curNode = NULL;
	xmlNode * taxNode = NULL;
	//xmlNode * groupNode = NULL;
	char strBuf[1000];

	doc = xmlNewDoc("1.0");

	rootNode = xmlNewNode(NULL, "Taxists");
	xmlDocSetRootElement(doc, rootNode);
	int i;
	for(i = 0; i < list_size(tax); i++){
        curNode = xmlNewChild(rootNode, NULL, "Taxist", NULL);

        xmlNewChild(curNode, NULL, "name", curr->name);
        xmlNewChild(curNode, NULL, "surname", curr->surname);
        char exp[10] = "";
        sprintf(exp, "%i", curr->experience);
        xmlNewChild(curNode, NULL, "experience", exp);
        char tar[20] = "";
        sprintf(tar, "%.2f", curr->tariff);
        xmlNewChild(curNode, NULL, "tariff", tar);
        xmlNewChild(curNode, NULL, "got_license", curr->got_license);
        if(curr->next != NULL)
            curr = curr->next;
	}


	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	strcpy(buf, (char*)bufferPtr->content);
	printf("\n\n%s\n\n", buf);
	xmlBufferFree(bufferPtr);

    xmlFreeDoc(doc);
	xmlCleanupParser();
}
int list_size(struct list * tax){
    return tax->size;
}
taxist_t * get_one_tax(struct list * tax, int N){
    taxist_t * curr = tax->head;
    int i;
    for(i = 0; i < N; i++){
        curr = curr->next;
    }
    return curr;
}
void tax_init(taxist_t * tax, char * name, char * surname, int exp, double tar, char * date){
    strcpy(tax->name, name);
    strcpy(tax->surname, surname);
    tax->experience = exp;
    tax->tariff = tar;
    strcpy(tax->got_license, date);
}

char * tax_select(){
    sqlite3 * db = NULL;
    int rc = 0;
    const char * dbFile = "Taxi.db";

    rc = sqlite3_open(dbFile, &db); // open connection to DB
    if (SQLITE_OK != rc){
        printf("Can't open file `%s`\n", dbFile);
        return 1;
    }


    //int rc = 0;
    int count = 0;
    sqlite3_stmt * stmt = NULL;
    char * sql = "SELECT  * FROM Taxi;";
    char * sql_count = "SELECT COUNT(*) FROM Taxi;";
    rc = sqlite3_prepare_v2(db, sql_count, strlen(sql_count), &stmt, NULL);
    do{
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
    struct list * tax_list = list_new();

    taxist_t * tax = malloc(sizeof(taxist_t)*count);
    do{
        rc = sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        if(rc == SQLITE_ERROR)
            break;
    }while(0);
    int i;
    for(i = 0; i < count; i++){
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ERROR)
            break;
        tax_fill(stmt, &tax[i]);
        tax_add(tax_list, &tax[i]);
    }
    sqlite3_finalize(stmt);
    char all[9000] = "";
    return_str_tax(tax_list, all);
    return &all;
}
void tax_fill(sqlite3_stmt * stmt, taxist_t * tax){
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

