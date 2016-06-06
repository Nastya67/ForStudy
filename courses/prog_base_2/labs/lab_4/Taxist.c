#include "Taxist.h"
#include <time.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

struct taxist_s {
    int id;
    char name[20];
    char surname[20];
    int experience;
    double tariff;
    char date[30];
    taxist_t * next;
};

struct list{
    taxist_t * head;
    taxist_t * tail;
    int size;
    int curr_id;
};

taxist_t * tax_new(){
    taxist_t * self = malloc(sizeof(taxist_t));
    return self;
}
struct list * list_new(){
    struct list * tax = malloc(sizeof(struct list));
    tax->size = 0;
    tax->curr_id = 0;
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
    self->id = tax->curr_id;
    tax->curr_id++;
    tax->size++;
}
void tax_del(struct list * tax, int N){
    taxist_t * curr = tax->head;
    if(N == 0){
        tax->head = curr->next;
        free(curr);
    }
    else{
        int i;
        for(i = 0; i < N-1 && i < tax->size; i++){
            curr = curr->next;
        }
        taxist_t * tmp = curr->next;
        if(tmp->next != NULL)
            curr->next = tmp->next;
        else
            tax->tail = curr;
        free(tmp);
    }

    tax->size--;
}
void tax_to_xml(taxist_t * tax, char * buf){
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * taxNode = NULL;
	char strBuf[1000];

	doc = xmlNewDoc("1.0");

	rootNode = xmlNewNode(NULL, "Taxist");
	xmlDocSetRootElement(doc, rootNode);

    char id[10] = "";
    sprintf(id, "%i", tax->id);
    xmlNewChild(rootNode, NULL, "id", id);
    xmlNewChild(rootNode, NULL, "name", tax->name);
    xmlNewChild(rootNode, NULL, "surname", tax->surname);
    char exp[10] = "";
    sprintf(exp, "%i", tax->experience);
    xmlNewChild(rootNode, NULL, "experience", exp);
    char tar[20] = "";
    sprintf(tar, "%.2f", tax->tariff);
    xmlNewChild(rootNode, NULL, "tariff", tar);
    xmlNewChild(rootNode, NULL, "got_license", tax->date);

	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	strcpy(buf, (char*)bufferPtr->content);
	xmlBufferFree(bufferPtr);

    xmlFreeDoc(doc);
	xmlCleanupParser();
}
void list_to_xml(struct list * tax, char * buf){
    taxist_t * curr = tax->head;

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

        char id[10] = "";
        sprintf(id, "%i", curr->id);
        xmlNewChild(curNode, NULL, "id", id);
        xmlNewChild(curNode, NULL, "name", curr->name);
        xmlNewChild(curNode, NULL, "surname", curr->surname);
        char exp[10] = "";
        sprintf(exp, "%i", curr->experience);
        xmlNewChild(curNode, NULL, "experience", exp);
        char tar[20] = "";
        sprintf(tar, "%.2f", curr->tariff);
        xmlNewChild(curNode, NULL, "tariff", tar);
        xmlNewChild(curNode, NULL, "got_license", curr->date);
        if(curr->next != NULL)
            curr = curr->next;
	}


	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	strcpy(buf, (char*)bufferPtr->content);
	xmlBufferFree(bufferPtr);

    xmlFreeDoc(doc);
	xmlCleanupParser();
}
void tax_to_html(taxist_t * tax, char * buf){
    sprintf(buf, "<html><head><title>%s %s</title></head>"
            "<body><h2>%s %s</h2><h4>experience: %i year</h4><h4>tariff: %.2f UAH/km</h4>"
            "<h4>got license: %s</h4><a href=\"#\" onclick=\"doDelete()\">Delete</a>"
            "<script>function doDelete(){ var xhttp = new XMLHttpRequest();"
            "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/taxists/%i\", true);"
            "xhttp.send();}"
            "</script></body></html>", tax->name, tax->surname, tax->surname,
            tax->name, tax->experience, tax->tariff, tax->date, tax->id);

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
taxist_t * get_one_taxId(struct list * tax, int id, int * N){
    taxist_t * curr = tax->head;
    int i;
    for(i = 0; i < list_size(tax); i++){
        if(curr->id == id){
            *N = i;
            return curr;
        }
        curr = curr->next;
    }
    *N = -1;
    return NULL;
}
void tax_init(taxist_t * tax, char * name, char * surname, int exp, double tar, char * date){
    strcpy(tax->name, name);
    strcpy(tax->surname, surname);
    tax->experience = exp;
    tax->tariff = tar;
    strcpy(tax->date, date);
}
void tax_parse(struct list * list, int buf_size, char text[buf_size]){
    char * name = malloc(sizeof(char)*15);
    char * surname = malloc(sizeof(char)*15);
    int age = 0;
    double tariff = 0;
    struct tm time;
    //mktime(&time);
    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if (NULL == xDoc) {
        printf("Error parsing xml from memory");
        return 1;
    }
    xmlNode * HeadElem;
    HeadElem = xmlDocGetRootElement(xDoc);
    xmlNode * xCur = HeadElem->children;
    xmlNode * xKids = xCur->children;
    int i;
    for(i = 0; NULL != xCur; xCur = xCur->next) {

        if (XML_ELEMENT_NODE == xCur->type) {
            //printf("tax:\n");
            //printf("Tag name <%s>\n", xCur->name);
           for(xKids = xCur->children; NULL != xKids ; xKids = xKids->next) {
                if (XML_ELEMENT_NODE == xKids->type) {
                    const char * content = xmlNodeGetContent(xKids);
                    if(strcmp(xKids->name, "name") == 0)
                        strcpy(name, content);
                    else if(strcmp(xKids->name, "surname") == 0)
                        strcpy(surname, content);
                    else if(strcmp(xKids->name, "age") == 0)
                        age = atoi(content);
                    else if (strcmp(xKids->name, "tariff") == 0)
                        tariff = atof(content);
                    else if(strcmp(xKids->name, "date") == 0) {
                        sscanf(content, "%i-%i-%i", &time.tm_year, &time.tm_mon, &time.tm_mday);
                        time.tm_year -= 1900;
                        time.tm_mon -= 1;
                    }
                }
            }
            i++;
            char datestr[12] = "";
            sprintf(datestr, "%i-%i-%i", time.tm_year+1900, time.tm_mon+1, time.tm_mday);
            taxist_t * tax = tax_new();
            tax_init(tax, name, surname, age, tariff, datestr);
            tax_add(list, tax);
            //printf("%i, %s, %s, %i, %.2f, %s\n", tax->id, tax->name, tax->surname, tax->experience, tax->tariff,
                  // tax->date);
        }
    }
}
void tax_repl_name(taxist_t * tax, char * name){
    strcpy(tax->name, name);
}
void tax_repl_surname(taxist_t * tax, char * surname){
    strcpy(tax->surname, surname);
}
void tax_repl_exp(taxist_t * tax, int exp){
    tax->experience = exp;
}
void tax_repl_tariff(taxist_t * tax, double tar){
    tax->tariff = tar;
}
void tax_repl_date(taxist_t * tax, char * date){
    strcpy(tax->date, date);
}
int tax_get_id(taxist_t * tax){
    return tax->id;
}
char * tax_get_name(taxist_t * tax){
    char * name = malloc(sizeof(char)*strlen(tax->name));
    strcpy(name, tax->name);
    return name;
}
char * tax_get_surname(taxist_t * tax){
    char * surname = malloc(sizeof(char)*strlen(tax->surname));
    strcpy(surname, tax->surname);
    return surname;
}

