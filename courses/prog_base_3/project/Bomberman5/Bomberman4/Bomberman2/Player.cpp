#include "Player.h"
#include <cstdlib>

#include <SFML/Graphics.hpp>

struct player_s{
    float dx, dy;
    FloatRect rect;
    float currFrame;
    int max_num_boomb;
    float speed;
    int time_boomb;
    int life;
    int mup[13][15];
};

Player * new_player(int arr[13][15]){
    Player * pl = (Player * )malloc(sizeof(Player));
    pl->rect = FloatRect(46, 100, 37, 57);
    pl->time_boomb = 10;
    pl->dx = pl->dy = 0;
    pl->currFrame = 0;
    pl->max_num_boomb = 1;
    pl->speed = 0.1;
    pl->life = 3;
    for(int i = 0; i < 13; i ++){
        for(int j = 0; j < 15; j ++){
            pl->mup[i][j] = arr[i][j];
        }
    }

    return pl;
}
/*void pl_explosion(Player * pl){
    for(int i = 0; i < pl->max_num_boomb-1; i++){
        //boomb[i] = boomb[i+1];
    }

    pl->cur_num_boomb--;
}*/
void pl_addBoomb(Player * pl, int x, int y){
    pl->mup[x][y] = 3;
}
void pl_update(Player * pl, Sprite & sprite, float time){
    pl->rect.left += pl->dx*time;
    pl_colisionX(pl);
    pl->rect.top += pl->dy*time;
    pl_colisionY(pl);

    pl->currFrame += 0.01*time;
    if(pl->currFrame > MAX_CURR_FRAME)
        pl->currFrame -= MAX_CURR_FRAME;

    if(pl->dx < 0)
        sprite.setTextureRect(IntRect(42*int(pl->currFrame), 60, 37, 58));
    if(pl->dx > 0)
        sprite.setTextureRect(IntRect(42*int(pl->currFrame), 121, 37, 58));
    if(pl->dy < 0)
        sprite.setTextureRect(IntRect(42*int(pl->currFrame), 183, 40, 58));
    if(pl->dy > 0)
        sprite.setTextureRect(IntRect(42*int(pl->currFrame), 0, 40, 58));

    sprite.setPosition(pl->rect.left, pl->rect.top);
    pl->dx = pl->dy = 0;
}
void pl_colisionX(Player * pl){
    for(int i = (pl->rect.top-34)/46; i < (pl->rect.top+pl->rect.height-68)/46; i++){
        for (int j = (pl->rect.left+7)/46; j < (pl->rect.left+pl->rect.width-7)/46; j++){
            if(pl->mup[i][j] == 1 || pl->mup[i][j] == 2){
                if(pl->dx > 0)
                    pl->rect.left = j*46-30;
                if(pl->dx < 0)
                    pl->rect.left = j*46+39;
            }
        }
    }
}
void pl_colisionY(Player * pl){
    for(int i = (pl->rect.top-34)/46; i < (pl->rect.top+pl->rect.height-68)/46; i++){
        for (int j = (pl->rect.left+7)/46; j < (pl->rect.left+pl->rect.width-7)/46; j++){
            if(pl->mup[i][j] == 1 || pl->mup[i][j] ==2){
                if(pl->dy > 0)
                    pl->rect.top = i*46+11;
                if(pl->dy < 0)
                    pl->rect.top = i*46+80;
            }
        }
    }
}
int pl_getRect(Player * pl, char c){
    switch(c){
        case 'l': return pl->rect.left;
        case 'w': return pl->rect.width;
        case 'h': return pl->rect.height;
        case 't': return pl->rect.top;
        default : return 0;
    }
}
int pl_getMaxNumBoomb(Player * pl){
    return pl->max_num_boomb;
}
void pl_left(Player * pl){
    pl->dx = -pl->speed;
}
void pl_right(Player * pl){
    pl->dx = pl->speed;
}
void pl_up(Player * pl){
    pl->dy = -pl->speed;
}
void pl_down(Player * pl){
    pl->dy = pl->speed;
}
void free_player(Player * pl){
    free(pl);
}
