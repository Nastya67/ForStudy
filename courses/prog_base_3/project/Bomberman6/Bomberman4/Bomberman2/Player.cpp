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
    int long_b;
};

Player * new_player(int arr[13][15]){
    Player * pl = (Player * )malloc(sizeof(Player));
    pl->rect = FloatRect(46, 100, 37, 57);
    pl->time_boomb = 15;
    pl->dx = pl->dy = 0;
    pl->currFrame = 0;
    pl->max_num_boomb = 2;
    pl->speed = 0.1;
    pl->life = 3;
    pl->long_b = 2;
    for(int i = 0; i < 13; i ++){
        for(int j = 0; j < 15; j ++){
            pl->mup[i][j] = arr[i][j];
        }
    }

    return pl;
}
int  pl_explosion(Player * l, int x, int y){
    for(int i = 1; i < l->long_b; i++){
        if(l->mup[x+i][y] == 1)
            break;
        if(l->mup[x+i][y] == 2){
            l->mup[x+i][y] = 0;
            break;
        }
        if((int)(l->rect.top - 34)/46 == x+i && (int)(l->rect.left+15)/46 == y)
            return 1;
        printf("%i, %i\n", x+i, y);
    }
    //right
    for(int i = 1; i < l->long_b; i++){
        if(l->mup[x-i][y] == 1)
            break;
        if(l->mup[x-i][y] == 2){
            l->mup[x-i][y] = 0;
            break;
        }
         if((int)(l->rect.top - 34)/46 == x-i && (int)(l->rect.left+15)/46 == y)
            return 1;
    }
    //up
    for(int i = 1; i < l->long_b; i++){
        if(l->mup[x][y-i] == 1)
            break;
        if(l->mup[x][y-i] == 2){
            l->mup[x][y-i] = 0;
            break;
        }
        if((int)(l->rect.top - 34)/46 == x && (int)(l->rect.left+15)/46 == y-i)
            return 1;
    }
    //down
    for(int i = 1; i < l->long_b; i++){
        if(l->mup[x][y+i] == 1)
            break;
        //l->mup[x][y+i] = 0;
        if(l->mup[x][y+i] == 2){
            l->mup[x][y+i] = 0;
            break;
        }
        if((int)(l->rect.top - 34)/46 == x && (int)(l->rect.left+15)/46 == y+i)
            return 1;
    }

    return 0;
}
int pl_getMaxTimeBoomb(Player * pl){
    return pl->time_boomb;
}
int pl_getMaxNumBoomb(Player * pl){
    return pl->max_num_boomb;
}
int pl_getLife(Player * pl){
    return pl->life;
}
float pl_getSpeed(Player * pl){
    return pl->speed;
}

int * pl_getCountBoomb(Player * pl){
    return &pl->max_num_boomb;
}
float * pl_getCountSpeed(Player * pl){
    return &pl->speed;
}
int * pl_getCountLife(Player * pl){
    return &pl->life;
}
void pl_addBoomb(Player * pl, int x, int y){
    printf("Player save boomb: %i, %i\n", x, y);
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
