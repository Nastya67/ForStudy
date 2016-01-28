#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void fprocess(const char * pread, const char * pwrite){
    char * mode1 = "r";
    char * mode2 = "w";
    FILE * toread;
    FILE * towrite;
    char tmp;
    int sh = 0, str5 = 0, a = 0;
    toread = fopen(pread, mode1);
    if (NULL == toread) {
        puts("Error!");
        a = 1;
    }
    tmp = fgetc(toread);
    while (EOF != tmp && a != 1) {
        if(tmp == '\n'){
            str5++;
        }
        tmp = fgetc(toread);
        if(str5 == 4)
            break;
    }
    char tmp1 = tmp;
    char str[100];
    str5 = 0;
    while(tmp != '\n' && a != 1){
        str[str5] = tmp;
        str5++;
        if(isspace(tmp1) && !isspace(tmp)){
            sh++;
        }
        tmp1 = tmp;
        tmp = fgetc(toread);
    }
    sh++;
    str[str5] = '\n';
    fclose(toread);
    int lword[sh];
    int i;
    for(i = 0; i < sh; i++)
        lword[i] = 0;
    i = str5 = 0;
    while(str[str5] != '\n' && a != 1 && i < sh){
        if(isspace(str[str5]) && !isspace(str[str5+1])){
           i++;
        }
        if(!isspace(str[str5]))
            lword[i]++;
        str5++;
    }
    int lw_min = lword[0];
    for(i = 0; i < sh; i++){
        if(lw_min > lword[i]){
            lw_min = lword[i];
        }
    }
    towrite = fopen(pwrite, mode2);
    fprintf(towrite, "%i", lw_min);
    fclose(towrite);
    printf("%i", lword[2]);
}

int main(){
    char str1[] = "in.txt";
    char str2[] = "in2.txt";
    const char * pread = &str1;
    const char * pwrite = &str2;
    fprocess(pread, pwrite);
    return 0;
}
