
#include <SFML/Graphics.hpp>
using namespace sf;
int carta[13][15];
class Player{
public:
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currFrame;

    Player(Texture &image){
        sprite.setTexture(image);
        rect = FloatRect(46, 100, 37, 57);

        dx = dy = 0;
        currFrame = 0;
    }
    void update(float time){
        rect.left += dx*time;
        colisionX();
        rect.top += dy*time;
        colisionY();

        currFrame += 0.005*time;
        if(currFrame > 4)
            currFrame -= 4;

        if(dx < 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 64, 37, 58));
        if(dx > 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 128, 37, 58));
        if(dy < 0)
            sprite.setTextureRect(IntRect(42*int(currFrame)+2, 190, 40, 58));
        if(dy > 0)
            sprite.setTextureRect(IntRect(42*int(currFrame)+2, 0, 40, 58));

        sprite.setPosition(rect.left, rect.top);
        dx = dy = 0;
    }
    void colisionX(){
        for(int i = (rect.top-34)/46; i < (rect.top+rect.height-68)/46; i++){
            for (int j = (rect.left+7)/46; j < (rect.left+rect.width-7)/46; j++){
                if(carta[i][j] == 1){
                    if(dx > 0)
                        rect.left = j*46-30;
                    if(dx < 0)
                        rect.left = j*46+39;
                }
            }
        }
    }
    void colisionY(){
        for(int i = (rect.top-34)/46; i < (rect.top+rect.height-68)/46; i++){
            for (int j = (rect.left+7)/46; j < (rect.left+rect.width-7)/46; j++){
                if(carta[i][j] == 1){
                    if(dy > 0)
                        rect.top = i*46+11;
                    if(dy < 0)
                        rect.top = i*46+80;
                }
            }
        }
    }
};
class Enemy{
public:
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currFrame;
    bool life;
    //float speedX, speedY;

Enemy(Texture &image, int x, int y, float sx, float sy){
        sprite.setTexture(image);
        rect = FloatRect(x, y, 37, 57);

        dx = sx;
        dy = sy;
        currFrame = 0;
        life = true;
    }
    void update(float time){
        rect.left += dx*time;
        colisionX();
        rect.top += dy*time;
        colisionY();

        currFrame += 0.005*time;
        if(currFrame > 4)
            currFrame -= 4;

        if(dx < 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 64, 37, 58));
        if(dx > 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 128, 37, 58));
        if(dy < 0)
            sprite.setTextureRect(IntRect(42*int(currFrame)+2, 190, 40, 58));
        if(dy > 0)
            sprite.setTextureRect(IntRect(42*int(currFrame)+2, 0, 40, 58));

        sprite.setPosition(rect.left, rect.top);
    }
    void colisionX(){
        for(int i = (rect.top-34)/46; i < (rect.top+rect.height-68)/46; i++){
            for (int j = (rect.left+7)/46; j < (rect.left+rect.width-7)/46; j++){
                if(carta[i][j] == 1){
                    if(dx > 0){
                        rect.left = j*46-30;
                        dx = -0.1;
                        break;
                    }
                    if(dx < 0){
                        rect.left = j*46+39;
                        dx = 0.1;
                        break;
                    }
                }
            }
        }
    }
    void colisionY(){
        for(int i = (rect.top-34)/46; i < (rect.top+rect.height-68)/46; i++){
            for (int j = (rect.left+7)/46; j < (rect.left+rect.width-7)/46; j++){
                if(carta[i][j] == 1){
                    if(dy > 0)
                        rect.top = i*46+11;
                    if(dy < 0)
                        rect.top = i*46+80;
                }
            }
        }
    }
};


int main()
{
    RenderWindow win(VideoMode(689, 700), "Krevetochka");
    Font font;
    font.loadFromFile("GoodDog.otf");
    Text text("text", font);
    text.setString("You Die");

    float speed = 0.15;
    Image i_p;
    i_p.loadFromFile("PinkyBlond1.png");
    i_p.createMaskFromColor(Color::White);
    Texture t_fon1, t_k;
    t_fon1.loadFromFile("fon.png");
    t_k.loadFromFile("k.png");
    Sprite s_fon1, s_k;
    s_fon1.setTexture(t_fon1);
    s_k.setTexture(t_k);
    Texture t_personazh;
	t_personazh.loadFromImage(i_p);
    //t_personazh.loadFromFile("XPspites1.png");

    Player pl(t_personazh);
    pl.sprite.setTextureRect(IntRect(0, 0, 40, 59));

    Enemy en1(t_personazh, 400, 546, 0.1, 0);
    en1.sprite.setTextureRect(IntRect(0, 0, 40, 59));

    Clock clock;
    for(int i = 0; i < 13; i++){
        for (int j = 0; j < 15; j++){
            if(i == 0 || j == 0 || i == 12 || j == 14 ||
               (i%2 == 0 && j%2 == 0)){
                carta[i][j] = 1;
            }
            else
                carta[i][j] = 0;
        }
    }

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
            pl.dx = -speed;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Right)){
            pl.dx = speed;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Up)){
            pl.dy = -speed;
        }
        else if(Keyboard::isKeyPressed(Keyboard::Down)){
            pl.dy = speed;
        }

        pl.update(time);
        en1.update(time);

        win.clear();
        win.draw(s_fon1);
        for(int i = 0; i < 13; i++){
            for (int j = 0; j < 15; j++){
                if(carta[i][j] == 1){
                    s_k.setPosition(j*46, i*46+68);
                    win.draw(s_k);
                }
            }
        }

        //win.draw(s_fon1);
        win.draw(pl.sprite);
        win.draw(en1.sprite);
        win.draw(text);
        win.display();
    }

    return 0;
}
