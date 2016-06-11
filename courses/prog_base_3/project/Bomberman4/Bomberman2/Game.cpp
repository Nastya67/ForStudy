#include "Game.h"

#include <SFML/Graphics.hpp>
#include <string.h>
//#include "Player.h"
#include "Lavel.h"
#include "Menu.h"
#include "Lavel_map.h"
#include "Chose_person.h"



struct game_s{
    int status;
    Lavel * lavel;
    int cur_lavel;
    char name[30];
    char sprite[30];
};

Game * new_game(){
    Game * g = (Game * )malloc(sizeof(Game));
    g->lavel = new_lavel();
    g->status = MAIN_MENU;
    g->name[0] = '\0';
    g->cur_lavel = 0;
    return g;
}
int game_proc(Game * game, RenderWindow & win){
    //char buf[30] = "";
    switch(game->status){
    case MAIN_MENU: game->status = menu_proc(win);
        break;
    case CHOSE_PERSON: game->status = chose_proc(win, game);
        break;
    case LAVEL_MAP: game->status = lavelMap_proc(game, win);
        break;
    case LAVEL: game->status = lavel_proc(game->lavel, win, (char*)game->sprite);
        break;
    case LOAD_SAVE_GAME:
        break;
    case SAVE_GAME:
        break;
    case EXIT:
        break;
    }
    return game->status;
}
void game_end(Game * game){
    free(game->lavel);
    free(game);
}
void game_addSpritePerson(Game * game, char * name){
    strcpy(game->sprite, name);
}
void game_addNamePerson(Game * game, char * name){
    strcpy(game->name, name);
}
void game_setCurLavel(Game * game, int num){
    game->cur_lavel = num;
}
char * game_getNameSprite(Game * game){
    return game->sprite;
}
