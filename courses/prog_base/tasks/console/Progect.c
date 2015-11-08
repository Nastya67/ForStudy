#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void)
{
    const long SLEEP_MILLISECONDS = 10;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int aqua = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    int blue = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    COORD pos;  /* ���������, �� ������ ������� ������� */
    pos.X = 0;
    pos.Y = 24;
    SetConsoleTextAttribute(hConsole, blue);
    SetConsoleCursorPosition(hConsole, pos);
    Sleep(SLEEP_MILLISECONDS);
    printf("*");

    while(pos.Y < 25){
        pos.X++;
        if(pos.Y == 24 && pos.X == 24){
            do{
                if((pos.X + pos.Y)%3 == 0 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, blue);
                }
                if((pos.X + pos.Y)%3 == 1 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, aqua);
                }
                if((pos.X + pos.Y)%3 == 2 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, green);
                }
                if((pos.X + pos.Y)%3 == 1 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, blue);
                }
                if((pos.X + pos.Y)%3 == 0 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, aqua);
                }
                if((pos.X + pos.Y)%3 == 2 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, green);
                }
                SetConsoleCursorPosition(hConsole, pos);
                Sleep(SLEEP_MILLISECONDS);
                printf("*");
                pos.X--;
                pos.Y--;
            }while(pos.X > 0);

        }
        if(pos.Y == 24 ){
            do{
                if((pos.X + pos.Y)%3 == 0 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, blue);
                }
                if((pos.X + pos.Y)%3 == 1 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, aqua);
                }
                if((pos.X + pos.Y)%3 == 2 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, green);
                }
                if((pos.X + pos.Y)%3 == 1 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, blue);
                }
                if((pos.X + pos.Y)%3 == 0 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, aqua);
                }
                if((pos.X + pos.Y)%3 == 2 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, green);
                }
                SetConsoleCursorPosition(hConsole, pos);
                Sleep(SLEEP_MILLISECONDS);
                printf("*");
                pos.X--;
                pos.Y--;
            }while(pos.X > -1);

        }
        if(pos.X == 0 && pos.Y >= 0){
            do{
                if((pos.X + pos.Y)%3 == 0 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, blue);
                }
                if((pos.X + pos.Y)%3 == 1 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, aqua);
                }
                if((pos.X + pos.Y)%3 == 2 && (pos.X + pos.Y) <= 52){
                    SetConsoleTextAttribute(hConsole, green);
                }
                if((pos.X + pos.Y)%3 == 1 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, blue);
                }
                if((pos.X + pos.Y)%3 == 0 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, aqua);
                }
                if((pos.X + pos.Y)%3 == 2 && (pos.X + pos.Y) > 52){
                    SetConsoleTextAttribute(hConsole, green);
                }
                SetConsoleCursorPosition(hConsole, pos);
                Sleep(SLEEP_MILLISECONDS);
                printf("*");
                pos.X++;
                pos.Y++;
            }while(pos.Y < 25);
            pos.Y--;
            pos.X--;
        }}

    return EXIT_SUCCESS;
}

