#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

enum status{UNDEF, STOP, PLAY, PAUS};
typedef struct Player Player;
typedef struct Sound Sound;

Player * new_player();
Sound * new_sound(char * name, char * executor);
void pl_addSound(Player * pl, Sound * sn);
void pl_delSound(Player * pl, int index);
int pl_getStatus(Player * pl);
void pl_setPlay(Player * pl, int index);
void pl_playNaxt(Player * pl);
void pl_playPrev(Player * pl);
void pl_getCurSound(Player * pl, char * name, char * executor);
int pl_getVal(Player * pl);
void pl_setVal(Player * pl, int vol);
void pl_setPause(Player * pl);
void pl_setStop(Player * pl);
void pl_free(Player * pl);


#endif // AUDIO_H_INCLUDED
