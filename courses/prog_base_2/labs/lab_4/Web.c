#include "Web.h"
#include <string.h>
#include "Taxist.h"
#include <stdlib.h>
#include <stddef.h>
#include <winsock2.h>


#pragma comment(lib,"ws2_32.lib")


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

struct socket_s {
    SOCKET winsock;
};

static socket_t * socket_new_winsock(SOCKET winsocket) {
    socket_t * self = malloc(sizeof(struct socket_s));
    self->winsock = winsocket;
    return self;
}

socket_t * socket_new(void) {
    SOCKET winsock = socket(AF_INET, SOCK_STREAM, 0);
    // == INVALID_SOCKET; WSAGetLastError()
    socket_t * self = socket_new_winsock(winsock);
    return self;
}

void socket_free(socket_t * self) {
    closesocket(self->winsock);
    free(self);
}

const char * socket_getIPAddress(socket_t * self) {
    return "(null)";  // @todo
}

int socket_getPortNumber(socket_t * self) {
    return -1;  // @todo
}

int socket_bind(socket_t * self, int portNumber) {
    struct sockaddr_in serveraddr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(portNumber)
    };
    int status = bind(self->winsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // @todo == SOCKET_ERROR
    return status;
}

int socket_listen(socket_t * self) {
    listen(self->winsock, 10);  // @todo param
    return 0; // @todo ?
}

socket_t * socket_accept(socket_t * self) {
    struct sockaddr_in clientaddr;
    int size = sizeof(struct sockaddr_in);
    SOCKET winsock = accept(self->winsock, (struct sockaddr *)&clientaddr, &size);
    if (INVALID_SOCKET == winsock) {
        return NULL;
    }
    socket_t * socket = socket_new_winsock(winsock);
    return socket;
}

int socket_connect(socket_t * self, const char * ipaddress, int portNumber) {
    struct sockaddr_in serveraddr = {
        .sin_addr.s_addr = inet_addr(ipaddress),
        .sin_family = AF_INET,
        .sin_port = htons(portNumber)
    };
    int status = connect(self->winsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // @todo if < 0
    return status;
}

int socket_read(socket_t * self, char * recvBuff, int recvBuffSize) {
    int recvSize = recv(self->winsock, recvBuff, recvBuffSize, 0);
    // @todo == SOCKET_ERROR
    recvBuff[recvSize] = '\0';
    return recvSize;
}

int socket_write(socket_t * self, const char * msg, int msgSize) {
    int status = send(self->winsock, msg, msgSize, 0);
    // @todo < 0
    return status;
}

int socket_write_string(socket_t * self, const char * msg) {
    return socket_write(self, msg, strlen(msg));
}

void socket_close(socket_t * self) {
    closesocket(self->winsock);
}

/* STATIC */

static WSADATA wsa;

void lib_init(void) {
    WSAStartup(MAKEWORD(2, 2), &wsa);
    // @todo check status != 0
}

void lib_free(void) {
    WSACleanup();
}
void server_proc(socket_t * sock, struct list * list){
    while(1){
        if(kbhit()){
            if(getch() == 13)
                break;
        }
        printf("\nWaiting...\n");
        socket_t * clientSocket = socket_accept(sock);
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
        if(strcmp(req.method, "GET") == 0){
            if(strcmp(req.uri, "/api") == 0){
                socket_write_string(clientSocket, reqvOk("text/html", "Hello, World"));
            }
            else if(strcmp(req.uri, "/api/taxists") == 0){
                char buff[3000] = "";
                list_to_xml(list, &buff);
                socket_write_string(clientSocket, reqvOk("application/xml", buff));
            }
            else if(NULL != strstr(req.uri, "/api/taxists/") && (14 == strlen(req.uri) || 15 == strlen(req.uri))){
                char s_accept[] = "0123456789";
                char * piont = strpbrk(req.uri, s_accept);
                int N = atoi(piont);
               // printf("%i\n", N);
                taxist_t * tax = get_one_taxId(list, N);
                if(NULL == tax){
                    socket_write_string(clientSocket, "HTTP/1.1 404 ERROR \n"
                                                        "Content-Type: text/html\n"
                                                        "Content-Length: 30\n"
                                                        "\n<h1>404 Page Not Found!</h1>");
                    socket_close(clientSocket);
                    socket_free(clientSocket);
                    continue;
                }
                char buff[3000] = "";
                tax_to_xml(tax, &buff);
                socket_write_string(clientSocket, reqvOk("application/xml", buff));
            }
            else if(strcmp(req.uri, "/") == 0){
                char text[] = "<html><head><title>Taxi Database</title></head>"
                    "<body><h3>You can see <a href='/taxists'><i>a list of all "
                     "the taxi drivers</i></a></h3></body></html>";
                socket_write_string(clientSocket, reqvOk("text/html", text));
            }
            else if(strcmp(req.uri, "/taxists") == 0){
                char html[1000] = "<html><head><title>Taxi Database</title></head><body>";
                int i;
                for(i = 0; i < list_size(list); i++){
                    char tmp[100] = "";
                    taxist_t * tax = get_one_tax(list, i);
                    sprintf(tmp, "<h3><a href='/taxists/%i'>%s %s</a></h3>", tax_get_id(tax),tax_get_surname(tax), tax_get_name(tax));
                    strcat(html, tmp);
                }
                strcat(html, "<h3><a href='/new-taxist' style=\"color:#3CB371\"><i>create new taxi driver >></i></a></h3></body></html>");
                socket_write_string(clientSocket, reqvOk("text/html", html));
            }
            else if(NULL != strstr(req.uri, "/taxists/") && (10 == strlen(req.uri) || 11 == strlen(req.uri))){
                char s_accept[] = "0123456789";
                char * piont = strpbrk(req.uri, s_accept);
                int N = atoi(piont);

                taxist_t * tax = get_one_taxId(list, N);
                if(NULL == tax){
                    socket_write_string(clientSocket, "HTTP/1.1 404 ERROR \n"
                                                        "Content-Type: text/html\n"
                                                        "Content-Length: 30\n"
                                                        "\n<h1>404 Page Not Found!</h1>");
                    socket_close(clientSocket);
                    socket_free(clientSocket);
                    continue;
                }
                char buff[3000] = "";
                tax_to_html(tax, &buff);
                socket_write_string(clientSocket, reqvOk("text/html", buff));
            }
            else if(strcmp(req.uri, "/new-taxist") == 0){
                char html[] = "<html><head><title>New taxist</title><h2><strong>New taxist"
                    "</strong></h2></head><body><form action=\"/taxists\" method=\"POST\">"
                    "Name:<br><input type=\"text\" name=\"name\" value = \"\"><br>"
                    "Surname:<br><input type=\"text\" name=\"surname\" value = \"\"><br>"
                    "Got license:<br><input type=\"text\" name=\"got_license\" value = \"0000-00-00\"><br>"
                    "Tariff:<br><input type=\"text\" name=\"tariff\" value = \"0.0\"><br>"
                    "Experience:<br><input type=\"text\" name=\"experience\" value = \"0\"><br><br>"
                    "<input type=\"submit\" value='Send POST request' /></form></body></html>";
                    socket_write_string(clientSocket, reqvOk("text/html", html));
            }
            else {
                socket_write_string(clientSocket, "HTTP/1.1 404 ERROR \n"
                                                        "Content-Type: text/html\n"
                                                        "Content-Length: 30\n"
                                                        "\n<h1>404 Page Not Found!</h1>");
            }
        }
        else if(strcmp(req.method, "POST") == 0){
            if(strcmp(req.uri, "/api/taxists") == 0){
                taxist_t * tax = tax_new();
                if(server_add_tax(clientSocket, tax, req) == 0){
                    tax_add(list, tax);
                    char buff[2000] = "";
                    tax_to_xml(tax, &buff);
                    //printf("%s", buff);
                    socket_write_string(clientSocket, reqvOk("application/xml", buff));
                }
                else{
                    socket_close(clientSocket);
                    socket_free(clientSocket);
                    continue;
                }
            }
            else if(strcmp(req.uri, "/taxists") == 0){
                taxist_t * tax = tax_new();
                if(server_add_tax(clientSocket, tax, req) == 0){
                    tax_add(list, tax);
                    char buff[2000] = "";
                    tax_to_html(tax, &buff);
                    //printf("%s", buff);
                    socket_write_string(clientSocket, reqvOk("text/html", buff));
                }
                else{
                    socket_close(clientSocket);
                    socket_free(clientSocket);
                    continue;
                }
            }
        }
        else if(strcmp(req.method, "DELETE") == 0){
            if(NULL != strstr(req.uri, "/api/taxists/")){
                char s_accept[] = "0123456789";
                char * piont = strpbrk(req.uri, s_accept);
                int N = atoi(piont);
                if(N > list_size(list)){
                    socket_write_string(clientSocket, "HTTP/1.1 404 ERROR \n"
                                                        "Content-Type: text/html\n"
                                                        "Content-Length: 30\n"
                                                        "\n<h1>404 Page Not Found!</h1>");
                }
                else{
                    tax_del(list, N);
                    printf("\ndel_ok\n");
                    socket_write_string(clientSocket, reqvOk("application/xml", "delete ok"));
                }
            }
            else if(NULL != strstr(req.uri, "/taxists/")){
                char s_accept[] = "0123456789";
                char * piont = strpbrk(req.uri, s_accept);
                int id = atoi(piont);
                int N = 0;
                /*if(N > list_size(list)){
                    socket_write_string(clientSocket, "Invalid Index");
                }*/
                taxist_t * tax = get_one_taxId(list, id, &N);
                if(NULL == tax){
                    socket_write_string(clientSocket, "HTTP/1.1 404 ERROR \n"
                                                        "Content-Type: text/html\n"
                                                        "Content-Length: 30\n"
                                                        "\n<h1>404 Page Not Found!</h1>");
                    socket_close(clientSocket);
                    socket_free(clientSocket);
                    continue;
                }
                if(N > 0){
                    tax_del(list, N);
                    printf("\ndel_ok from %i\n", N);
                    socket_write_string(clientSocket, reqvOk("text/html", "delete ok"));
                    socket_close(clientSocket);
                    socket_free(clientSocket);
                }

            }
            else
                socket_write_string(clientSocket, "HTTP/1.1 404 ERROR \n"
                                                        "Content-Type: text/html\n"
                                                        "Content-Length: 30\n"
                                                        "\n<h1>404 Page Not Found!</h1>");
        }

        socket_close(clientSocket);
        socket_free(clientSocket);
    }
}
int server_add_tax(socket_t * clientSocket, taxist_t * tax, http_request_t req){
    int i, lll = 0;
    for(i = 0; i < req.formLength; i++){
        printf("%s=%s\n", req.form[i].key, req.form[i].value);
        if(strcmp(req.form[i].key, "name") == 0){
            if(strlen(req.form[i].value) > 20){
                socket_write_string(clientSocket, "To long name\n");
                lll = 1;
                continue;
            }
            tax_repl_name(tax, req.form[i].value);
        }
        else if(strcmp(req.form[i].key, "surname") == 0){
            if(strlen(req.form[i].value) > 20){
                socket_write_string(clientSocket, "To long surname\n");
                lll = 1;
                continue;
            }
            tax_repl_surname(tax, req.form[i].value);
        }
        else if(strcmp(req.form[i].key, "experience") == 0){
            int val;
            int status = sscanf(req.form[i].value, "%i", &val);
            if(status < 1){
                socket_write_string(clientSocket, "Not a number\n");
                lll = 1;
                continue;
            }
            tax_repl_exp(tax, atoi(req.form[i].value));
        }
        else if(strcmp(req.form[i].key, "tariff") == 0){
            float val;
            int status = sscanf(req.form[i].value, "%f", &val);
            if(status < 1){
                socket_write_string(clientSocket, "Not a number\n");
                lll = 1;
                continue;
            }
            tax_repl_tariff(tax, atof(req.form[i].value));
        }
        else if(strcmp(req.form[i].key, "got_license") == 0){
            int year = 0, month = 0, day = 0;
            int status = sscanf(req.form[i].value, "%i-%i-%i", &year, &month, &day);
            if((year%4 == 0 &&
               ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 ||month == 12)&&
               day > 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (month == 2 && day > 29))
               || (year%4 != 0 &&
               ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 ||month == 12)&&
               day > 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (month == 2 && day > 28))
               || month > 12 || day > 31 || status < 3){
                socket_write_string(clientSocket, "Wrong date\n");
                lll = 1;
                continue;
            }
            tax_repl_date(tax, req.form[i].value);
        }
    }
    return lll;
}
char * reqvOk(char * type, char * text){
    char reqv[10024];
    sprintf(reqv,
        "HTTP/1.1 200 OK\n"
        "Content-Type: %s\n"
        "Content-Length: %i\n"
        "\n%s", type, strlen(text), text);
    return reqv;
}


