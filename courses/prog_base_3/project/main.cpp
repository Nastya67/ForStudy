
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow win(sf::VideoMode(300, 300), "Krevetochka", sf::Style::Fullscreen);
    //sf::CircleShape shape(100.f);
   // shape.setFillColor(sf::Color::Green);
    sf::Image helik;
    helik.loadFromFile("Imege/Helik.png");

    sf::Texture helik_texture;
	helik_texture.loadFromImage(helik);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
        }

        win.clear();
        win.draw(helik_texture);
        win.display();
    }

    return 0;
}
