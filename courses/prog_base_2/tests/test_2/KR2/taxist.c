#include "taxist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


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

void return_str_tax(struct list * tax, int N, char * buf){
    taxist_t * curr = tax->head;
    int i;
    for(i = 0; i < N; i++){
        curr = curr->next;
    }
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * taxNode = NULL;
	//xmlNode * groupNode = NULL;
	char strBuf[1000];

	doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "Taxist");
	xmlDocSetRootElement(doc, rootNode);

	xmlNewChild(rootNode, NULL, "name", curr->name);
	xmlNewChild(rootNode, NULL, "surname", curr->surname);
	char exp[10] = "";
	sprintf(exp, "%i", curr->experience);
	xmlNewChild(rootNode, NULL, "experience", exp);
	char tar[20] = "";
	sprintf(tar, "%.2f", curr->tariff);
	xmlNewChild(rootNode, NULL, "tariff", tar);
	xmlNewChild(rootNode, NULL, "got_license", curr->got_license);


	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	srtcpy(buf, (char*)bufferPtr->content);
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



