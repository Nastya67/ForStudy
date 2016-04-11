#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "taxist.h"

int main() {
    char line[100];
    char text[1000] = "";
    FILE * fr = fopen("doc.xml", "r");
    while(fgets(line, 100, fr)) {
        strcat(text, line);
    }
    printf("Original:\n%s", text);
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
    taxist_t * tax[3];
    int i;
    for(i = 0; i < 3; i++){
        tax[i] = tax_new();
    }
    for(i = 0; NULL != xCur && i < 3; xCur = xCur->next) {
        if (XML_ELEMENT_NODE == xCur->type) {
            //printf("Tag name <%s>\n", xCur->name);
           for(xKids = xCur->children; NULL != xKids ; xKids = xKids->next) {
                if (XML_ELEMENT_NODE == xKids->type) {
                    const char * content = xmlNodeGetContent(xKids);
                    if(strcmp(xKids->name, "name") == 0)
                        tax_name(tax[i], content);
                    else if(strcmp(xKids->name, "surname") == 0)
                        tax_surname(tax[i], content);
                    else if(strcmp(xKids->name, "years_old") == 0)
                        tax_years_old(tax[i], atoi(content));
                    else if (strcmp(xKids->name, "average_speed") == 0)
                        tax_average_speed(tax[i], atof(content));
                    else if(strcmp(xKids->name, "got_a_drivers_license") == 0) {
                        char * place = tax_got_a_drivers_license_place(tax[i], xmlGetProp(xKids, "place"));
                        char * time = tax_got_a_drivers_license_time(tax[i], content);
                        //printf("\t%10s: %s (%s)\n", xKids->name, place, time);
                        continue;
                    }
                    //printf("\t%10s: %s\n", xKids->name, content);
                }
            }
            i++;
        }
    }
    puts("\nInformation from the structures");
    tax_print(tax);
    tax_free(tax);
	return 0;
}

