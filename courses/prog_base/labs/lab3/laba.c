#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

void format(int x, int y, int color){
    COORD pos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, color);
}
void zero(int size, int matrix[size][size]){
    int i, j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            matrix[i][j] = 0;
        }
    }
    outp(size, matrix);
}
void random (int size, int matrix[size][size], int min, int max){
    int i, j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            matrix[i][j] = rand()%(max-min+1) + min;
        }
    }
    outp(size, matrix);
}
void outp(int size, int matrix[size][size]){
    format(0, 0, 0);
    system("cls");
    int x, y, i, j;
    int blue = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    int blue2 = BACKGROUND_BLUE;
    for(x = 1; x < 79; x++){
        for(y = 1; y < size+1; y++){
            format(x, y, blue);
            printf(" ");
        }
    }
    for(x = 0, y = 0; x < 80; x++){
        format(x, y, blue2);
        printf("*");
    }
    for(x = 0, y = size+1; x < 80; x++){
        format(x, y, blue2);
        printf("*");
    }
    for(x = 0, y = 0; y < size+2; y++){
        format(x, y, blue2);
        printf("*");
    }
    for(x = 79, y = 0; y < size+2; y++){
        format(x, y, blue2);
        printf("*");
    }
    x = y = 1;
    for(i = 0; i < size; i++){
        format(x, y, blue);
        printf("{");
        for(j = 0; j < size; j++){
            if(j == size-1){
                printf("%3i}\n\n", matrix[i][j]);
                y++;
            }
            else printf("%3i, ", matrix[i][j]);
        }
    }
}
void horizontalReflection (int size, int matrix[size][size]){
    int i, j, mat2[size][size];
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            mat2[i][j] = matrix[size-1 - i][j];
        }
    }
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            matrix[i][j] = mat2[i][j];
        }
    }
    outp(size, matrix);
}
void transpose(int size, int matrix[size][size]){
    int i, j, mat2[size][size];
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            mat2[i][j] = matrix[size-1 - j][size-1 - i];
        }
    }
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            matrix[i][j] = mat2[i][j];
        }
    }
    outp(size, matrix);
}
void turning(int size, int matrix[size][size]){
    int i, j, mat2[size][size];
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            mat2[i][j] = matrix[size-1 - j][i];
        }
    }
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            matrix[i][j] = mat2[i][j];
        }
    }
    outp(size, matrix);
}
int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int size, x, y;
    int blue = BACKGROUND_BLUE;
    printf("Size of matrix [2-15] = ");
    scanf("%i", &size);
    while(1){
        if(size < 2 || size > 15){
            SetConsoleTextAttribute(hConsole, 12);
            printf("ERROR. Please try again.\n");
            SetConsoleTextAttribute(hConsole, 7);
            printf("Size of matrix [2-15] = ");
            scanf("%i", &size);
        }
        else break;
    }
    int matrix[size][size];
    char str[100];
    outp(size, matrix);
    while(1){
        SetConsoleTextAttribute(hConsole, 7);
        scanf("%s", &str);
        if(strcmp (str, "zero") == 0){
            zero(size, matrix);
        }
        else if(strcmp (str, "rand") == 0){
            int min, max;
            SetConsoleTextAttribute(hConsole, 7);
            scanf("%i, %i", &min, &max);
            random(size, matrix, min, max);
        }
        else if(strcmp (str, "horizontalReflection") == 0){
            horizontalReflection(size, matrix);
        }
        else if(strcmp (str, "replacement") == 0){
            int i, j, mean;
            scanf("%i, %i", &i, &j);
            scanf("%i", &mean);
            matrix[i-1][j-1] = mean;
            outp(size, matrix);
        }
        else if(strcmp (str, "transpose") == 0){
            transpose(size, matrix);
        }
        else if(strcmp (str, "turn") == 0){
            turning(size, matrix);
        }
        else{
            SetConsoleTextAttribute(hConsole, 12);
            printf("ERROR. Please try again.\n");
        }
    }
    return 0;
}
