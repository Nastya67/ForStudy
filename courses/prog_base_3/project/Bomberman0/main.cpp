
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    RenderWindow win(VideoMode(689, 415), "Krevetochka");

    float curr_frame = 0;
    float speed = 0.07;
    Texture t_fon1;
    t_fon1.loadFromFile("1uroven_1.png");
    Sprite s_fon1;
    s_fon1.setTexture(t_fon1);
    Texture t_personazh;
	t_personazh.loadFromFile("textura2.png");

    Sprite s_personazh;
    s_personazh.setTexture(t_personazh);
    s_personazh.setTextureRect(IntRect(30, 0, 30, 31));
    s_personazh.setPosition(20, 10);

    Clock clock;

    while (win.isOpen()){
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                win.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            s_personazh.move(-speed*time, 0);
            curr_frame += 0.005*time;
            if(curr_frame > 3)
                curr_frame -= 3;
            s_personazh.setTextureRect(IntRect(30*int(curr_frame), 32, 30, 31));

        }
        else if(Keyboard::isKeyPressed(Keyboard::Right)){
            s_personazh.move(speed*time, 0);
            curr_frame += 0.005*time;
            if(curr_frame > 3)
                curr_frame -= 3;
            s_personazh.setTextureRect(IntRect(30*int(curr_frame), 63, 30, 31));
        }
        else if(Keyboard::isKeyPressed(Keyboard::Up)){
            s_personazh.move(0, -speed*time);
            curr_frame += 0.005*time;
            if(curr_frame > 3)
                curr_frame -= 3;
            s_personazh.setTextureRect(IntRect(30*int(curr_frame), 94, 30, 31));
        }
        else if(Keyboard::isKeyPressed(Keyboard::Down)){
            s_personazh.move(0, speed*time);
             curr_frame += 0.005*time;
            if(curr_frame > 3)
                curr_frame -= 3;
            s_personazh.setTextureRect(IntRect(30*int(curr_frame), 0, 30, 31));
        }

        win.clear();
        win.draw(s_fon1);
        win.draw(s_personazh);
        win.display();
    }

    return 0;
}
