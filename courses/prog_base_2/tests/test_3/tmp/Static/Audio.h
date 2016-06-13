#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

enum status{UNDEF, STOP, PLAY, PAUS};
typedef struct Player Player;
typedef struct Sound Sound;

Player * new_player(int num);
void pl_addSound(Player * pl, Sound * sn);
void pl_delSound(Player * pl, int index);
enum status pl_getStatus(Player * pl);
void pl_setPlay(Player * pl, int index);
void pl_playNaxt(Player * pl);
void pl_playPrev(Player * pl);
void pl_getCurSound(Player * pl, char * name, char * executor);


#endif // AUDIO_H_INCLUDED
