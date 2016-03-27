#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thread.h"
#include "mutex.h"
#include "printer.h"

int main(){
    shared_t sharedData1;
    shared_t sharedData2;
    shared_t sharedData3;
    char str_1 [] = "1";
    char str_2 [] = "22";
    char str_3 [] = "333";
    sharedData1.str = malloc(sizeof(char)*5);
    strcpy(sharedData1.str, str_1);
    sharedData1.mu = mutex_new();
    sharedData2.str = malloc(sizeof(char)*5);
    strcpy(sharedData2.str, str_2);
    sharedData2.mu = sharedData1.mu;
    sharedData3.str = malloc(sizeof(char)*5);
    strcpy(sharedData3.str, str_3);
    sharedData3.mu = sharedData1.mu;


    printer_t * str1 = printer_constructor(&sharedData1);
    printer_t * str2 = printer_constructor(&sharedData2);
    printer_t * str3 = printer_constructor(&sharedData3);

    printer_join (str1);
    printer_join (str2);
    printer_join (str3);

    printer_destructor (str1);
    printer_destructor (str2);
    printer_destructor (str3);

    mutex_free(sharedData1.mu);

    return 0;
}
