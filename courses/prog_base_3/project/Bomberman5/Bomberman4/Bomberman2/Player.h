#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
//#include "Lavel.h"

#define MAX_CURR_FRAME 4

using namespace sf;

typedef struct player_s Player;

Player * new_player(int arr[13][15]);
void free_player(Player * pl);
void pl_addBoomb(Player * pl, int x, int y);
void pl_update(Player * pl, Sprite & srite, float time);
void pl_left(Player * pl);
void pl_right(Player * pl);
void pl_up(Player * pl);
void pl_down(Player * pl);
void pl_explosion(Player * pl);
int pl_getRect(Player * pl, char c);
void pl_colisionX(Player * pl);
void pl_colisionY(Player * pl);
int pl_getMaxNumBoomb(Player * pl);






#endif // PLAYER_H_INCLUDED
