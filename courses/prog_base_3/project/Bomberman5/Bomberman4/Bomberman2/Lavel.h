#ifndef LAVEL_H_INCLUDED
#define LAVEL_H_INCLUDED
#include "Player.h"
#include "Enemy.h"

#define STENA 1
#define KUST 2
#define BOOMB 3
//#include <loadMap.h>

typedef struct lavel_s Lavel;
typedef struct lvl_list lvl_list;

Lavel * new_lavel(int num);
Lavel * lavel_load(int num);
lvl_list * new_lvlList();
Lavel * lavel_get(lvl_list * l_l, int num);
void l_addBoomb(Lavel * l, int x, int y);
void l_clear(Lavel * l, int x, int y);
int l_get(Lavel * l, int x, int y);
void l_initPlayer(Lavel * l, Sprite * sprite);
int lavel_proc(Lavel * l, RenderWindow & win, char * namePers);



#endif // LAVEL_H_INCLUDED
