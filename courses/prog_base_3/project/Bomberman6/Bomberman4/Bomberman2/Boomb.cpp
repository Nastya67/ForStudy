#include "Boomb.h"
#include <cstdlib>

//#include <SFML/Graphics.hpp>

struct boomb_s{
    float cur_time;
    float max_time;
    float cur_frame;
    int x, y;
};
struct b_list{
    Boomb bomb[15];
    int cur_num;
};
b_list * new_bList(float time){
    b_list * b = (b_list*)malloc(sizeof(b_list));
    for(int i = 0; i < 15; i++){
        b->bomb[i].x = 0;
        b->bomb[i].y = 0;
        b->bomb[i].cur_frame = 0;
        b->bomb[i].max_time = time;
        b->bomb[i].cur_time = 0;
    }
    b->cur_num = 0;
    return b;
}
Boomb * b_get(b_list * b, int i){
    return &b->bomb[i];
}
bool isNULL(b_list * b, int i){
    if(b->bomb[i].x == 0 && b->bomb[i].y == 0 && b->bomb[i].cur_time == 0)
        return true;
    return false;
}
void b_addBoomb(b_list * b, int x, int y){
    printf("Save %i boomb: %i, %i\n", b->cur_num, x, y);
    b->bomb[b->cur_num].x = x;
    b->bomb[b->cur_num].y = y;
    b->bomb[b->cur_num].cur_time = 0;
    b->cur_num++;

}
Boomb * new_boomb(float time, int x, int y){
    Boomb * b = (Boomb * )malloc(sizeof(Boomb));
    b->cur_time = 0;
    b->max_time = time;
    b->cur_frame = 0;
    b->x = x;
    b->y = y;
    return b;
}
bool b_update(Boomb * b, Sprite & sprite, float time){
    b->cur_time += 0.0035*time;
    if(b->cur_time >= b->max_time)
        return b_exlosion(b, sprite);
    return false;
}
bool b_exlosion(Boomb * b, Sprite & sprite){
    if(b->cur_frame < MAX_CURR_FRAME){
        sprite.setTextureRect(IntRect(40*int(b->cur_frame), 0, 40, 46));
        b->cur_frame += rand()%2;
        return false;
    }
    else{
        b->cur_frame = 0;
       // b->x = 0;
       // b->y = 0;
        return true;
    }
}
void b_del(b_list * b){
    /*for(int i = 0; i < 14; i++){
        if(isNULL(b, i+1))
            break;
        b->bomb[i].x = b->bomb[i+1].x;
        b->bomb[i].y = b->bomb[i+1].y;
        b->bomb[i].cur_frame = b->bomb[i+1].cur_frame;
        b->bomb[i].cur_time = b->bomb[i+1].cur_time;
    }
    b->bomb[15].x = 0;
    b->bomb[15].y = 0;
    b->bomb[15].cur_frame = 0;
    b->bomb[15].cur_time = 0;*/
    b->bomb[b->cur_num].x = 0;
    b->bomb[b->cur_num].y = 0;
    b->bomb[b->cur_num].cur_frame = 0;
    b->bomb[b->cur_num].cur_time = 0;
    b->cur_num--;
}
void free_boomb(Boomb * b){
    free(b);
}
int b_getX(b_list * b, int i){
    return b->bomb[0].x;
}
int b_getY(b_list * b, int i){
    return b->bomb[0].y;
}
