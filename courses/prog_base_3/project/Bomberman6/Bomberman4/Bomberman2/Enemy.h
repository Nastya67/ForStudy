#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <SFML/Graphics.hpp>
//#include "Lavel.h"

#define MAX_CURR_FRAME 4

using namespace sf;


typedef struct enemy_s Enemy;
typedef struct en_list en_list;
typedef void (*cb_fn)(Enemy * en);
void en_cb_react(Enemy * en, cb_fn cb);


Enemy * new_enemy(int arr[13][15]);
void en_init(Enemy * en,  int arr[13][15]);
Enemy * enemys(int num, int arr[13][15]);
void free_enemy(Enemy * pl);
int en_explosion(Enemy * l, int n, int x, int y);
void en_addBoomb(Enemy * pl, int x, int y);
int en_update(Enemy * pl, Sprite & srite, float time, int x, int y);
void en_left(Enemy * pl);
void en_right(Enemy * pl);
void en_up(Enemy * pl);
void en_down(Enemy * pl);
int en_getRect(Enemy * pl, char c);
int en_colisionX(Enemy * en, int x, int y);
int en_colisionY(Enemy * en, int x, int y);
void react1(Enemy * en);
void react2(Enemy * en);

#endif // ENEMY_H_INCLUDED
