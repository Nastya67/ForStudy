#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Lavel.h"
#include "Game.h"
#include <loadMap.h>

using namespace sf;

int main(){
    RenderWindow win(VideoMode(689, 700), "Krevetochka");
    win.setPosition(Vector2i(0, 0));
    Game * game = new_game();
    Music music;
    music.openFromFile("mus_game.ogg");
    //music.setVolume(3);
    music.play();
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
    return 0;
}
