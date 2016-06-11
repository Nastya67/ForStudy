#include "Lavel.h"
#include <cstdlib>
//#include "Player.h"

struct lavel_s{
    int mup[13][15];
    Player * player;
    //Sprite * sprite;
};
Lavel * new_lavel(){
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
    l->player = new_player();
    return l;
}
/*void l_initPlayer(Lavel * l, Sprite * sprite){
    l->sprite = sprite;
}*/
int lavel_proc(Lavel * l, RenderWindow & win, char * namePers){
    Font font;
    font.loadFromFile("GoodDog.otf");
    Text text("text", font);
    text.setString("You Die");


    Texture t_personazh, t_fon, t_kamen, t_kust, t_boomb;
    t_boomb.loadFromFile("Destroy1.png");
	t_personazh.loadFromFile(namePers);
	t_fon.loadFromFile("fon.png");
	t_kamen.loadFromFile("statuya2.png");
	t_kust.loadFromFile("Kust.png");
	Sprite s_p, s_fon, s_kamen, s_kust, s_boomb;
	s_boomb.setTexture(t_boomb);
	s_kust.setTexture(t_kust);
	s_kamen.setTexture(t_kamen);
	s_fon.setTexture(t_fon);
	s_p.setTexture(t_personazh);
	s_p.setTextureRect(IntRect(0, 0, 40, 58));

    Clock clock;

    //Lavel * lavel1 = new_lavel();
    //Player * player1 = new_player(lavel1);

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
            //pl.addBoomb(t_boomb);
        }
        pl_update(l->player, s_p, time);

        win.clear();
        win.draw(s_fon);
        int tmp;
        for(int i = 0; i < 13; i++){
            for (int j = 0; j < 15; j++){
                tmp = l_get(l, i, j);
                if(tmp == STENA){
                    s_kamen.setPosition(j*46, i*46+68);
                    win.draw(s_kamen);
                }
                else if(tmp == KUST){
                    s_kust.setPosition(j*46, i*46+68);
                    win.draw(s_kust);
                }
            }
        }

        win.draw(s_p);
        win.draw(text);
        win.display();
    }
    return 103;
}
void l_addBoomb(Lavel * l, int x, int y){
    l->mup[x][y] = BOOMB;
}
void l_clear(Lavel * l, int x, int y){
    l->mup[x][y] = 0;
}
int l_get(Lavel * l, int x, int y){
    return l->mup[x][y];
}
