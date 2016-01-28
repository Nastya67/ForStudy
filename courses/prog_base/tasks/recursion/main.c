#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * after(char str[], char * pointEndStr){
    char nul = '0';
    if(*(pointEndStr) == '@'){
        if(*(pointEndStr + 1) != '\0')
            return pointEndStr + 1;
        else return &nul;
    }
    else if((*pointEndStr) == '\0')
        return &nul;
    else
        return after(str, pointEndStr -1);
}

int main(){
    printf("Enter string\n");
    char str[20];
    scanf("%s", &str);
    char * pointEndStr = &str;
    pointEndStr += strlen(str) - 1;
    char symbol;
    strncpy(&symbol ,after(str, pointEndStr), 1);
    printf("\ncharacter after '@' - %c", symbol);
    return 0;
}
