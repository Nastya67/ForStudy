#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Lavel.h"
#include "Game.h"

using namespace sf;

int main(){
    RenderWindow win(VideoMode(689, 700), "Krevetochka");
    win.setPosition(Vector2i(0, 0));
    Game * game = new_game();
    while (win.isOpen()){
        Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)){
                win.close();
            }
        }

        if(game_proc(game, win) == EXIT)
            break;
    }
  /*
   Font font;
    font.loadFromFile("GoodDog.otf");
    Text text("text", font);
    text.setString("You Die");


    Texture t_personazh, t_fon, t_kamen, t_kust, t_boomb;
    t_boomb.loadFromFile("Destroy1.png");
	t_personazh.loadFromFile("Blondy.png");
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

    Lavel * lavel1 = new_lavel();
    Player * player1 = new_player(lavel1);

    while (win.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        //printf("%i\n", time);
        Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)){
                win.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            pl_left(player1);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Right)){
            pl_right(player1);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Up)){
            pl_up(player1);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Down)){
            pl_down(player1);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Space)){
            //pl.addBoomb(t_boomb);
        }
        pl_update(player1, s_p, time);

        win.clear();
        win.draw(s_fon);
        int tmp;
        for(int i = 0; i < 13; i++){
            for (int j = 0; j < 15; j++){
                tmp = l_get(lavel1, i, j);
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
    }*/

    return 0;
}
