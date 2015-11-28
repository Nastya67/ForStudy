#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*struct User {
    char username[30];

};*/
int main(){
    char name1[50];
    puts("Please, write file's name");
    scanf("%s", &name1);
    char * fileName1 = &name1;
    char name2[50];
    puts("Please, write second file's name");
    scanf("%s", &name2);
    char * fileName2 = &name2;
    char * mode1 = "r";
    char * mode2 = "w";
    FILE * file1;
    char tmp;

    file1 = fopen(fileName1, mode1);
    if (NULL == file1) {
        puts("Error!");
        return EXIT_FAILURE;
    }

    tmp = fgetc(file1);
    FILE * file2;
    file2 = fopen(fileName2, mode2);
    while (EOF != tmp) {
        fprintf(file2, "%s", tmp);
        tmp = fgetc(file1);
    }

    puts("\nOK!");

    fclose(file1);
    fclose(file2);
    return 0;

}
