#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

static int arr[80][25];

void format(int x, int y, int color){
    COORD pos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, color);
}
void outAnt(int x, int y, int a, int pos){
    int yellow = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    char ant[4] = {'^', '>', 'v', '<'};
    format(x, y, arr[x][y]);
    printf("%c", ant[a]);
    format(73, 24, yellow);
    printf("%i", pos);
}
void antComeout(int x, int y, int speed){
    const int SLEEP_MILLISECONDS = speed;
    zamena(x, y);
    format(x, y, arr[x][y]);
    Sleep(SLEEP_MILLISECONDS);
    printf(" ");
}
void zamena(int x, int y){
    int black = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int white = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY;
    if(arr[x][y] == white)
        arr[x][y] = black;
    else if(arr[x][y] == black)
        arr[x][y] = white;
}
void moveAnt(int pos){
    int black = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int white = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int x = 39, y = 12, a = 0;
    int speed;
    if(pos == 1)
        speed = speedf();
    else
        speed = 200;
    system("cls");
    arr[x][y] = white;
    outAnt(x, y, a, pos);
    format(0, 0, 14);
    printf("Press any key to stop");
    mov(1, pos, x, y, a, speed);
}
int speedf(){        //..
    int speed;
    printf("\n\nSpeed = ");
    scanf("%i", &speed);
    return speed;
}
void outCommand(){      //printCom, moveAnt, goTo;
    clean();
    int pointC = 0;
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int lll = 0;
    format(0, 0, 7);
    system("cls");
    format(2, 0, aqua);
    printf("What you wish?");
    printCom(pointC);
    while(lll == 0){
        switch(getch()){
        case 72: pointC--;
            break;
        case 80: pointC++;
            break;
        case 13: lll = 1;
            break;
        }
        printCom(pointC);
    }
    switch(pointC%2){
    case 0: moveAnt(1);
    case 1: goTo();
    }
}
void goTo(){            //moveAnt
    system("cls");
    format(0, 0, 7);
    int iterstion;
    printf("to which iteration you want to go?\n");
    scanf("%i", &iterstion);
    moveAnt(iterstion);
}
void printCom(int pointC){//..
    char command[2][30] = {"Watch the movement first", "Go to a particular iteration"};
    int red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    switch(pointC % 2){
    case 0:
        format(0, 2, red);
        printf("%s", command[0]);
        format(0, 4, 7);
        printf("%s", command[1]);
        break;
    case 1:
        format(0, 2, 7);
        printf("%s", command[0]);
        format(0, 4, red);
        printf("%s", command[1]);
        break;
    }
}
void continueStop(int pointCS){//..
    char command[2][30] = {"Continue", "Exit the menu"};
    int red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    switch(pointCS % 2){
    case 0:
        format(0, 2, red);
        printf("%s", command[0]);
        format(0, 4, 7);
        printf("%s", command[1]);
        break;
    case 1:
        format(0, 2, 7);
        printf("%s", command[0]);
        format(0, 4, red);
        printf("%s", command[1]);
        break;
    }
}
void outContStop(int count, int pos, int x, int y, int a, int speed){  //continueStop
    int pointCS = 0;
    int lll = 0;
    continueStop(pointCS);
    while(lll == 0){
        switch(getch()){
        case 72: pointCS--;
            break;
        case 80: pointCS++;
            break;
        case 13: lll = 1;
            break;
        }
        continueStop(pointCS);
    }
    switch(pointCS%2){
    case 0: mov(count, pos, x, y, a, speed);
    case 1: outCommand();
    }
}
void clean(){           //..
    int black = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int i, j;
    for(i = 1; i < 80; i++){
        for(j = 0; j < 25; j++){
            arr[i][j] = black;
        }
    }
}
void mov(int count, int pos, int x, int y, int a, int speed){
    int black = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int white = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY;
    while(!kbhit()){
        if(count <= pos){
            antComeout(x, y, 0);
        }
        else
            antComeout(x, y, speed);
        if(a == 0 && arr[x][y] == white){
            a = 1;
            x++;
        }
        else if(a == 0 && arr[x][y] == black){
            a = 3;
            x--;
        }
        else if(a == 1 && arr[x][y] == white){
            a = 2;
            y++;
        }
        else if(a == 1 && arr[x][y] == black){
            a = 0;
            y--;
        }
        else if(a == 2 && arr[x][y] == white){
            a = 3;
            x--;
        }
        else if(a == 2 && arr[x][y] == black){
            a = 1;
            x++;
        }
        else if(a == 3 && arr[x][y] == white){
            a = 0;
            y--;
        }
        else if(a == 3 && arr[x][y] == black){
            a = 2;
            y++;
        }
        if(x == -1 || x == 80 || y == -1 || y == 25){
           break;
        }
        count++;
        outAnt(x, y, a, count);
    }
    outContStop(count, pos, x, y, a, speed);
}
int main(){
    int white = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_INTENSITY;
    clean();
    int j;
    for(j = 0; j < 25; j++){
        arr[0][j] = white;
    }
    outCommand();
    format(0, 0, 7);
    return 0;
}
