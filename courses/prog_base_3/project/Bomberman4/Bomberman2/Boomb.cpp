#include "Boomb.h"

struct boomb_s{
    float cur_time;
    float max_time;
    float cur_frame;
    int x, y;
};
Boomb * new_boomb(float time, int x, int y){
    Boomb * b = (Boomb * )malloc(sizeof(Boomb));
    b->cur_time = 0;
    b->max_time = time;
    b->cur_frame = 0;
    b->x = x;
    b->y = y;
    return b;
}
bool b_update(Boomb * b, float time){
    b->cur_time += 0.0035*time;
    if(b->cur_time >= b->max_time)
        return b_exlosion(b);
    return false;
}
bool b_exlosion(Boomb * b){
    if(b->cur_frame < MAX_CURR_FRAME){
        //s_boomb.setTextureRect(IntRect(46*int(b->cur_frame), 0, 40, 46));
        b->cur_frame++;
        return false;
    }
    else{
        b->cur_frame = 0;
        //Cmap.map[i][j] = 0;
        return true;
    }
}
void free_boomb(Boomb * b){
    free(b);
}
