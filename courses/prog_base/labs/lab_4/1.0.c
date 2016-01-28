#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
struct notes{
    float d0;
    float d0_d;
    float re;
    float re_d;
    float mi;
    float fa;
    float fa_d;
    float sol;
    float sol_d;
    float lia;
    float lia_d;
    float si;
    int cel;
    int pol;
};
struct Songs{
    char name[20];
    float song[100];
};
struct playList{
    char name[20];
    struct Songs someSong[100];
};
void elochka(struct Songs first){
    int i;
    for(i = 0; i < 29; i++){
        Beep(first.song[i], 500);
    }
}
void format(int x, int y, int color){
    COORD pos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, color);
}
int color(){                //random color
    int pink = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int red = BACKGROUND_RED | BACKGROUND_INTENSITY;
    int yellow = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int aqua = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int blue = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    int lll = rand()%6;
    switch(lll){
        case 0: return pink;
        case 1: return red;
        case 2: return yellow;
        case 3: return green;
        case 4: return aqua;
        case 5: return blue;
    }
}
void pressing(int x1, int x2, int devergencuya, int vkl){   //podsvetka klavish
    int white = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int x, y;
    int colorLoc = color();
    if(devergencuya == 2){
        for(x = x1; x <= x2; x++){
            for(y = 0; y <= 4; y++){
                if(vkl == 1)
                    format(x, y, colorLoc);
                else if(vkl == 0)
                    format(x, y, 7);
                printf(" ");
            }
        }
    }
    else{
        for(x = x1; x <= x2; x++){
            for(y = 0; y <= 9; y++){
                if(devergencuya == -1){
                    if(x == x2 && y < 5){}
                    else{
                        if(vkl == 1)
                            format(x, y, colorLoc);
                        else if(vkl == 0)
                            format(x, y, white);
                        printf(" ");
                    }
                }
                else if(devergencuya == 0){
                    if(x == x2 && y < 5){}
                    else if(x == x1 && y < 5){}
                    else{
                        if(vkl == 1)
                            format(x, y, colorLoc);
                        else if(vkl == 0)
                            format(x, y, white);
                        printf(" ");
                    }
                }
                else if(devergencuya == 1){
                    if(x == x1 && y < 5){}
                    else{
                        if(vkl == 1)
                            format(x, y, colorLoc);
                        else if(vkl == 0)
                            format(x, y, white);
                        printf(" ");
                    }
                }
            }
        }
    }
    format(0, 0, white);
}
void interact (char command){                               //zvyk i kartinka
    int x, y;
    struct notes octave1 = {261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.0, 415.3, 440.0, 466.16, 493.88, 700, 350};
    struct notes octave2 = {523.25, 554.36, 587.32, 622.26, 659.26, 698.46, 739.98, 784.0, 830.6, 880.0, 932.32, 987.75, 700, 350};
    switch(command){
        case ' ':
            Beep(0, octave1.pol);
            break;
        case 'z':
            pressing(0, 3, -1, 1);
            Beep(octave1.d0, octave1.pol);
            pressing(0, 3, -1, 0);
            break;
        case 'x':
            pressing(5, 9, 0, 1);
            Beep(octave1.re, octave1.pol);
            pressing(5, 9, 0, 0);
            break;
        case 'c':
            pressing(11, 15, 1, 1);
            Beep(octave1.mi, octave1.pol);
            pressing(11, 15, 1, 0);
            break;
        case 'v':
            pressing(17, 21, -1, 1);
            Beep(octave1.fa, octave1.pol);
            pressing(17, 21, -1, 0);
            break;
        case 'b':
            pressing(23, 27, 0, 1);
            Beep(octave1.sol, octave1.pol);
            pressing(23, 27, 0, 0);
            break;
        case 'n':
            pressing(29, 33, 0, 1);
            Beep(octave1.lia, octave1.pol);
            pressing(29, 33, 0, 0);
            break;
        case 'm':
            pressing(35, 39, 1, 1);
            Beep(octave1.si, octave1.pol);
            pressing(35, 39, 1, 0);
            break;
        case 's':
            pressing(3, 5, 2, 1);
            Beep(octave1.d0_d, octave1.pol);
            pressing(3, 5, 2, 0);
            break;
        case 'd':
            pressing(9, 11, 2, 1);
            Beep(octave1.re_d, octave1.pol);
            pressing(9, 11, 2, 0);
            break;
        case 'g':
            pressing(21, 23, 2, 1);
            Beep(octave1.fa_d, octave1.pol);
            pressing(21, 23, 2, 0);
            break;
        case 'h':
            pressing(27, 29, 2, 1);
            Beep(octave1.sol_d, octave1.pol);
            pressing(27, 29, 2, 0);
            break;
        case 'j':
            pressing(33, 35, 2, 1);
            Beep(octave1.lia_d, octave1.pol);
            pressing(33, 35, 2, 0);
            break;
        case 'w':
        case ',':
            pressing(41, 45, -1, 1);
            Beep(octave2.d0, octave2.pol);
            pressing(41, 45, -1, 0);
            break;
        case 'e':
        case '.':
            pressing(47, 51, 0, 1);
            Beep(octave2.re, octave2.pol);
            pressing(47, 51, 0, 0);
            break;
        case 'r':
        case '/':
            pressing(53, 57, 1, 1);
            Beep(octave2.mi, octave2.pol);
            pressing(53, 57, 1, 0);
            break;
        case 't':
            pressing(59, 63, -1, 1);
            Beep(octave2.fa, octave2.pol);
            pressing(59, 63, -1, 0);
            break;
        case 'y':
            pressing(65, 69, 0, 1);
            Beep(octave2.sol, octave2.pol);
            pressing(65, 69, 0, 0);
            break;
        case 'u':
            pressing(71, 75, 0, 1);
            Beep(octave2.lia, octave2.pol);
            pressing(71, 75, 0, 0);
            break;
        case 'i':
            pressing(77, 79, 1, 1);
            Beep(octave2.si, octave2.pol);
            pressing(77, 79, 1, 0);
            break;
        case '3':
        case 'l':
            pressing(45, 47, 2, 1);
            Beep(octave2.d0_d, octave2.pol);
            pressing(45, 47, 2, 0);
            break;
        case '4':
        case ';':
            pressing(51, 53, 2, 1);
            Beep(octave2.re_d, octave2.pol);
            pressing(51, 53, 2, 0);
            break;
        case '6':
            pressing(63, 65, 2, 1);
            Beep(octave2.fa_d, octave2.pol);
            pressing(63, 65, 2, 0);
            break;
        case '7':
            pressing(69, 71, 2, 1);
            Beep(octave2.sol_d, octave2.pol);
            pressing(69, 71, 2, 0);
            break;
        case '8':
            pressing(75, 77, 2, 1);
            Beep(octave2.lia_d, octave2.pol);
            pressing(75, 77, 2, 0);
            break;
        case 'Z':
            pressing(0, 3, -1, 1);
            Beep(octave1.d0, octave1.cel);
            pressing(0, 3, -1, 0);
            break;
        case 'X':
            pressing(5, 9, 0, 1);
            Beep(octave1.re, octave1.cel);
            pressing(5, 9, 0, 0);
            break;
        case 'C':
            pressing(11, 15, 1, 1);
            Beep(octave1.mi, octave1.cel);
            pressing(11, 15, 1, 0);
            break;
        case 'V':
            pressing(17, 21, -1, 1);
            Beep(octave1.fa, octave1.cel);
            pressing(17, 21, -1, 0);
            break;
        case 'B':
            pressing(23, 27, 0, 1);
            Beep(octave1.sol, octave1.cel);
            pressing(23, 27, 0, 0);
            break;
        case 'N':
            pressing(29, 33, 0, 1);
            Beep(octave1.lia, octave1.cel);
            pressing(29, 33, 0, 0);
            break;
        case 'M':
            pressing(35, 39, 1, 1);
            Beep(octave1.si, octave1.cel);
            pressing(35, 39, 1, 0);
            break;
        case 'S':
            pressing(3, 5, 2, 1);
            Beep(octave1.d0_d, octave1.cel);
            pressing(3, 5, 2, 0);
            break;
        case 'D':
            pressing(9, 11, 2, 1);
            Beep(octave1.re_d, octave1.cel);
            pressing(9, 11, 2, 0);
            break;
        case 'G':
            pressing(21, 23, 2, 1);
            Beep(octave1.fa_d, octave1.cel);
            pressing(21, 23, 2, 0);
            break;
        case 'H':
            pressing(27, 29, 2, 1);
            Beep(octave1.sol_d, octave1.cel);
            pressing(27, 29, 2, 0);
            break;
        case 'J':
            pressing(33, 35, 2, 1);
            Beep(octave1.lia_d, octave1.cel);
            pressing(33, 35, 2, 0);
            break;
        case 'W':
        case '<':
            pressing(41, 45, -1, 1);
            Beep(octave2.d0, octave2.cel);
            pressing(41, 45, -1, 0);
            break;
        case 'E':
        case '>':
            pressing(47, 51, 0, 1);
            Beep(octave2.re, octave2.cel);
            pressing(47, 51, 0, 0);
            break;
        case 'R':
        case '?':
            pressing(53, 57, 1, 1);
            Beep(octave2.mi, octave2.cel);
            pressing(53, 57, 1, 0);
            break;
        case 'T':
            pressing(59, 63, -1, 1);
            Beep(octave2.fa, octave2.cel);
            pressing(59, 63, -1, 0);
            break;
        case 'Y':
            pressing(65, 69, 0, 1);
            Beep(octave2.sol, octave2.cel);
            pressing(65, 69, 0, 0);
            break;
        case 'U':
            pressing(71, 75, 0, 1);
            Beep(octave2.lia, octave2.cel);
            pressing(71, 75, 0, 0);
            break;
        case 'I':
            pressing(77, 79, 1, 1);
            Beep(octave2.si, octave2.cel);
            pressing(77, 79, 1, 0);
            break;
        case '#':
        case 'L':
            pressing(45, 47, 2, 1);
            Beep(octave2.d0_d, octave2.cel);
            pressing(45, 47, 2, 0);
            break;
        case '$':
        case ':':
            pressing(51, 53, 2, 1);
            Beep(octave2.re_d, octave2.cel);
            pressing(51, 53, 2, 0);
            break;
        case '^':
            pressing(63, 65, 2, 1);
            Beep(octave2.fa_d, octave2.cel);
            pressing(63, 65, 2, 0);
            break;
        case '&':
            pressing(69, 71, 2, 1);
            Beep(octave2.sol_d, octave2.cel);
            pressing(69, 71, 2, 0);
            break;
        case '*':
            pressing(75, 77, 2, 1);
            Beep(octave2.lia_d, octave2.cel);
            pressing(75, 77, 2, 0);
            break;
    }
}
void keyboard(int record){            //just keyboard
    int white = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int x, y, i;
    format(0, 0, 7);
    system("cls");
    for(x = 0; x < 80; x++){
        for(y = 0; y < 25; y++){
            if(y < 5){
                if(x%6 == 0){
                    format(x, y, white);
                    printf("   ");
                }
                else if(x == 15 || x == 39 || x == 57){
                    format(x, y, white);
                    printf(" | ");
                }
            }
            else if(y < 10 && y > 4){
                if((x+3)%6 == 1){
                    format(x, y, white);
                    printf("|");
                }
                else{
                    format(x, y, white);
                    printf(" ");
                }
            }
            else if(y == 10){
                format(x, y, white);
                printf("-");
            }
            else{
                format(x, y, white);
                printf(" ");
            }
        }
    }
    format(0, 0, white);
    char notka;
    while(1){
        notka = getch();
        if(record == 1){
            char melody[100];
            for(i = 0; i < 100; i++){
                if(notka == 13){
                    //addSong(melody);
                    break;
                }
                else
                    melody[i] = notka;
            }
        }
        if(notka == 8 || notka == 13){
            break;
        }
        interact(notka);
    }
}


void outCommand(int pointCommand, char command[3][20]){
    int red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    switch(pointCommand % 3){
    case 0:
        format(0, 2, red);
        printf("%s", command[0]);
        format(0, 4, 7);
        printf("%s", command[1]);
        format(0, 6, 7);
        printf("%s", command[2]);
        break;
    case 1:
        format(0, 2, 7);
        printf("%s", command[0]);
        format(0, 4, red);
        printf("%s", command[1]);
        format(0, 6, 7);
        printf("%s", command[2]);
        break;
    case 2:
        format(0, 2, 7);
        printf("%s", command[0]);
        format(0, 4, 7);
        printf("%s", command[1]);
        format(0, 6, red);
        printf("%s", command[2]);
        break;
    }
}
int choice(int pointCommand, char command[3][20]){
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int lll = 0;
    format(0, 0, 7);
    system("cls");
    format(2, 0, aqua);
    printf("What you wish?");
    outCommand(0, command);
    while(lll == 0){
        switch(getch()){
        case 72: pointCommand--;
            break;
        case 80: pointCommand++;
            break;
        case 13: lll = 1;
            break;
        case 27: return 1;
        }
        outCommand(pointCommand, command);
    }
    switch(pointCommand%3){
    case 0: keyboard(0);
        break;
    case 1: //outPlaylist();
        break;
    case 2: keyboard(1);
        break;
    }
    return 0;
}
int main(){
    char command[3][20] = {"Play the piano", "Look playlists", "Record a new melody"};
    int pointCommand = 0;
    char null = NULL;

    int lll = 0;
    while(lll == 0)
        lll = choice(pointCommand, command);

    return 0;
}
