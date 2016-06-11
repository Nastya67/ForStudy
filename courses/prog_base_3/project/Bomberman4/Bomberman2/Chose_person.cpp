#include "Chose_person.h"
#include "Game.h"
#include "Lavel.h"
#include "Player.h"
#include <windows.h>
#include <string>

int chose_proc(RenderWindow & win, Game * game){
    const int num = 4;
    //int status[num] = {}
    char personazh[num][25] = {"Blondy.png", "bluepink1_2.png", "wizzard.png", "blondpresident.png"};
    Image i_pod;
    i_pod.loadFromFile("podsvet.png");
    i_pod.createMaskFromColor(Color::White);
    Texture t_perconach[num], t_fon, t_pod;
    t_pod.loadFromImage(i_pod);
    t_fon.loadFromFile("menu.png");
    Sprite s_person[num], s_fon, s_pod;
    s_pod.setTexture(t_pod);
    s_fon.setTexture(t_fon);
    for(int i = 0; i < num; i++){
        t_perconach[i].loadFromFile(personazh[i]);
        s_person[i].setTexture(t_perconach[i]);
        s_person[i].setTextureRect(IntRect(0, 0, 40, 55));
        s_person[i].setPosition(i*100+170, 350);
    }
    Font font;
    font.loadFromFile("GoodDog.otf");
    Color pink(255, 0, 128);
    Color blue(63, 200, 210);
    Text text("Select your hero", font);
    text.setCharacterSize(90);
    text.setPosition(130, 220);
    text.setColor(pink);
    bool IsKeyPressedOneTime = false;
    int cur = 0;
    while (win.isOpen()){
        Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)){
                win.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Right) && !IsKeyPressedOneTime){
            IsKeyPressedOneTime = true;
            if(cur < num-1)
                cur++;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Left) && !IsKeyPressedOneTime){
            IsKeyPressedOneTime = true;
            if(cur > 0)
                cur--;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Return)){
            game_addSpritePerson(game, (char*)personazh[cur]);
            game_addNamePerson(game, (char*)"Player1");
            break;
        }
        else if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
            return MAIN_MENU;
        }

        s_pod.setPosition(cur*100+163, 390);
        win.clear();
        win.draw(s_fon);
        win.draw(s_pod);
        win.draw(text);
        for(int i = 0; i < num; i++)
            win.draw(s_person[i]);
        win.display();
        Sleep(100);
        IsKeyPressedOneTime = false;
    }
    return LAVEL_MAP;
}
