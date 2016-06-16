#include "Game.h"

//#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <windows.h>
//#include "Player.h"
#include "Lavel.h"
#include "Menu.h"
#include "Lavel_map.h"
#include "Chose_person.h"
#include "Load.h"

#include <loadMap.h>
#include <sqlite3.h>

typedef struct dynamic_s {
    HMODULE hLib;
    void (*pl_insert_f)(char *name, int lvl, int life, double speed, int boomb);
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = (dynamic_t * )malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->pl_insert_f = NULL;
    //dyn->react_f = NULL;
    if (NULL != dyn->hLib) {
        dyn->pl_insert_f = (void ( *)(char *name, int lvl,
                                      int life, double speed, int boomb))GetProcAddress(dyn->hLib, "pl_insert");

        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}

struct game_s{
    int status;
    lvl_list * lavel;
    int cur_lavel;
    char name[30];
    char sprite[30];
    int num_lvl;
};

Game * new_game(){
    Game * g = (Game * )malloc(sizeof(Game));
    g->num_lvl = 1;
    g->lavel = new_lvlList();
    g->status = MAIN_MENU;
    g->name[0] = '\0';
    g->cur_lavel = 0;
    return g;
}
int game_proc(Game * game, RenderWindow & win){
    switch(game->status){
    case MAIN_MENU: game->status = menu_proc(win);
        break;
    case CHOSE_PERSON: game->status = chose_proc(win, game);
        break;
    case LAVEL_MAP: game->status = lavelMap_proc(game, win);
    if(game->status == LAVEL)
        game->status = SAVE_GAME;
        break;
    case LAVEL: game-> status = lavel_proc(lavel_get(game->lavel, game->cur_lavel), win, (char*)game->sprite);
    l_load(game->lavel, game->cur_lavel);
        break;
    case LOAD_SAVE_GAME: {char * tmp_str = load_proc(&game->num_lvl, (char *)&game->sprite,
                    pl_getCountLife(l_getPlayer(lavel_get(game->lavel, game->cur_lavel))),
                    pl_getCountSpeed(l_getPlayer(lavel_get(game->lavel, game->cur_lavel))),
                    pl_getCountBoomb(l_getPlayer(lavel_get(game->lavel, game->cur_lavel))));
                    printf("----------%s\n", tmp_str);
        strcpy(game->sprite, tmp_str);
                game->status = LAVEL_MAP;
        break;
    }
    case NEXT_LAVEL: game->num_lvl++;
        game-> status = LAVEL_MAP;
        break;
    case SAVE_GAME: {
        dynamic_t * dll = dynamic_init("saveGame.dll");
        if (NULL == dll) {
            printf("Can't load dynamic!\n");
            return 1;
        }
        if (NULL == dll->pl_insert_f) {
            printf("Can't get compare function!\n");
            Sleep(100);
            return 1;
        }
        dll->pl_insert_f(game->sprite, game->num_lvl, 3, 0.05, 1);
        dynamic_clean(dll);
        game-> status = LAVEL;
        break;
    }
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
int game_getNumLvl(Game * game){
    return game->num_lvl;
}
int game_getCurLvl(Game * game){
    return game->cur_lavel;
}
