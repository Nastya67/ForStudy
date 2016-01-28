#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
//25 variant;
static int arr[100];
void outp (){
    system("cls");
    int i;
    for(i = 0; i < 100; i++){
        printf("%i ", arr[i]);
    }
}
void push(int point){
    printf("enter value ");
    scanf("%i", &arr[point]);
    outp();
}
void pop(int point){
    int x = arr[point];
    arr[point] = NAN;
    outp();
    printf("\nvalue = %i\n", x);
}
int peek(int point){
    printf("%i\n", arr[point]);
    return arr[point];
}
int count(int point){
    printf("%i\n", point+1);
    return point;
}
int main(){
    int i;
    int point = 0;
    for(i = 0; i < 100; i++){
        arr[i] = NAN;
    }
    arr[0] = 78;
    char str[10];
    outp();
    while(1){
        scanf("%s", &str);
        if (strcmp (str, "push") == 0){
            if(point < 99){
                point++;
                push(point);
            }
            else
                printf("Error! The stack overflowed.\n");
        }
        else if(strcmp (str, "pop") == 0){
            if(point >= 0){
                pop(point);
                point--;
            }
            else
                printf("Error! The stack is empty.\n");
        }
        else if (strcmp (str, "peek") == 0){
            peek(point);
        }
        else if(strcmp (str, "count") == 0){
            count(point);
        }
        else if(strcmp (str, "exit") == 0)
            break;
        else
            printf("ERROR. Try again.\n");
    }
    return 0;
}
