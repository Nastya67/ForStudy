#include "Lavel_map.h"
#include <windows.h>

int lavelMap_proc(Game * game, RenderWindow & win){
    const int num = 4;
    int pos[num][2] = {{250, 567}, {305, 535}, {358, 505}, {408, 474}};

    Image i_pod;
    i_pod.loadFromFile("podsvet.png");
    i_pod.createMaskFromColor(Color::White);
    Texture t_fon, t_pod, t_p;
    t_p.loadFromFile(game_getNameSprite(game));
    t_pod.loadFromImage(i_pod);
    t_fon.loadFromFile("lavel_map.png");
    Sprite s_fon, s_pod, s_p;
    s_p.setTexture(t_p);
    s_p.setTextureRect(IntRect(40, 0, 40, 55));
    s_pod.setTexture(t_pod);
    s_fon.setTexture(t_fon);
    Font font;
    font.loadFromFile("GoodDog.otf");
    Color pink(255, 0, 128);
    Color blue(63, 200, 210);
    Text text("Lavel map", font);
    text.setCharacterSize(90);
    text.setPosition(200, 0);
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
            game_setCurLavel(game, 0);
            break;
        }
        else if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
            return MAIN_MENU;
        }
        s_p.setPosition(pos[cur][0]+7, pos[cur][1]-38);
        s_pod.setPosition(pos[cur][0], pos[cur][1]);
        win.clear();
        win.draw(s_fon);
        win.draw(s_pod);
        win.draw(text);
        win.draw(s_p);
        win.display();
        Sleep(100);
        IsKeyPressedOneTime = false;
    }
    return LAVEL;

}
