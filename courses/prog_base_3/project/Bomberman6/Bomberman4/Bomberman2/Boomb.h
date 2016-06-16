#ifndef BOOMB_H_INCLUDED
#define BOOMB_H_INCLUDED

#include <SFML/Graphics.hpp>
#define MAX_CURR_FRAME 4

using namespace sf;

typedef struct boomb_s Boomb;
typedef struct b_list b_list;

b_list * new_bList(float time);
void b_addBoomb(b_list * b, int x, int y);
Boomb * new_boomb(float time);
bool b_update(Boomb * b, Sprite & sprite, float time);
bool b_exlosion(Boomb * b, Sprite & srite);
void free_boomb(Boomb * b);
bool isNULL(b_list * b, int num);
Boomb * b_get(b_list * b, int i);
int b_getX(b_list * b, int i);
int b_getY(b_list * b, int i);
void b_del(b_list * b);

#endif // BOOMB_H_INCLUDED
