
#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    RenderWindow win(VideoMode(500, 500), "Krevetochka");

    float curr_frame = 0;

    Texture t_personazh;
	t_personazh.loadFromFile("textura2.png");

    Sprite s_personazh;
    s_personazh.setTexture(t_personazh);
    s_personazh.setTextureRect(IntRect(30, 0, 30, 31));
    s_personazh.setPosition(20, 10);

    while (win.isOpen()){
        Event event;
        while (win.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                win.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            s_personazh.move(-0.1, 0);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Right)){
            s_personazh.move(0.1, 0);

        }
        else if(Keyboard::isKeyPressed(Keyboard::Up)){
            s_personazh.move(0, -0.1);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Down)){
            s_personazh.move(0, 0.1);
        }

        win.clear();
        win.draw(s_personazh);
        win.display();
    }

    return 0;
}
