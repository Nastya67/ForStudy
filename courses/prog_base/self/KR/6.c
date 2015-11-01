#include <stdio.h>
#include <stdlib.h>

int Ns1 (char str1[], char str2[]){
    int ns1, i, j;
    for (i = 0; i != NULL; i++){
        for(j = 0; j != NULL; j++){
            do{
                if(str1[i] != str2[j]){
                    ns1++;
                }
            }while (str1[i] == str1[j] || str2[i] == str2[j]);
         }
    }
    return Ns1;
}

int Ns2 (char str1[], char str2[]){
    int ns2, i, j;
    for (i = 0; i != NULL; i++){
        for(j = 0; j != NULL; j++){
            do{
                if(str2[i] != str1[j]){
                    ns2++;
                }
            }while (str1[i] == str1[j] || str2[i] == str2[j]);
         }
    }
    return Ns2;
}

int Os (char str1[], char str2[]){
    int os, i, j;

    for (i = 0; i != NULL; i++){
         for(j = 0; j != NULL; j++){
             do{
                 if(str1[i] == str2[j]){
                      os++;
                  }
            }while (str1[i] == str1[j] || str2[i] == str2[j]);
         }
    }
    return Os;
}


int main(){
    char str1[200];
    char str2[200];
    scanf("%s ", &str1);
    scanf("%s ", &str2);

    Ns1;
    Ns2;
    Os;
    printf("%i, %i, %i", &Ns1, &Ns2, &Os);
}
