#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct comments {
    int like;
    char name[20];
    char str[100];
};
int count(int size, struct comments arr[size]){
    int i, num = 0;
    for(i = 0; i < size; i++){
        if(arr[i].like > 100){
            num++;
        }
    }
    return num;
}
void change(struct comments * pVar, const char * newValue){
    strcpy(pVar->str, newValue);
}
void print(struct comments * pVar){
    printf("Name: %s\n  %s\n  Like: %i\n", pVar->name, pVar->str, pVar->like);
}

int main(){
    int size = 3;
    struct comments arr[size];
    arr[0].like = 100500;
    strcpy(arr[0].name, "Nastya");
    strcpy(arr[0].str, "I Love OP");
    arr[1].like = rand()%50;
    strcpy(arr[1].name, "Vitaliy");
    strcpy(arr[1].str, "We all die.");
    arr[2].like = rand()%600;
    strcpy(arr[2].name,  "Sashka");
    strcpy(arr[2].str, "\"Star Wars\" forever");
    int i;
    for(i = 0; i < size; i++){
        printf("%i.", i+1);
        print(&arr[i]);
    }
    printf("comments that have more than 100 likes: %i\n", count(size, arr));
    printf("\nPlease enter the index comments that you want to change ");
    int index;
    scanf("%i", &index);
    while(index > 3 || index < 1){
        printf("Error. Try again ");
        scanf("%i", &index);
    }
    change(&arr[index-1], "Matan - evil!");
    print(&arr[index-1]);
    return 0;
}
