#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "taxist.h"
#include <winsock2.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")  // Winsock Library

struct socket_s {
    SOCKET winsock;
};

static socket_t *
socket_new_winsock(SOCKET winsocket) {
    socket_t * self = malloc(sizeof(struct socket_s));
    self->winsock = winsocket;
    return self;
}

socket_t * sock_new(void) {
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

typedef struct{
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


void server_proc(){
    lib_init();
    struct list * taxistu = list_new();
    socket_t * sock = sock_new();
    socket_bind(sock, 5000);
    socket_listen(sock);
    int j = 0;
    while(j < 3){
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
            else if(strcmp(req.uri, "/database") == 0){

                socket_write_string(clientSocket, tax_select());

            }
            else
                socket_write_string(clientSocket, "Error");
        }


        socket_close(clientSocket);
        socket_free(clientSocket);
        j++;
    }
    socket_free(sock);
    lib_free();
    return 0;
}

void proc2(){
    lib_init();
    struct list * taxistu = list_new();
    socket_t * sock = sock_new();
    socket_bind(sock, 5000);
    socket_listen(sock);
    int j = 0;
    char * dirname = malloc(sizeof(char)*30);
    while(j < 3){
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
            /*if(strcmp(req.uri, "/") == 0){
                socket_write_string(clientSocket, "Hello");
               // printf("Empty\n");
            }
            else if(strcmp(req.uri, "/database") == 0){

                socket_write_string(clientSocket, tax_select());

            }
            else
                socket_write_string(clientSocket, "Error");*/

            if(strstr(req.uri, "//dir//") != NULL){
                sscanf(req.uri, "//dir//", dirname);
                const char * testDir1 = "D:\\Настя\\Уроки\\2семестр\\ОП\\KR2";
                printf("Dir exists: %i\n", dir_exists(testDir1));
                printf("Num of files: %i\n", dir_printFiles(testDir1));
            }
        }


        socket_close(clientSocket);
        socket_free(clientSocket);
        j++;
    }
    socket_free(sock);
    lib_free();
    return 0;
}
int dir_exists(const char * dirname) {
    struct stat buffer;
    return (stat (dirname, &buffer) == 0) && S_ISDIR(buffer.st_mode);
}
int dir_printFiles(const char * dirname) {
    DIR *dp;
    struct dirent *ep;
    int file_count = 0;
    dp = opendir (dirname);
    if (dp != NULL) {
        while ((ep = readdir (dp))) {
            if(32 == dp->dd_dta.attrib) {
                puts(dp->dd_dir.d_name);
                file_count++;
            }
        }
        (void) closedir (dp);
        return file_count;
    }
    else {
        return -1;
    }
}
long long file_getSize(const char * filename) {
    struct stat st;
    if (0 != stat(filename, &st)) {
        return -1;
    }
    long long size = st.st_size;
    return size;
}
time_t file_getCreateTime(const char * filename) {
    struct stat st;
    if (0 != stat(filename, &st)) {
        return (time_t)0;
    }
    return st.st_ctime;
}
