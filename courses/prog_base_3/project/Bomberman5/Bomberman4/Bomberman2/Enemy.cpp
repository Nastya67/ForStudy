#include "Enemy.h"
#include <cstdlib>

#include <SFML/Graphics.hpp>


struct enemy_s{
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currFrame;
    float speed;
    bool life;
    int mup[13][15];
    cb_fn react;
};
void en_cb_react(Enemy * en, cb_fn cb){
    en->react = cb;
}
Enemy * new_enemy(int arr[13][15]){
    Enemy * en = (Enemy * )malloc(sizeof(Enemy));
    en->rect = FloatRect(46, 100, 37, 57);
    en->dy = 0.1;
    en->dx = 0;
    en->currFrame = 0;
    en->speed = 0.1;
    en->life = true;
    for(int i = 0; i < 13; i ++){
        for(int j = 0; j < 15; j ++){
            en->mup[i][j] = arr[i][j];
        }
    }

    return en;
}
void en_init(Enemy * en,  int arr[13][15]){
    en->rect = FloatRect(46, 100, 37, 57);
    en->dx = en->dy = 0;
    en->currFrame = 0;
    en->speed = 0.1;
    en->life = true;
    for(int i = 0; i < 13; i ++){
        for(int j = 0; j < 15; j ++){
            en->mup[i][j] = arr[i][j];
        }
    }
}
Enemy * enemys(int num, int arr[13][15]){
    Enemy * en = (Enemy*)malloc(sizeof(Enemy)*num);
    for(int i = 0; i < num; i++){
        en_init((Enemy*)&en[i], arr);
    }
    return en;
}
/*void pl_explosion(Player * pl){
    for(int i = 0; i < pl->max_num_boomb-1; i++){
        //boomb[i] = boomb[i+1];
    }

    pl->cur_num_boomb--;
}*/
/*void en_addBoomb(Enemy * en, int x, int y){
    pl->mup[x][y] = 3;
}*/
void en_update(Enemy * en, Sprite & sprite, float time){
    en->rect.left += en->dx*time;
    en_colisionX(en);
    en->rect.top += en->dy*time;
    en_colisionY(en);

    en->currFrame += 0.01*time;
    if(en->currFrame > MAX_CURR_FRAME)
        en->currFrame -= MAX_CURR_FRAME;

    if(en->dx < 0)
        sprite.setTextureRect(IntRect(42*int(en->currFrame), 60, 37, 58));
    if(en->dx > 0)
        sprite.setTextureRect(IntRect(42*int(en->currFrame), 121, 37, 58));
    if(en->dy < 0)
        sprite.setTextureRect(IntRect(42*int(en->currFrame), 183, 40, 58));
    if(en->dy > 0)
        sprite.setTextureRect(IntRect(42*int(en->currFrame), 0, 40, 58));

    sprite.setPosition(en->rect.left, en->rect.top);
    //en->dx = en->dy = 0;
}
void react1(Enemy * en){
    int tmp = rand()%4;
    switch(tmp){
        case 0:en->dy = 0;
            en->dx = 0.1;
            break;
        case 1:en->dy = 0;
            en->dx = -0.1;
            break;
        case 2:en->dx = 0;
            en->dy = -0.1;
            break;
        case 3:en->dx = 0;
            en->dy = 0.1;
            break;
    }
}
void react2(Enemy * en){
    if(en->dx > 0){
        en->dy = 0;
        en->dx = 0.1;
    }
    else if(en->dx < 0){
        en->dy = 0;
        en->dx = -0.1;
    }
    else if(en->dy > 0){
        en->dx = 0;
        en->dy = -0.1;
    }
    else if(en->dy < 0){
        en->dx = 0;
        en->dy = 0.1;
    }
}
void en_colisionX(Enemy * en){
    for(int i = (en->rect.top-34)/46; i < (en->rect.top+en->rect.height-68)/46; i++){
        for (int j = (en->rect.left+7)/46; j < (en->rect.left+en->rect.width-7)/46; j++){
            if(en->mup[i][j] == 1 || en->mup[i][j] == 2){
                if(en->dx > 0){
                    en->rect.left = j*46-30;
                    en->react(en);
                    break;
                }
                if(en->dx < 0){
                    en->rect.left = j*46+39;
                    en->react(en);
                    break;
                }
            }
        }
    }
}
void en_colisionY(Enemy * en){
    for(int i = (en->rect.top-34)/46; i < (en->rect.top+en->rect.height-68)/46; i++){
        for (int j = (en->rect.left+7)/46; j < (en->rect.left+en->rect.width-7)/46; j++){
            if(en->mup[i][j] == 1 || en->mup[i][j] ==2){
                if(en->dy > 0){
                    en->rect.top = i*46+11;
                    en->react(en);
                    break;
                }
                if(en->dy < 0){
                    en->rect.top = i*46+80;
                    en->react(en);
                    break;
                }
            }
        }
    }
}

int en_getRect(Enemy * en, char c){
    switch(c){
        case 'l': return en->rect.left;
        case 'w': return en->rect.width;
        case 'h': return en->rect.height;
        case 't': return en->rect.top;
        default : return 0;
    }
}
/*int en_getMaxNumBoomb(Enemy * en){
    return en->max_num_boomb;
}*/
void en_left(Enemy * en){
    en->dx = -en->speed;
}
void en_right(Enemy * en){
    en->dx = en->speed;
}
void en_up(Enemy * en){
    en->dy = -en->speed;
}
void en_down(Enemy * en){
    en->dy = en->speed;
}
void free_enemy(Enemy * en){
    free(en);
}
