#include "Audio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Sound{
    char *name;
    char * executor;
    int status;
};
struct Player{
    Sound list_sound[10];
    int cur_num;
    int cur_play;
    int status;
    int volume;
};

Player * new_player(){
    Player * pl = malloc(sizeof(Player));
    pl->cur_num = 0;
    pl->cur_play = 0;
    pl->volume = 10;
    pl->status = UNDEF;
    return pl;
}
Sound * new_sound(char * name, char * executor){
    Sound * sn = malloc(sizeof(Sound));
    sn->name = malloc(sizeof(char)*15);
    sn->executor = malloc(sizeof(char)*15);
    strcpy(sn->executor, executor);
    strcpy(sn->name, name);

    return sn;
}
void pl_addSound(Player * pl, Sound * sn){
    pl->list_sound[pl->cur_num].executor = malloc(sizeof(char)*15);
    pl->list_sound[pl->cur_num].name = malloc(sizeof(char)*15);
    strcpy(pl->list_sound[pl->cur_num].executor, sn->executor);
    strcpy(pl->list_sound[pl->cur_num].name, sn->name);
    pl->list_sound[pl->cur_num].status = UNDEF;
    pl->cur_num++;
}
void pl_delSound(Player * pl, int index){
    int i = 0;
    for(i = index; i < 9; i++){
        strcpy(pl->list_sound[i].executor, pl->list_sound[i+1].executor);
        strcpy(pl->list_sound[i].name, pl->list_sound[i+1].name);
        pl->list_sound[i].status = pl->list_sound[i+1].status;
    }
    pl->cur_num--;
}
int pl_getStatus(Player * pl){
    return pl->status;
}
void pl_setPlay(Player * pl, int index){
    pl->list_sound[pl->cur_play].status = UNDEF;
    pl->list_sound[index].status = PLAY;
    pl->status = PLAY;
    pl->cur_play = index;
}
void pl_playNaxt(Player * pl){
    pl->list_sound[pl->cur_play].status = UNDEF;
    if(pl->cur_play < 9)
        pl->cur_play++;
    pl->list_sound[pl->cur_play].status = PLAY;
}
void pl_playPrev(Player * pl){
    pl->list_sound[pl->cur_play].status = UNDEF;
    if(pl->cur_play > 0)
        pl->cur_play--;
    pl->list_sound[pl->cur_play].status = PLAY;
}
void pl_getCurSound(Player * pl, char * name, char * executor){
    strcpy(name, pl->list_sound[pl->cur_play].name);
    strcpy(executor, pl->list_sound[pl->cur_play].executor);
}
int pl_getVal(Player * pl){
    return pl->volume;
}
void pl_setVal(Player * pl, int vol){
    pl->volume = vol;
}
void pl_setPause(Player * pl){
    pl->status = PAUS;
}
void pl_setStop(Player * pl){
    pl->status = STOP;
}
void pl_free(Player * pl){
    free(pl);
}
