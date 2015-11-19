#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>

void format(int x, int y, int color){
    COORD pos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, color);
}
int main(){
    float prot_y;
    float prot_x;
    int blue = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    int red = BACKGROUND_RED | BACKGROUND_INTENSITY;
    int blue_text = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    int red_text = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int yellow_text = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int x0 = 39;
    int y0 = 12;
    float k = 1;
    while(1){
        for(prot_x = x0, prot_y = 0; prot_y <= 24; prot_y++){
            if((int)(k*(prot_y-y0))%5 == 0){
                format(prot_x, prot_y, 7);
                printf("+");
            }
            else{
                format(prot_x, prot_y, 7);
                printf("|");
            }
        }
        for(prot_x = 0, prot_y = y0; prot_x <= 79; prot_x++){
            if((int)(k*(prot_x-x0))%5 == 0){
                format(prot_x, prot_y, 7);
                printf("+");
            }
            else{
                format(prot_x, prot_y, 7);
                printf("-");
            }
        }
        for(prot_x = -(79-x0); prot_x < 80; prot_x+= 0.1){
            prot_y = -0.5 * k * tan(prot_x/k + 1.5);
            prot_y+= y0;
            prot_x+= x0;
            if(prot_y >= 0 && prot_y < 25 && prot_x < 80 && prot_x >=0){
                format(prot_x, prot_y, red);
                printf(".");
            }
            prot_y-= y0;
            prot_x-= x0;
            prot_y = -k*(pow((prot_x/k), 2) - 5);
            prot_y+= y0;
            prot_x+= x0;
            if(prot_y >= 0 && prot_y < 25 && prot_x < 80 && prot_x >=0){
                format(prot_x, prot_y, blue);
                printf("*");
            }
            prot_y-= y0;
            prot_x-= x0;
        }
        format(0, 0, blue_text);
        printf("y=x^2-5");
        format(0, 1, red_text);
        printf("y=0.5*tg(x+2)");
        format(0, 2, yellow_text);
        printf("Up = \"u\"\nDown = \"d\"\nRight = \"r\"\nLeft = \"l\"");
        prot_x = 0;
        prot_y = 24;
        char doing;
        format(prot_x, prot_y, 7);
        scanf("%c", &doing);
        switch(doing){
            case 'u': y0--;
                break;
            case 'd': y0++;
                break;
            case 'l': x0--;
                break;
            case 'r': x0++;
                break;
            case '+': k = k*1.5;
                break;
            case '-': k = k/1.5;
                break;
        }
        system("cls");
    }
    return EXIT_SUCCESS;
}
