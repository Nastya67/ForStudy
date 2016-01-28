#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<ctype.h>

void format(int x, int y, int color){
    COORD pos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, color);
}
void help(size){
    int x, y;
    int green = FOREGROUND_GREEN;
    y = size+3;
    x = 0;
    format(x, y, green);
    printf("Instruction:");
    format(x, y++, green);
    puts("You can enter the name");
    format(x, y++, green);
    puts("of the function.");
    format(x, y++, 7);
    puts("1.zero - zero out the entire matrix");
    format(x, y++, 7);
    puts("2.rand - fills the array with random numbers");
    format(x, y++, 7);
    puts("3.replacement - changes the value of the");
    format(x, y++, 7);
    puts(" item at the specified index");
    format(x, y++, 7);
    puts("4.h_reflection - flip horizontally");
    format(x, y++, 7);
    puts("5.transpose - reflects the relative lateral horizontal");
    format(x, y++, 7);
    puts("6.turn - rotates clockwise");
    format(x, y++, 7);
    puts("7.average - displays the average value");
    format(x, y++, 7);
    puts("8.sum_column - the sum of the elements of the column");
    format(x, y++, 7);
    puts("9.under_sum - sum of the elements below the main diagonal");
    format(x, y++, 7);
    puts("10.repl_first - first maximum");
    format(x, y++, 7);
    puts(" and minimum elements in some places");
    format(x, y++, 7);
    puts("11.repl_last - last maximum and ");
    format(x, y++, 7);
    puts(" minimum elements in some places");
    format(x, y++, 7);
    puts("12.repl_column - maximum and minimum column in some places");
    format(x, y++, 7);
    puts("13.exit");
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
    for(x = 1; x < size+1; x++){
        for(y = 1; y < size+1; y++){
            format(x, y, blue);
            printf(" ");
        }
    }
    for(x = 0, y = 0; x < 5*size+1; x++){
        format(x, y, blue2);
        printf("*");
    }
    for(x = 0, y = size+1; x < 5*size+1; x++){
        format(x, y, blue2);
        printf("*");
    }
    for(x = 0, y = 0; y < size+2; y++){
        format(x, y, blue2);
        printf("*");
    }
    for(x = 5*size+1, y = 0; y < size+2; y++){
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
float average(int size, int matrix[size][size]){
    int i, j, n = 0, sum = 0;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            sum += matrix[i][j];
            n++;
        }
    }
    return (float)sum/n;
}
int sumColumn(int size, int matrix[size][size], int column){
    int i, sum = 0;
    for(i = 0; i < size; i++){
        sum += matrix[i][column-1];
    }
    return sum;
}
int under_sum(int size, int matrix[size][size]){
    int i, j, sum = 0;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(i >= j){
                sum += matrix[i][j];
            }
        }
    }
    return sum;
}
void firstrepl(int size, int matrix[size][size]){
    int i, j, imax = 0, jmax = 0, imin = 0, jmin = 0, temp, min = matrix[0][0], max = matrix[0][0];
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(min > matrix[i][j]){
                min = matrix[i][j];
                imin = i;
                jmin = j;
            }
            if(max < matrix[i][j]){
                max = matrix[i][j];
                imax = i;
                jmax = j;
            }
        }
    }
    temp = matrix[imax][jmax];
    matrix[imax][jmax] = matrix[imin][jmin];
    matrix[imin][jmin] = temp;
    outp(size, matrix);
}
void lastrepl(int size, int matrix[size][size]){
    int i, j, imax = 0, jmax = 0, imin = 0, jmin = 0, temp, min = matrix[0][0], max = matrix[0][0];
    for(i = size-1; i >= 0; i--){
        for(j = size-1; j >= 0; j--){
            if(min > matrix[i][j]){
                min = matrix[i][j];
                imin = i;
                jmin = j;
            }
            else if(max < matrix[i][j]){
                max = matrix[i][j];
                imax = i;
                jmax = j;
            }
        }
    }
    temp = matrix[imax][jmax];
    matrix[imax][jmax] = matrix[imin][jmin];
    matrix[imin][jmin] = temp;
    outp(size, matrix);
}
void compareColumn(int size, int matrix[size][size]){
    int j, i, sum[size];
    for(i = 0; i < size; i++){
        sum[i] = 0;
    }
    for(j = 0; j < size; j++){
        for(i = 0; i < size; i++){
            sum[j] += matrix[i][j];
        }
    }
    int maxC = sum[0], minC = sum[0], jmax = 0, jmin = 0;
    for(j = 0; j < size; j++){
        if(minC > sum[j]){
            minC = sum[j];
            jmin = j;
        }
        else if(maxC < sum[j]){
            maxC = sum[j];
            jmax = j;
        }
    }
    int tmp;
    for(i = 0; i < size; i++){
        tmp = matrix[i][jmax];
        matrix[i][jmax] = matrix[i][jmin];
        matrix[i][jmin] = tmp;
    }
    outp(size, matrix);
}

int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int blue = BACKGROUND_BLUE;
    int size, x, y;
    char siz[3];
    printf("Size of matrix [2-15] = ");
    scanf("%s", siz);
    while(1){
        if(!isdigit(siz[0]) && !isdigit(siz[1])){
            SetConsoleTextAttribute(hConsole, 12);
            printf("ERROR. Please try again. Enter the number\n");
            SetConsoleTextAttribute(hConsole, 7);
            printf("Size of matrix [2-15] = ");
            scanf("%s", siz);
        }
        else  size = atoi(siz);
        if(size < 2 || size > 15){
            SetConsoleTextAttribute(hConsole, 12);
            printf("ERROR. Please try again.\n");
            SetConsoleTextAttribute(hConsole, 7);
            printf("Size of matrix [2-15] = ");
        }
        else  break;
        scanf("%s", siz);
    }
    int matrix[size][size];
    char str[100];
    int min, max;
    printf("Please, specify the range of from .. ,to ..\n");
    scanf("%i, %i", &min, &max);
    random(size, matrix, min, max);
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
        else if(strcmp (str, "h_reflection") == 0){
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
        else if(strcmp (str, "average") == 0){
            printf("%.4f\n", average(size, matrix));
        }
        else if(strcmp (str, "sum_column") == 0){
            int column;
            scanf("%i", &column);
            printf("sum column = %i\n", sumColumn(size, matrix, column));
        }
        else if(strcmp (str, "under_sum") == 0){
            printf("sum (under the lower diagonal) = %i\n", under_sum(size, matrix));
        }
        else if(strcmp (str, "repl_first") == 0){
            firstrepl(size, matrix);
        }
        else if(strcmp (str, "repl_last") == 0){
            lastrepl(size, matrix);
        }
        else if(strcmp (str, "repl_column") == 0){
            compareColumn(size, matrix);
        }
        else if(strcmp (str, "exit") == 0){
            printf("Goodbye :)\n");
            break;
        }
        else if(strcmp (str, "help") == 0){
            help(size);
        }
        else{
            SetConsoleTextAttribute(hConsole, 12);
            printf("ERROR. Please try again.\n");
        }
    }
    return 0;
}
