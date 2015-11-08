/*Я ще працюю над цим кодом..він трохи не так працює
Але я це виправляю*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void)
{
    const long SLEEP_MILLISECONDS = 1;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int aqua = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    int blue = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    COORD pos;  /* ñòðóêòóðà, ùî ì³ñòèòü ïîçèö³þ êóðñîðà */
    pos.X = 0;
    pos.Y = 24;
    SetConsoleTextAttribute(hConsole, blue);
    SetConsoleCursorPosition(hConsole, pos);
    Sleep(SLEEP_MILLISECONDS);
    printf("*");
    pos.X++;
    while(1){
        if(pos.Y == 24 && pos.X < 79){
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
            }while(pos.X > 0 && pos.Y != 0);
            if(pos.Y > 0){
                pos.Y--;
            }
            else{
                pos.X++;
            }
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
            }while(pos.Y < 24);
            pos.X++;
        }
        if(pos.Y == 0 && pos.X <= 79){
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
            }while(pos.Y < 24 && pos.X < 79);
            if(pos.X == 79){
                pos.Y--;
            }
            else{
                pos.X++;
            }
        }
        if(pos.X == 79 && pos.Y != 0){
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
            }while(pos.Y > 0);
            pos.X++;
        }
        if(pos.X == 79 && pos.Y ==0){
            SetConsoleTextAttribute(hConsole, blue);
            SetConsoleCursorPosition(hConsole, pos);
            Sleep(SLEEP_MILLISECONDS);
            printf("*");
            break;
        }
    }
    return EXIT_SUCCESS;
}


