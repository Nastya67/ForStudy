#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <queue.h>

//typedef int (*inspection_f) (queue_t * q);
//typedef void (*react_f)();

typedef struct dynamic_s {
    HANDLE hLib;
    int (*inspection_f) (queue_osnova * q);
    void (*react_f)();
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

void UserChoose(char * file){
    while(1){
        printf("Please select the method of operation of the program.\n");
        printf("1) Announce sunny weather;\n");
        printf("2) Publicize the rainy weather \n");
        char text[10];
        int i;
        scanf("%s", text);
        i = atoi(text);
        if( i == 1){
            strcpy(file, "Dll1.dll");
            break;
        }
        else if(i == 2){
            strcpy(file, "Dll2.dll");
            break;
        }
        system("cls");
    }
}

int main(){
    queue_osnova * q = new_queue_osnova();
    char * file = malloc(sizeof(char)*10);
    UserChoose(file);
    dynamic_t * dll = dynamic_init(file);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->inspection_f) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react_f) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!");

    Sleep(2000);

    queue_t * arr;

    while(1){
        system("cls");
        arr = queue_new(q, rand()%20-5);
        queue_print(q);
        if(dll->inspection_f(q))
            dll->react_f();
        Sleep(2000);
        //system("cls");

    }
    //dynamic_clean(dll);

    return 0;
}
dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->inspection_f = NULL;
    dyn->react_f = NULL;
    if (NULL != dyn->hLib) {
        dyn->inspection_f = (int ( *)(queue_osnova * ))GetProcAddress(dyn->hLib, "inspection");
        dyn->react_f = (void ( *)())GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
