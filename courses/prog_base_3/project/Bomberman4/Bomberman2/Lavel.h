#ifndef LAVEL_H_INCLUDED
#define LAVEL_H_INCLUDED
#include "Player.h"

#define STENA 1
#define KUST 2
#define BOOMB 3

typedef struct lavel_s Lavel;

Lavel * new_lavel();
void l_addBoomb(Lavel * l, int x, int y);
void l_clear(Lavel * l, int x, int y);
int l_get(Lavel * l, int x, int y);
void l_initPlayer(Lavel * l, Sprite * sprite);
int lavel_proc(Lavel * l, RenderWindow & win, char * namePers);

#endif // LAVEL_H_INCLUDED
