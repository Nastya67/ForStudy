#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
int main(void){
    char * inputStr     = NULL;
    char * numCharPtr   = NULL;
    char * numCharPtr2 = NULL;
    char * num          = "1234567890";
    int  * count        = NULL;
    int  * i            = NULL;
    int  * value        = NULL;

    inputStr = (char *) malloc(50 * sizeof(char));
    count = (int  *) malloc( 1 * sizeof(int ));
    i    = (int  *) malloc( 1 * sizeof(int ));
    value = (int  *) malloc( 1 * sizeof(int ));
    if (NULL == inputStr || NULL == count){
        printf("Alloc error");
        return EXIT_FAILURE;
    }
    *count = 0;
    printf("Please, input string: ");
    scanf("%s", inputStr);
    numCharPtr = strpbrk(inputStr, num);
    while (NULL != numCharPtr) {
        (*count) ++;
        numCharPtr = strpbrk(numCharPtr + 1, num);
    }
    if(*count > 0){
        numCharPtr2 = strpbrk(inputStr, num);
        for(*i = *count - 1; *i > 0; (*i)--){
            numCharPtr2 = strpbrk(numCharPtr2 + 1, num);
        }
        *value = atoi(numCharPtr2);
    }
    printf("\nThe last digit.: %i", *value);
    free(inputStr);
    free(count);
    free(i);
    free(value);
    return EXIT_SUCCESS;
}
