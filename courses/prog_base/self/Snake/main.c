#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

const char head[4] = {'^', '>', 'v', '<'};

static int longs = 1;

static int arr[80][25];

void format(int x, int y, int color){//+
    COORD pos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, color);
}
void move(){
    int aqua = BACKGROUND_BLUE | BACKGROUND_GREEN;
    int pos = 0;
    int y = 12, x = 39;
    int speed = 100;
    char strelka = 0, priem = 0;
    while(1){
        if(kbhit()){
            switch(getch()){
            case 75: pos = 3;
                break;
            case 77: pos = 1;
                break;
            case 72: pos = 0;
                break;
            case 80: pos = 2;
                break;
            }
        }
        if(pos == 0){
            y--;
        }
        else if(pos == 1){
            x++;
        }
        else if(pos == 2){
            y++;
        }
        else if(pos == 3){
            x--;
        }
        Sleep(speed);
        format(x, y, aqua);
        printf(" ");
                if(kbhit()){
            switch(getch()){
            case 75: pos = 3;
                break;
            case 77: pos = 1;
                break;
            case 72: pos = 0;
                break;
            case 80: pos = 2;
                break;
            }
        }
    }
}
int main(){
    int aqua = BACKGROUND_BLUE | BACKGROUND_GREEN;
    move();
    return 0;
}
