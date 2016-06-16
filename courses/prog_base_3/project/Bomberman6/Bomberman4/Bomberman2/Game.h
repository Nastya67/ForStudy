#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define MAIN_MENU 100
#define CHOSE_PERSON 101
#define LAVEL_MAP 102
#define LAVEL 103
#define LOAD_SAVE_GAME 104
#define SAVE_GAME 105
#define EXIT 106
#define NEXT_LAVEL 107

#include <SFML/Graphics.hpp>

using namespace sf;

typedef struct game_s Game;

Game * new_game();
int game_proc(Game * game, RenderWindow & win);
void game_end();
void game_addSpritePerson(Game * game, char * sprite);
void game_addNamePerson(Game * game, char * name);
void game_setCurLavel(Game * game, int num);
int game_getCurLvl(Game * game);
int game_getNumLvl(Game * game);

char * game_getNameSprite(Game * game);

#endif // GAME_H_INCLUDED
