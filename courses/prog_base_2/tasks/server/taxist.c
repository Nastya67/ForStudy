#include "taxist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


struct taxist_s {
    char taxist [300];
    taxist_t * next;
};

struct list{
    taxist_t * head;
    taxist_t * tail;
    int size;
};

taxist_t * tax_new(char * text){
    taxist_t * self = malloc(sizeof(taxist_t));
    strcpy(self->taxist, text);
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
void tax_parse(struct list * tax, char * text){
    int length = strlen(text);
    char * nachalo = malloc(sizeof(char)*length);
    nachalo = strstr(text, "<taxi_driver>");
    char * end = malloc(sizeof(char)*(length+10));
    end = strstr(nachalo, "</taxi_driver>");
    char text2[250] = "";
    strncpy(text2, nachalo, (size_t)(strlen(nachalo)-strlen(end)+strlen("</taxi_driver>")));
    text2[strlen(nachalo)-strlen(end)+strlen("</taxi_driver>")] = '\0';
    taxist_t * some_tax = tax_new(text2);
    tax_add(tax, some_tax);
    int i;
    for(i = 0; i < 2; i++){
        nachalo = strstr(end, "<taxi_driver>");
        end = strstr(nachalo, "</taxi_driver>");
        memset(text2, 0, 250);
        strncpy(text2, nachalo, (size_t)(strlen(nachalo)-strlen(end)+strlen("</taxi_driver>")));
        text2[strlen(nachalo)-strlen(end)+strlen("</taxi_driver>")] = '\0';
        taxist_t * some_tax2 = tax_new(text2);
        tax_add(tax, some_tax2);
    }
    memset(text2, 0, 250);
    free(nachalo);
    free(end);
}
void return_str_tax(struct list * tax, int N, char * buf){
    taxist_t * curr = tax->head;
    int i;
    for(i = 0; i < N; i++){
        curr = curr->next;
    }
    strcpy(buf, curr->taxist);
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
void tax_repl_name(struct list * tax, int N, char * name){
    taxist_t * curr = get_one_tax(tax, N);
    char * tmp1 = malloc(sizeof(char)*300);
    tmp1 = strstr(curr->taxist, "</name>");
    char * tmp2 = "<taxi_driver>\n<name>";
    sprintf(curr->taxist, "%s%s%s", tmp2, name, tmp1);
    free(tmp1);
}
void tax_repl_surname(struct list * tax, int N, char * surname){
    taxist_t * curr = get_one_tax(tax, N);
    char * after = malloc(sizeof(char)*300);
    strcpy(after, strstr(curr->taxist, "</surname>"));
    char * before = malloc(sizeof(char)*300);
    strcpy(before, curr->taxist);
    char * tmp3 = malloc(sizeof(char)*300);
    strcpy(tmp3, strstr(curr->taxist, "<surname>"));
    before[strlen(curr->taxist)-strlen(tmp3)+strlen("<surname>")] = '\0';
    sprintf(curr->taxist, "%s%s%s", before, surname, after);
    free(after);
    free(before);
    free(tmp3);
}
void tax_repl_age(struct list * tax, int N, int age){
    taxist_t * curr = get_one_tax(tax, N);
    char * after = malloc(sizeof(char)*300);
    strcpy(after, strstr(curr->taxist, "</years_old>"));
    char * before = malloc(sizeof(char)*300);
    strcpy(before, curr->taxist);
    char * tmp3 = malloc(sizeof(char)*300);
    strcpy(tmp3, strstr(curr->taxist, "<years_old>"));
    before[strlen(curr->taxist)-strlen(tmp3)+strlen("<years_old>")] = '\0';
    sprintf(curr->taxist, "%s%i%s", before, age, after);
    printf("%s", curr->taxist);
    free(after);
    free(before);
    free(tmp3);
}
void tax_repl_speed(struct list * tax, int N, double speed){
    taxist_t * curr = get_one_tax(tax, N);
    char * after = malloc(sizeof(char)*300);
    strcpy(after, strstr(curr->taxist, "</average_speed>"));
    char * before = malloc(sizeof(char)*300);
    strcpy(before, curr->taxist);
    char * tmp3 = malloc(sizeof(char)*300);
    strcpy(tmp3, strstr(curr->taxist, "<average_speed>"));
    before[strlen(curr->taxist)-strlen(tmp3)+strlen("<average_speed>")] = '\0';
    sprintf(curr->taxist, "%s%.3f%s", before, speed, after);
    free(after);
    free(before);
    free(tmp3);
}
void tax_repl_place(struct list * tax, int N, char * place){
    taxist_t * curr = get_one_tax(tax, N);
    char * after = malloc(sizeof(char)*300);
    strcpy(after, strstr(curr->taxist, "'>"));
    char * before = malloc(sizeof(char)*300);
    strcpy(before, curr->taxist);
    char * tmp3 = malloc(sizeof(char)*300);
    strcpy(tmp3, strstr(curr->taxist, "place="));
    before[strlen(curr->taxist)-strlen(tmp3)+strlen("place=")] = '\0';
    sprintf(curr->taxist, "%s'%s%s", before, place, after);
    free(after);
    free(before);
    free(tmp3);
}
void tax_repl_time(struct list * tax, int N, char * date){
    taxist_t * curr = get_one_tax(tax, N);
    char * after = malloc(sizeof(char)*300);
    strcpy(after, strstr(curr->taxist, "</got_a_drivers_license>"));
    char * before = malloc(sizeof(char)*300);
    strcpy(before, curr->taxist);
    char * tmp3 = malloc(sizeof(char)*300);
    strcpy(tmp3, strstr(curr->taxist, "'>"));
    before[strlen(curr->taxist)-strlen(tmp3)+strlen("'>")] = '\0';
    sprintf(curr->taxist, "%s%s%s", before, date, after);
    printf("%s", curr->taxist);
    free(after);
    free(before);
    free(tmp3);
}

