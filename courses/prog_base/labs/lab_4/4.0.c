#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
struct notes{   //+
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
struct Songs{ //+;
    char name[20];
    float nots[100];
    time_t pause[100];
};
struct playLists{    //+
    char namelist[20];
    struct Songs someSong[100];
};
struct playLists arrPlaylist[20];
void playSongs(char nots[100], float paus[100], int Album, int newS){
    int i = 0;
    while(i < 100 && strcmp(&nots[i], "\0")){
        float start, k = 0.0;
        start = clock();
        while(k < paus[i]){
            k +=  clock() - start;
            start = clock();
        }
        interact(nots[i], 0);
        i++;
    }
    if(newS >= 0)
        addSong(arrPlaylist, Album, nots, paus);
    else
        choiceSong(arrPlaylist, Album);
}
struct timeval tv1,tv2,dtv;
void time_start(){
    gettimeofday(&tv1);
}
long time_stop(){
    gettimeofday(&tv2);
    dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;
    dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;
    if(dtv.tv_usec<0){
        dtv.tv_sec--; dtv.tv_usec+=1000000;
    }
    return dtv.tv_sec*1000+dtv.tv_usec/1000;
}
void format(int x, int y, int color){//+
    COORD pos = {x, y};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, color);
}
int color(){                //random color//+
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
void pressing(int x1, int x2, int devergencuya, int vkl){   //podsvetka klavish//+
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
void interact (char command, int video){                               //zvyk i kartinka//+
    int x, y;
    struct notes octave1 = {261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.0, 415.3, 440.0, 466.16, 493.88, 700, 350};
    struct notes octave2 = {523.25, 554.36, 587.32, 622.26, 659.26, 698.46, 739.98, 784.0, 830.6, 880.0, 932.32, 987.75, 700, 350};
    if(video == 1){
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
    else{
        switch(command){
            case ' ': Beep(0, octave1.pol);
                break;
            case 'z': Beep(octave1.d0, octave1.pol);
                break;
            case 'x': Beep(octave1.re, octave1.pol);
                break;
            case 'c': Beep(octave1.mi, octave1.pol);
                break;
            case 'v': Beep(octave1.fa, octave1.pol);
                break;
            case 'b': Beep(octave1.sol, octave1.pol);
                break;
            case 'n':Beep(octave1.lia, octave1.pol);
                break;
            case 'm': Beep(octave1.si, octave1.pol);
                break;
            case 's': Beep(octave1.d0_d, octave1.pol);
                break;
            case 'd': Beep(octave1.re_d, octave1.pol);
                break;
            case 'g': Beep(octave1.fa_d, octave1.pol);
                break;
            case 'h': Beep(octave1.sol_d, octave1.pol);
                break;
            case 'j': Beep(octave1.lia_d, octave1.pol);
                break;
            case 'w':
            case ',':Beep(octave2.d0, octave2.pol);
                break;
            case 'e':
            case '.': Beep(octave2.re, octave2.pol);
                break;
            case 'r':
            case '/': Beep(octave2.mi, octave2.pol);
                break;
            case 't': Beep(octave2.fa, octave2.pol);
                break;
            case 'y': Beep(octave2.sol, octave2.pol);
                break;
            case 'u': Beep(octave2.lia, octave2.pol);
                break;
            case 'i': Beep(octave2.si, octave2.pol);
                break;
            case '3':
            case 'l': Beep(octave2.d0_d, octave2.pol);
                break;
            case '4':
            case ';': Beep(octave2.re_d, octave2.pol);
                break;
            case '6': Beep(octave2.fa_d, octave2.pol);
                break;
            case '7': Beep(octave2.sol_d, octave2.pol);
                break;
            case '8': Beep(octave2.lia_d, octave2.pol);
                break;
            case 'Z': Beep(octave1.d0, octave1.cel);
                break;
            case 'X': Beep(octave1.re, octave1.cel);
                break;
            case 'C': Beep(octave1.mi, octave1.cel);
                break;
            case 'V': Beep(octave1.fa, octave1.cel);
                break;
            case 'B': Beep(octave1.sol, octave1.cel);
                break;
            case 'N': Beep(octave1.lia, octave1.cel);
                break;
            case 'M': Beep(octave1.si, octave1.cel);
                break;
            case 'S': Beep(octave1.d0_d, octave1.cel);
                break;
            case 'D': Beep(octave1.re_d, octave1.cel);
                break;
            case 'G': Beep(octave1.fa_d, octave1.cel);
                break;
            case 'H': Beep(octave1.sol_d, octave1.cel);
                break;
            case 'J': Beep(octave1.lia_d, octave1.cel);
                break;
            case 'W':
            case '<': Beep(octave2.d0, octave2.cel);
                break;
            case 'E':
            case '>': Beep(octave2.re, octave2.cel);
                break;
            case 'R':
            case '?': Beep(octave2.mi, octave2.cel);
                break;
            case 'T': Beep(octave2.fa, octave2.cel);
                break;
            case 'Y': Beep(octave2.sol, octave2.cel);
                break;
            case 'U': Beep(octave2.lia, octave2.cel);
                break;
            case 'I': Beep(octave2.si, octave2.cel);
                break;
            case '#':
            case 'L': Beep(octave2.d0_d, octave2.cel);
                break;
            case '$':
            case ':': Beep(octave2.re_d, octave2.cel);
                break;
            case '^': Beep(octave2.fa_d, octave2.cel);
                break;
            case '&': Beep(octave2.sol_d, octave2.cel);
                break;
            case '*': Beep(octave2.lia_d, octave2.cel);
                break;
        }
    }
}
void keyboard(int record){            //just keyboard//+/-
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
    float pause[100];
    while(1){
        if(record >= 0){
            char melody[100];
            strcpy(&melody, "\0");
            for(i = 0; i < 100; i++){
                time_start();
                notka = getch();
                if(i == 0)
                    pause[i] = 0.0;
                else
                    pause[i] = time_stop();
                interact(notka, 1);
                if(notka == 13){
                    playSongs(melody, pause, record, 1);
                    break;
                }
                else
                    melody[i] = notka;
            }break;
        }
        else{
            notka = getch();
            interact(notka, 1);
        }
        if(notka == 8){
            break;
        }

    }
}
void outCommand(int pointCommand, int n, char command[n][20], int x){//+
    int red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int i;
    for(i = 0; i < n; i++){
        if(i == pointCommand%n)
            format(x, 2*i+2, red);
        else
            format(x, 2*i+2, 7);
        printf("%s", command[i]);
    }
}
int choice(int pointCommand){//+
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    char command[3][20] = {"Play the piano", "Look playlists", "Record a new melody"};
    int lll = 0;
    format(0, 0, 7);
    system("cls");
    format(2, 0, aqua);
    printf("What you wish?");
    outCommand(0, 3, command, 0);
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
        outCommand(pointCommand, 3, command, 0);
    }
    switch(pointCommand%3){
    case 0: return 2; //play
    case 1: return 3; //show list
    case 2: return 4; //record
    }
    return 0;
}
void goodbye(){//+
    int aqua = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    int blue = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
    int tblue = BACKGROUND_BLUE;
    int white = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_RED;
    int green = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
    int lll = 0;
    system("cls");
    format(0, 0, white);
    printf("Goodbye..");
    int x, y, y2;
    for(x = 0; x < 80; x++){
        y = rand()%20;
        y2 = y;
        format(x, 24-y, blue);
        printf(" ");
        format(x, 23-y, tblue);
        printf(" ");
        for(;y > 0;y--){
            if(y > y2/2)
                format(x, 25 - y, aqua);
            else
                format(x, 25 - y, green);
            printf(" ");
        }
    }
    format(0, 0, 7);
}
void saveToFile(struct playLists *pointPlaylist){   //+
    char doc[] = "Memory.txt";
    const char * toWrite = &doc;
    char * w = "w";
    FILE * memory;
    memory = fopen(doc, w);
    int i, j;
    for(j = 0; j < 20; j++, pointPlaylist++){
        fprintf(memory, "%s{\n", pointPlaylist->namelist);
        for(i = 0; i < 20; i++){
            fprintf(memory, "%s\n", pointPlaylist->someSong[i].name);
        }
        fprintf(memory, "}\n\n");
    }
    fclose(memory);
}
void readfromFile(struct playLists *pointPlaylist){ //+
    char doc[] = "Memory.txt";
    const char * toRead = &doc;
    char * r = "r";
    FILE * memory;
    memory = fopen(doc, r);
    int i, j = 0;
    char tmp[20];
    while(j < 20){
        fscanf(memory, "%s{", &tmp);
        strncpy(&pointPlaylist->namelist, &tmp, (strlen(&tmp) - 1));
        for(i = 0; i <100; i++){
            fscanf(memory, "%s", pointPlaylist->someSong[i].name);
            if(strcmp(pointPlaylist->someSong[i].name, "}") == 0){
                strcpy(pointPlaylist->someSong[i].name, "\0");
                break;
            }
        }
        pointPlaylist++;
        j++;
    }
    fclose(memory);
}
void addPlaylist(struct playLists arrPlaylist[20]){//+
    int i = 0, aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    system("cls");
    while(strcmp(arrPlaylist[i].namelist, "\0") != 0 && i < 20){
        i++;
    }
    if(i == 20){
        format(2, 0, aqua);
        printf("You have the maximum number of playlists.");
        getch(i);
    }
    else{
        format(2, 0, aqua);
        printf("The name of the new album is ");
        format(0, 2, 7);
        scanf("%s", &arrPlaylist[i].namelist);
    }
    choicePlaylists(arrPlaylist);
}
int choicePlaylists(struct playLists * tmp){
    system("cls");
    int red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int i, numberPlaylists = 0, pointPl = 0, lll = 0;
    format(2, 0, aqua);
    printf("Your playlists");
    for(i = 0; i < 20; i++){
        if(strcmp(arrPlaylist[i].namelist, "\0") != 0){
            numberPlaylists++;
            if(i == 0)
                format(0, 2*numberPlaylists, red);
            else
                format(0, 2*numberPlaylists, 7);
            printf("%s", arrPlaylist[i].namelist);
        }
    }
    while(lll == 0){
        switch(getch()){
        case 72: pointPl--;
            break;
        case 80: pointPl++;
            break;
        case 13: lll = 1;
            break;
        case 8:
            return choice(0);
        }
        outPlaylists(numberPlaylists, arrPlaylist, pointPl);
    }
    menuPlaylist(tmp, pointPl);
}
void menuPlaylist(struct playLists * tmp, int someAlbum){
    int red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    char forChoice[5][20] = {"Look", "Rename", "Delete", "Cancel", "Create a new album"};
    int lll = 0, pointCommand = 0;
    format(65, 0, aqua);
    printf("What to do?");
    outCommand(0, 5, forChoice, 61);
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
        outCommand(pointCommand, 5, forChoice, 61);
    }
    switch(pointCommand%5){
    case 0: choiceSong(tmp, someAlbum);
        break;
    case 1: renamePlaylist(arrPlaylist, someAlbum);
        break;
    case 2: delAlbum(arrPlaylist, someAlbum);
        break;
    case 3: choicePlaylists(arrPlaylist);
        break;
    case 4: addPlaylist(arrPlaylist);
        break;
    }
}
void outPlaylists(int n, struct playLists arrPlaylist[20], int pointPl){
    int i, j, red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    for(i = 0; i < n; i++){
        if(i == pointPl%n)
            format(0, 2*i+2, red);
        else
            format(0, 2*i+2, 7);
        printf("%s", arrPlaylist[i].namelist);
    }
}
void choiceSong(struct playLists * tmp, int someAlbum){
    system("cls");
    int red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int i, numberSong = 0, points = 0, lll = 0;
    format(2, 0, aqua);
    printf("%s", arrPlaylist[someAlbum].namelist);
    for(i = 0; i < 100; i++){
        if(strcmp(arrPlaylist[someAlbum].someSong[i].name, "\0") != 0){
            numberSong++;
            if(i == 0)
                format(0, 2*i+2, red);
            else
                format(0, 2*i+2, 7);
            printf("%s", arrPlaylist[someAlbum].someSong[i].name);
        }
    }
    if(numberSong == 0){
        format(0, 2, 7);
        printf("This album is empty");
        format(0, 4, aqua);
        printf("You want to add songs here?");
        if(getch() == 13)
            keyboard(someAlbum);
        else choicePlaylists(arrPlaylist);
    }
    while(lll == 0){
        switch(getch()){
        case 72: points--;
            break;
        case 80: points++;
            break;
        case 13: lll = 1;
            break;
        case 8:
        return choicePlaylists(arrPlaylist);
        }
        outSongs(numberSong, arrPlaylist[someAlbum] , points);
    }
    menuSong(tmp, someAlbum, points%numberSong);
}
void outSongs(int n, struct playLists someAlbum, int pointS){
    int i, red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    for(i = 0; i < n; i++){
        if(i == pointS%n)
            format(0, 2*i+2, red);
        else
            format(0, 2*i+2, 7);
        printf("%s", someAlbum.someSong[i].name);
    }
}
void delAlbum(struct playLists arrPlaylist[20], int someAlbum){
    strcpy(&arrPlaylist[someAlbum].namelist, "\0");
    int i, j;
    for(i = 0; i < 100; i++){
        strcpy(&arrPlaylist[someAlbum].someSong[i].name, "\0");
        strcpy(&arrPlaylist[someAlbum].someSong[i].nots, "\0");
    }
    for(i = someAlbum; i < 19; i++){
        strcpy(&arrPlaylist[i].namelist, &arrPlaylist[i+1].namelist);
        for(j = 0; j < 19; j++){
            strcpy(&arrPlaylist[i].someSong[j].name, &arrPlaylist[i+1].someSong[j].name);
            strcpy(&arrPlaylist[i].someSong[j].nots, &arrPlaylist[i+1].someSong[j].nots);
        }
    }
    strcpy(&arrPlaylist[19].namelist, "\0");
    for(i = 0; i < 100; i++){
        delSong(arrPlaylist, 19, i);
    }
    choicePlaylists(arrPlaylist);
}
void renamePlaylist(struct playLists arrPlaylist[20], int someAlbum){
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    system("cls");
    format(2, 0, aqua);
    printf("New name:");
    format(0, 2, 7);
    scanf("%s", &arrPlaylist[someAlbum].namelist);
    choicePlaylists(arrPlaylist);
}
void menuSong(struct playLists * tmp, int someAlbum, int numSong){
    int red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int num = 7;
    char forChoice[7][20] = {"Listen", "Rename", "Delete", "Cancel", "Copy", "Insert", "Create a new song"};
    int lll = 0, pointCommand = 0;
    format(65, 0, aqua);
    printf("What to do?");
    outCommand(0, num, forChoice, 61);
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
        outCommand(pointCommand, num, forChoice, 61);
    }
    switch(pointCommand%num){
    case 0: playSongs(arrPlaylist[someAlbum].someSong[numSong].nots, arrPlaylist[someAlbum].someSong[numSong].pause, someAlbum, -1);
        break;
    case 1: renameSong(arrPlaylist, someAlbum, numSong);
        break;
    case 2: delSong(arrPlaylist, someAlbum, numSong);
        break;
    case 3: choiceSong(arrPlaylist, someAlbum);
        break;
    case 4: copySong(arrPlaylist, someAlbum, tmp, numSong);
        break;
    case 5: insertSong(arrPlaylist, someAlbum, tmp, numSong);
        break;
    case 6: keyboard(someAlbum);
        break;
    }
}
void renameSong(struct playLists arrPlaylist[20], int someAlbum , int numberSong){
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    system("cls");
    format(2, 0, aqua);
    printf("New name:");
    format(0, 2, 7);
    scanf("%s", &arrPlaylist[someAlbum].someSong[numberSong].name);
    choiceSong(arrPlaylist, someAlbum);
}
void delSong(struct playLists arrPlaylist[20], int someAlbum , int numberSong){
    strcpy(&arrPlaylist[someAlbum].someSong[numberSong].name, "\0");
    strcpy(&arrPlaylist[someAlbum].someSong[numberSong].nots, "\0");
    int j, i;
    for(j = numberSong; j < 19; j++){
        strcpy(&arrPlaylist[someAlbum].someSong[j].name, &arrPlaylist[someAlbum].someSong[j+1].name);
        strcpy(&arrPlaylist[someAlbum].someSong[j].nots, &arrPlaylist[someAlbum].someSong[j+1].nots);
        for(i = 0; i < 100; i++){
            arrPlaylist[someAlbum].someSong[j].pause[i] = arrPlaylist[someAlbum].someSong[j].pause[i];
        }
    }
    strcpy(&arrPlaylist[someAlbum].someSong[99].name, "\0");
    strcpy(&arrPlaylist[someAlbum].someSong[99].nots, "\0");
    for(i = 0; i < 100; i++){
        arrPlaylist[someAlbum].someSong[99].pause[i] = 0;
    }
    choiceSong(arrPlaylist, someAlbum);
}
void addSong(struct playLists arrPlaylist[20], int someAlbum, char nots[100], float paus[100]){
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    format(0, 0, 7);
    system("cls");
    int i = 0, j;
    while(strcmp(arrPlaylist[someAlbum].someSong[i].name, "\0") != 0 && i < 100){
        i++;
    }
    if(i == 100){
        format(2, 0, aqua);
        printf("You have the maximum number of songs.");
    }
    else{
        format(2, 0, aqua);
        printf("The name of the new song is ");
        format(0, 2, 7);
        scanf("%s", &arrPlaylist[someAlbum].someSong[i].name);
        strcpy(&arrPlaylist[someAlbum].someSong[i].nots, nots);
        for(j = 0; j < 100; j++){
            arrPlaylist[someAlbum].someSong[i].pause[j] = paus[j];
        }
    }
    choiceSong(arrPlaylist, someAlbum);
}
void copySong(struct playLists arrPlaylist[20], int someAlbum , struct playLists * tmp, int numSong){
    int j;
    strcpy(&tmp->someSong[0].name, &arrPlaylist[someAlbum].someSong[numSong].name);
    strcpy(&tmp->someSong[0].nots, &arrPlaylist[someAlbum].someSong[numSong].nots);
    for(j = 0; j < 100; j++){
        tmp->someSong[0].pause[j] = arrPlaylist[someAlbum].someSong[numSong].pause[j];
    }
    choiceSong(tmp, someAlbum);
}
void insertSong(struct playLists arrPlaylist[20], int someAlbum, struct playLists * tmp, int numSong){
    int i = 0, j;
    int aqua = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    while(strcmp(arrPlaylist[someAlbum].someSong[i].name, "\0") != 0 && i < 100){
        i++;
    }
    if(i == 100){
        format(2, 0, aqua);
        printf("You have the maximum number of songs.");
        getch();
    }
    else{
        strcpy(&arrPlaylist[someAlbum].someSong[i].name, &tmp->someSong[0].name);
        strcpy(&arrPlaylist[someAlbum].someSong[i].nots, &tmp->someSong[0].nots);
        for(j = 0; j < 100; j++){
            arrPlaylist[someAlbum].someSong[i].pause[j] = tmp->someSong[0].pause[j];
        }
    }
    choiceSong(tmp, someAlbum);
}
void saveNots(struct playLists *pointPlaylist){
    char doc[] = "Memoryn.txt";
    const char * toWrite = &doc;
    char * w = "w";
    FILE * memory;
    memory = fopen(doc, w);
    int i, j;
    for(j = 0; j < 20; j++, pointPlaylist++){
        fprintf(memory, "%s{\n", pointPlaylist->namelist);
        for(i = 0; i < 20; i++){
            fprintf(memory, "%s\n", pointPlaylist->someSong[i].nots);
        }
        fprintf(memory, "}\n\n");
    }
    fclose(memory);
}
void readNots(struct playLists *pointPlaylist){
    char doc[] = "Memoryn.txt";
    const char * toRead = &doc;
    char * r = "r";
    FILE * memory;
    memory = fopen(doc, r);
    int i, j = 0;
    char tmp[20];
    while(j < 20){
        fscanf(memory, "%s{", &tmp);
        strncpy(&pointPlaylist->namelist, &tmp, (strlen(&tmp) - 1));
        for(i = 0; i <100; i++){
            fscanf(memory, "%s", pointPlaylist->someSong[i].nots);
            if(strcmp(pointPlaylist->someSong[i].nots, "}") == 0){
                strcpy(pointPlaylist->someSong[i].nots, "\0");
                break;
            }
        }
        pointPlaylist++;
        j++;
    }
    fclose(memory);
}
int main(){
    int pointCommand = 0;
    char null = NULL;
    int lll = 0, i;
    struct playLists * pointPlaylist = (struct playLists *)malloc(sizeof(struct playLists));
    pointPlaylist = &arrPlaylist;
    readfromFile(pointPlaylist);
    readNots(pointPlaylist);
    struct playLists * tmp = (struct playLists *)malloc(sizeof(struct playLists));
    while(lll != 1){
        lll = choice(pointCommand);
        switch(lll){
        case 2: keyboard(-1);
            break;
        case 3: choicePlaylists(tmp);
            break;
        case 4: keyboard(0);
            break;
        }
    }
    saveToFile(pointPlaylist);
    saveNots(pointPlaylist);
    free(pointPlaylist);
    free(tmp);
    goodbye();
    return 0;
}
