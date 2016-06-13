#include <stdio.h>
#include <stdlib.h>
#include <Audio.h>

int main(){
    Player * pl = new_player();
    pl_addSound(pl, new_sound("song1", "autor1"));
    printf("status: %i\n", pl_getStatus(pl));
    pl_setStop(pl);
    printf("status: %i\n", pl_getStatus(pl));
    return 0;
}
