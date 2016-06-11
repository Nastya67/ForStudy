#include "Player.h"
#include <cstdlib>

#include <SFML/Graphics.hpp>

struct player_s{
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currFrame;
    int max_num_boomb;
    int cur_num_boomb;
    float speed;
    //class Boomb boomb[15];
    int time_boomb;
    bool life;
    //Lavel * lavel;
};

Player * new_player(){
    Player * pl = (Player * )malloc(sizeof(Player));
    pl->rect = FloatRect(46, 100, 37, 57);
    pl->time_boomb = 10;
    pl->dx = pl->dy = 0;
    pl->currFrame = 0;
    pl->max_num_boomb = 2;
    pl->cur_num_boomb = 0;
    pl->speed = 0.1;
    pl->life = true;
    //pl->lavel = l;
    return pl;
}
/*void pl_explosion(Player * pl){
    for(int i = 0; i < pl->max_num_boomb-1; i++){
        //boomb[i] = boomb[i+1];
    }

    pl->cur_num_boomb--;
}
void pl_addBoomb(Texture &image){
    int i = (rect.top-34)/46;
    int j = (rect.left+7)/46;
    if(cur_num_boomb < max_num_boomb && carta[i][j] != BOOMB){
        printf("ok\n");
        Boomb b(this, image, time_boomb, i, j);
        boomb[cur_num_boomb] = b;
        cur_num_boomb++;
        //carta[][] = 3;
    }
}*/
void pl_update(Player * pl, Sprite & sprite, float time){
    pl->rect.left += pl->dx*time;
    //pl_colisionX(pl);
    pl->rect.top += pl->dy*time;
    //pl_colisionY(pl);

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
    /*for(int i = 0; i < pl->max_num_boomb; i++){
        //if(boomb[i].update(time))
           // exp();
    }*/

}
/*void pl_colisionX(Player * pl){
    for(int i = (pl->rect.top-34)/46; i < (pl->rect.top+pl->rect.height-68)/46; i++){
        for (int j = (pl->rect.left+7)/46; j < (pl->rect.left+pl->rect.width-7)/46; j++){
            if(l_get(pl->lavel, i, j) == 1 || l_get(pl->lavel, i, j) == 2){
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
            if(l_get(pl->lavel, i, j) == 1 || l_get(pl->lavel, i, j) ==2){
                if(pl->dy > 0)
                    pl->rect.top = i*46+11;
                if(pl->dy < 0)
                    pl->rect.top = i*46+80;
            }
        }
    }
}*/
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
