#include "Lavel.h"
#include <cstdlib>
#include <string.h>
//#include <loadMap.h>
#include "Boomb.h"

struct lavel_s{
    int mup[13][15];
    Player * player;
    int cur_num_boomb;
    b_list * bomb;
    Enemy * enemy;
    int long_b;
};
struct lvl_list{
    Lavel lvl[15];
};
int readFile(char * name, char text[300]){
    FILE * file;
    file = fopen(name, "r");
    if(NULL == file)
        return 1;
    char str[17] = "";
    //char text[305] = "";
    while(fgets(str, 17, file)){
        strcat(text, str);
    }
    return 0;
}
lvl_list * new_lvlList(){
    lvl_list * l_l = (lvl_list*)malloc(sizeof(lvl_list));
    for(int i = 0; i < 15; i++){
        char name[15] = "";
        sprintf(name, "map%i.txt", i+1);
        char mup[300] = "";
        if(!readFile(name, mup)){
            for(int j = 0; j < 13; j++){
                for(int k = 0; k < 15; k++){
                    switch(mup[j*16+k]){
                        case '0': l_l->lvl[i].mup[j][k] = 0;
                       // printf("%i, %i: %i \n", j, k, l_l->lvl->mup[j][k]);
                            break;
                        case '1': l_l->lvl[i].mup[j][k] = 1;
                        //printf("%i, %i: %i \n", j, k, l_l->lvl->mup[j][k]);
                            break;
                        case '2': l_l->lvl[i].mup[j][k] = 2;
                        //printf("%i, %i: %i \n", j, k, l_l->lvl->mup[j][k]);
                            break;
                        case '3': l_l->lvl[i].mup[j][k] = 3;
                        //printf("%i, %i: %i \n", j, k, l_l->lvl->mup[j][k]);
                            break;
                        case '4': l_l->lvl[i].mup[j][k] = 4;
                            break;
                        case '5': l_l->lvl[i].mup[j][k] = 5;
                            break;
                        case '\n': printf("\\n");
                    }
                }
            }
        }
        else {
            continue;
        }
        l_l->lvl[i].enemy = new_enemy(l_l->lvl[i].mup);
        en_cb_react(l_l->lvl[i].enemy, react1);
        l_l->lvl[i].player = new_player(l_l->lvl[i].mup);
        l_l->lvl[i].cur_num_boomb = 0;
        l_l->lvl[i].long_b = 2;
        l_l->lvl[i].bomb = new_bList(pl_getMaxTimeBoomb(l_l->lvl[i].player));
    }
    return l_l;
}
Lavel * l_load(lvl_list * llist, int i){
    Lavel * l_l = (Lavel*)malloc(sizeof(Lavel));
    //for(int i = 0; i < 15; i++){
        char name[15] = "";
        sprintf(name, "map%i.txt", i+1);
        char mup[300] = "";
        if(!readFile(name, mup)){
            for(int j = 0; j < 13; j++){
                for(int k = 0; k < 15; k++){
                    switch(mup[j*16+k]){
                        case '0': l_l->mup[j][k] = 0;
                       // printf("%i, %i: %i \n", j, k, l_l->lvl->mup[j][k]);
                            break;
                        case '1': l_l->mup[j][k] = 1;
                        //printf("%i, %i: %i \n", j, k, l_l->lvl->mup[j][k]);
                            break;
                        case '2': l_l->mup[j][k] = 2;
                        //printf("%i, %i: %i \n", j, k, l_l->lvl->mup[j][k]);
                            break;
                        case '3': l_l->mup[j][k] = 3;
                        //printf("%i, %i: %i \n", j, k, l_l->lvl->mup[j][k]);
                            break;
                        case '4': l_l->mup[j][k] = 4;
                            break;
                        case '5': l_l->mup[j][k] = 5;
                            break;
                        case '\n': printf("\\n");
                    }
                }
            }
        }
        else
            return NULL;
        l_l->enemy = new_enemy(l_l->mup);
        en_cb_react(l_l->enemy, react1);
        l_l->player = new_player(l_l->mup);
        l_l->cur_num_boomb = 0;
        l_l->long_b = 2;
        l_l->bomb = new_bList(pl_getMaxTimeBoomb(l_l->player));

    llist->lvl[i] = *l_l;
    return l_l;
}
Lavel * lavel_get(lvl_list * l_l, int num){
    return (Lavel *)&l_l->lvl[num];
}
Lavel * new_lavel(int num){
    Lavel * l = (Lavel *)malloc(sizeof(Lavel));
    int tmp;
    for(int i = 0; i < 13; i++){
        for (int j = 0; j < 15; j++){
            tmp = rand()%3;
            if(i == 0 || j == 0 || i == 12 || j == 14 ||
               (i%2 == 0 && j%2 == 0)){
                l->mup[i][j] = STENA;
            }
            else if(tmp == 2 && i+j > 3)
                l->mup[i][j] = KUST;
            else
                l->mup[i][j] = 0;
        }
    }
    //char * name = map_getlvl(num);
    l->enemy = new_enemy(l->mup);
    en_cb_react(l->enemy, react2);
    l->player = new_player(l->mup);
    l->cur_num_boomb = 0;
    return l;
}

int lavel_proc(Lavel * l, RenderWindow & win, char * namePers){
    Font font;
    font.loadFromFile("GoodDog.otf");
    Text text("text", font);
    text.setString("You Die");


    Texture t_personazh, t_fon, t_kamen, t_kust, t_boomb, t_e1, t_e2, t_e3;
    t_e1.loadFromFile("Blondy.png");
    t_e2.loadFromFile("Enemy1.png");
    t_e3.loadFromFile("Enemy2.png");
    t_boomb.loadFromFile("Bomb.png");
	t_personazh.loadFromFile(namePers);
	t_fon.loadFromFile("fon.png");
	t_kamen.loadFromFile("statuya2.png");
	t_kust.loadFromFile("Kust.png");
	Sprite s_p, s_fon, s_kamen, s_kust, s_boomb, s_e1, s_e2, s_e3;
	s_e1.setTexture(t_e1);
	s_e1.setPosition(400, 500);
	s_e2.setTexture(t_e2);
	s_e3.setTexture(t_e3);
	s_boomb.setTexture(t_boomb);
	s_boomb.setTextureRect(IntRect(0, 0, 40, 48));
	s_kust.setTexture(t_kust);
	s_kamen.setTexture(t_kamen);
	s_fon.setTexture(t_fon);
	s_p.setTexture(t_personazh);
	s_p.setTextureRect(IntRect(0, 0, 40, 58));

    Clock clock;

    while (win.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)){
                win.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            pl_left(l->player);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Right)){
            pl_right(l->player);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Up)){
            pl_up(l->player);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Down)){
            pl_down(l->player);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Space)){
            l_addBoomb(l, (pl_getRect(l->player, 't')-34)/46, (pl_getRect(l->player, 'l')+15)/46);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Escape)){
            return 106;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Return)){
            return 107;
        }
        pl_update(l->player, s_p, time);
        if(en_update(l->enemy, s_e1, time, (pl_getRect(l->player, 't')-34)/46, (pl_getRect(l->player, 'l')+15)/46) == 102)
            return 102;
        win.clear();
        win.draw(s_fon);
        for(int i = 0; i < l->cur_num_boomb; i++){
            printf("%i Process..\n", i);
            if(!isNULL(l->bomb, i)){
                printf("NOT NULL %i\n", i);
                if(b_update(b_get(l->bomb, i), s_boomb, time)){
                    printf("Explision..\n");
                    int x = b_getX(l->bomb, i), y = b_getY(l->bomb, i);
                    printf("\n====\n%i, %i\n====\n", x, y);
                    l_delBoomb(l, x, y);
                    s_boomb.setTextureRect(IntRect(0, 0, 40, 48));

                    if(pl_explosion(l->player, x,y))
                        return 102;
                    if(en_explosion(l->enemy, l->long_b, x, y))
                        return 107;
                    b_del(l->bomb);
                }
                //s_boomb.setPosition(b_getY(l->bomb, i)*46, b_getX(l->bomb, i)*46+68);
                //win.draw(s_boomb);
            }
        }



        int tmp, count = 0;;
        for(int i = 0; i < 13; i++){
            for (int j = 0; j < 15; j++){
                tmp = l_get(l, i, j);
                if(tmp == STENA){
                    s_kamen.setPosition(j*46, i*46+68);
                    win.draw(s_kamen);
                }
                else if(tmp == KUST){
                    count = 1;
                    s_kust.setPosition(j*46, i*46+68);
                    win.draw(s_kust);
                }
                else if(tmp == BOOMB){
                    s_boomb.setPosition(j*46, i*46+68);
                    win.draw(s_boomb);
                }
            }
        }
        if(count == 0)
            return 107;
        win.draw(s_p);
        win.draw(s_e1);
        win.draw(text);
        win.display();
    }
    return 103;
}
void l_addBoomb(Lavel * l, int x, int y){
    if(pl_getMaxNumBoomb(l->player) > l->cur_num_boomb && l->mup[x][y] == 0){
        printf("Add..\n=====\n");
        l->mup[x][y] = BOOMB;
        l->cur_num_boomb++;
        printf("Num boomb: %i\n", l->cur_num_boomb);
        pl_addBoomb(l->player, x, y);
        en_addBoomb(l->enemy, x, y);    //
        b_addBoomb(l->bomb, x, y);      //
    }
}
void l_delBoomb(Lavel * l, int x, int y){
    l->mup[x][y] = 0;
    l->cur_num_boomb--;
    //left
    for(int i = 1; i < l->long_b; i++){
        if(l->mup[x+i][y] == 1)
            break;
        if(l->mup[x+i][y] == 2){
            l->mup[x+i][y] = 0;
            break;
        }
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
    }
    //up
    for(int i = 1; i < l->long_b; i++){
        if(l->mup[x][y-i] == 1)
            break;
        if(l->mup[x][y-i] == 2){
            l->mup[x][y-i] = 0;
            break;
        }

    }
    //down
    for(int i = 1; i < l->long_b; i++){
        if(l->mup[x][y+i] == 1)
            break;

        if(l->mup[x][y+i] == 2){
            l->mup[x][y+i] = 0;
            break;
        }

    }
}
void l_clear(Lavel * l, int x, int y){
    l->mup[x][y] = 0;
}
int l_get(Lavel * l, int x, int y){
    return l->mup[x][y];
}
Player * l_getPlayer(Lavel * l){
    return l->player;
}
