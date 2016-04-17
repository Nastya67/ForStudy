#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "socket.h"
#include "taxist.h"


typedef struct {
    char key[256];
    char value[256];
} keyvalue_t;

typedef struct {
    char method[8];
    char uri[256];
    keyvalue_t * form;
    int formLength;
} http_request_t;

http_request_t http_request_parse(const char * const request) {
    http_request_t req;
    req.form = NULL;
    req.formLength = 0;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';
    // parse form data
    const char * bodyStartPtr = strstr(request, "\r\n\r\n") + strlen("\r\n\r\n");
    const char * cur = bodyStartPtr;
    const char * pairEndPtr = cur;
    const char * eqPtr = cur;
    while (strlen(cur) > 0) {
        pairEndPtr = strchr(cur, '&');
        if (NULL == pairEndPtr) {
            pairEndPtr = cur + strlen(cur);
        }
        keyvalue_t kv;
        // get key
        eqPtr = strchr(cur, '=');
        ptrdiff_t keyLen = eqPtr - cur;
        memcpy(kv.key, cur, keyLen);
        kv.key[keyLen] = '\0';
        // get value
        eqPtr++;
        ptrdiff_t valueLen = pairEndPtr - eqPtr;
        memcpy(kv.value, eqPtr, valueLen);
        kv.value[valueLen] = '\0';
        // insert key-value pair into request form list
        req.formLength += 1;
        req.form = realloc(req.form, sizeof(keyvalue_t) * req.formLength);
        req.form[req.formLength - 1] = kv;
        cur = pairEndPtr + ((strlen(pairEndPtr) > 0) ? 1 : 0);
    }
    return req;
}

const char * http_request_getArg(http_request_t * self, const char * key) {
    int i;
    for (i = 0; i < self->formLength; i++) {
        if (strcmp(self->form[i].key, key) == 0) {
            return self->form[i].value;
        }
    }
    return NULL;
}

const char * keyvalue_toString(keyvalue_t * self) {
    char * str = malloc(sizeof(char) * (strlen(self->key) + strlen(self->value) + 2));
    sprintf(str, "%s=%s\0", self->key, self->value);
    return str;
}

int main(){
    lib_init();

    char line[100];
    char text[1000] = "";
    FILE * fr = fopen("doc.xml", "r");
    while(fgets(line, 100, fr)) {
        strcat(text, line);
    }
    fclose(fr);
    struct list * taxistu = list_new();
    tax_parse(taxistu, &text);

    socket_t * sock = socket_new();
    socket_bind(sock, 5000);
    socket_listen(sock);
    while(1){
        puts("Waiting for connection..");
        socket_t * clientSocket = socket_accept(sock);
        puts("New clients");

        char buf[1050];
        int readLength = socket_read(clientSocket, buf, 1050);

        if(readLength == 0){
            socket_close(clientSocket);
            socket_free(clientSocket);
            puts("Skipping empty request");
            continue;
        }

        http_request_t req = http_request_parse(buf);
        printf("Method: %s\nURL: %s\n", req.method, req.uri);
        int i;
        for(i = 0; i < req.formLength; i++){
            const * kvStr = keyvalue_toString(&req.form[i]);
            printf("%s\n", kvStr);
            free(kvStr);
        }

        printf("Client sent: \n-----------------\n%s\n---------------\n", buf);
        if(strcmp(req.method, "GET") == 0){
            if(strcmp(req.uri, "/") == 0){
                socket_write_string(clientSocket, "Hello");
               // printf("Empty\n");
            }
            else if(strcmp(req.uri, "/taxists") == 0){
                int i;
                char * toPrint = malloc(sizeof(char)*300);
                char * buf = malloc(sizeof(char)*1000);
                memset(buf, 0, 1000);
                for(i = 0; i < list_size(taxistu); i++){
                    return_str_tax(taxistu, i, toPrint);
                    strcat(toPrint, "\n");
                    strcat(buf, toPrint);
                }
                socket_write_string(clientSocket, buf);
               // printf("Em..\n%i\n", i);
            }
            else if(10 == strlen(req.uri) || 11 == strlen(req.uri)){
                if(NULL != strstr(req.uri, "/taxists/")){
                    char s_accept[] = "0123456789";
                    char * piont = strpbrk(req.uri, s_accept);
                    int N = atoi(piont);
                    char * toPrint = malloc(sizeof(char)*300);
                    if(N > list_size(taxistu)){
                        socket_write_string(clientSocket, "Invalid Index");
                    }
                    else{
                        return_str_tax(taxistu, N, toPrint);
                        socket_write_string(clientSocket, toPrint);
                        //printf("One %i\n", N);
                    }
                }
                else
                    socket_write_string(clientSocket, "Error");
            }
            else
                socket_write_string(clientSocket, "Error");
        }
        else if(strcmp(req.method, "POST") == 0 && NULL != strstr(req.uri, "/taxists/")){
            char s_accept[] = "0123456789";
            char * piont = strpbrk(req.uri, s_accept);
            int N = atoi(piont);
            char * toPrint = malloc(sizeof(char)*300);
            if(N > list_size(taxistu)){
                socket_write_string(clientSocket, "Invalid Index");
            }
            else{
                return_str_tax(taxistu, N, toPrint);
                socket_write_string(clientSocket, toPrint);
                //printf("One %i\n", N);
                int i;
                for(i = 0; i < req.formLength; i++){
                    if(strcmp(req.form[i].key, "name") == 0){
                        if(strlen(req.form[i].value) > 20){
                            socket_write_string(clientSocket, "To long name");
                            return 1;
                        }
                        tax_repl_name(taxistu, N, req.form[i].value);
                    }
                    else if(strcmp(req.form[i].key, "surname") == 0){
                        if(strlen(req.form[i].value) > 20){
                            socket_write_string(clientSocket, "To long surname");
                            return 1;
                        }
                        tax_repl_surname(taxistu, N, req.form[i].value);
                    }
                    else if(strcmp(req.form[i].key, "years_old") == 0){
                        int val;
                        int status = sscanf(req.form[i].value, "%i", &val);
                        if(status < 1){
                            socket_write_string(clientSocket, "Not a number");
                            return 1;
                        }
                        tax_repl_age(taxistu, N, atoi(req.form[i].value));
                    }
                    else if(strcmp(req.form[i].key, "average_speed") == 0){
                        float val;
                        int status = sscanf(req.form[i].value, "%f", &val);
                        if(status < 1){
                            socket_write_string(clientSocket, "Not a number");
                            return 1;
                        }
                        tax_repl_speed(taxistu, N, atof(req.form[i].value));
                    }
                    else if(strcmp(req.form[i].key, "got_a_drivers_license_place") == 0){
                        if(strlen(req.form[i].value) > 20){
                            socket_write_string(clientSocket, "To long name place");
                            return 1;
                        }
                        tax_repl_speed(taxistu, N, req.form[i].value);
                    }
                    else if(strcmp(req.form[i].key, "got_a_drivers_license_date") == 0){
                        //struct tm hire_time;
                        //memset(&hire_time, 0, sizeof(struct tm));
                        int year = 0, month = 0, day = 0;
                        int status = sscanf(req.form[i].value, "%i-%i-%i", &year, &month, &day);
                        if((year%4 == 0 &&
                           ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 ||month == 12)&&
                           day > 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (month == 2 && day > 29))
                           || (year%4 != 0 &&
                           ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 ||month == 12)&&
                           day > 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (month == 2 && day > 28))
                           || month > 12 || day > 31 || status < 3){
                            socket_write_string(clientSocket, "Wrong date");
                            return 1;
                        }
                        tax_repl_time(taxistu, N, req.form[i].value);
                    }
                }
            }
        }
        else if(strcmp(req.method, "DELETE") == 0 && NULL != strstr(req.uri, "/taxists/")){
            if(NULL != strstr(req.uri, "/taxists/")){
                char s_accept[] = "0123456789";
                char * piont = strpbrk(req.uri, s_accept);
                int N = atoi(piont);
                if(N > list_size(taxistu)){
                    socket_write_string(clientSocket, "Invalid Index");
                }
                else{
                    tax_del(taxistu, N);
                }
            }
            else
                socket_write_string(clientSocket, "Error");
        }

        socket_close(clientSocket);
        socket_free(clientSocket);
    }
    socket_free(sock);
    lib_free();
    return 0;
}

