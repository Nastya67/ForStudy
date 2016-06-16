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
    //en->rect = FloatRect(46, 100, 37, 57);
    en->rect = FloatRect(400, 500, 37, 57);
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
void en_addBoomb(Enemy * en, int x, int y){
    printf("Enemy save boomb: %i, %i\n", x, y);
    en->mup[x][y] = 3;
}

int en_update(Enemy * en, Sprite & sprite, float time, int x, int y){
    en->rect.left += en->dx*time;
    if(en_colisionX(en, x, y) == 102)
        return 102;
    en->rect.top += en->dy*time;
    if(en_colisionY(en, x, y) == 102)
        return 102;

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
    return 0;
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
int en_colisionX(Enemy * en, int x, int y){
    for(int i = (en->rect.top-34)/46; i < (en->rect.top+en->rect.height-68)/46; i++){
        for (int j = (en->rect.left+7)/46; j < (en->rect.left+en->rect.width-7)/46; j++){
            if(i == x, j == y)
                return 102;
            if(en->mup[i][j] == 1 || en->mup[i][j] == 2 || en->mup[i][j] == 3){
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
    return 0;
}
int  en_colisionY(Enemy * en, int x, int y){
    for(int i = (en->rect.top-34)/46; i < (en->rect.top+en->rect.height-68)/46; i++){
        for (int j = (en->rect.left+7)/46; j < (en->rect.left+en->rect.width-7)/46; j++){
            if(en->mup[i][j] == 1 || en->mup[i][j] ==2 || en->mup[i][j] == 3){
                if(i == x, j == y)
                    return 102;
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
    return 0;
}
int en_explosion(Enemy * l, int n, int x, int y){
    l->mup[x][y] = 0;
    for(int i = 1; i < n; i++){
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
    for(int i = 1; i < n; i++){
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
    for(int i = 1; i < n; i++){
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
    for(int i = 1; i < n; i++){
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
