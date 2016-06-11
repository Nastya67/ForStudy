#ifndef BOOMB_H_INCLUDED
#define BOOMB_H_INCLUDED

#include <SFML/Graphics.hpp>
#define MAX_CURR_FRAME 4

typedef struct boomb_s Boomb;

Boomb * new_boomb(float time);
bool b_update(Boomb * b, float time);
bool b_exlosion(Boomb * b);
void free_boomb(Boomb * b);

#endif // BOOMB_H_INCLUDED
