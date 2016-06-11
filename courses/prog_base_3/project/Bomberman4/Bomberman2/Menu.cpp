#include "Menu.h"
#include "Game.h"
#include <windows.h>

int menu_proc(RenderWindow & win){
    int status[3] = {CHOSE_PERSON, LOAD_SAVE_GAME, EXIT};
    Texture t_fon;
    t_fon.loadFromFile("Labelmenu1.png");
    Sprite s_fon;
    s_fon.setTexture(t_fon);
    Font font;
    font.loadFromFile("GoodDog.otf");
    //Text text("text", font);
    char text[3][15] = {"New Game", "Load Game", "Exit"};
    Text t[3];
    Color pink(254, 137, 245);
    Color yellow(255, 214, 136);
    for(int i = 0; i < 3; i++){
        t[i].setString(text[i]);
        t[i].setFont(font);
        t[i].setCharacterSize(100);
        t[i].setPosition(190, i*90+160);
        t[i].setColor(pink);
    }

    int cur = 0;
    t[cur].setColor(yellow);
    bool IsKeyPressedOneTime = false;


    while (win.isOpen()){
        Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)){
                win.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Down) && !IsKeyPressedOneTime){
            IsKeyPressedOneTime = true;
            t[cur].setColor(pink);
            if(cur < 2)
                cur++;
            t[cur].setColor(yellow);

        }
        else if(Keyboard::isKeyPressed(Keyboard::Up) && !IsKeyPressedOneTime){
            IsKeyPressedOneTime = true;
            t[cur].setColor(pink);
            if(cur > 0)
                cur--;
            t[cur].setColor(yellow);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Return)){
            break;
        }
        win.clear();
        win.draw(s_fon);

        for(int i = 0; i < 3; i++)
            win.draw(t[i]);
        win.display();
        Sleep(100);
        IsKeyPressedOneTime = false;
    }
    return status[cur];
}
