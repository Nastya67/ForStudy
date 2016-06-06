#include <stdio.h>
#include <stdlib.h>
#include "Web.h"
#include "Taxist.h"


int main(){
    char line[100];
    char text[1000] = "";
    FILE * fr = fopen("doc.xml", "r");
    while(fgets(line, 100, fr)) {
        strcat(text, line);
    }
    fclose(fr);
    struct list * list = list_new();
    tax_parse(list, 1000, text);

    char buff[3000] = "";
    list_to_xml(list, buff);
    //printf("\n%s\n", buff);
    lib_init();
    socket_t * sock = socket_new();
    socket_bind(sock, 5000);
    socket_listen(sock);

    server_proc(sock, list);


    socket_free(sock);
    lib_free();
    return 0;
}
