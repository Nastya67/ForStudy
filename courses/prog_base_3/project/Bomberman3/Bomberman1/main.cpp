
#include <SFML/Graphics.hpp>
#include <valarray>

#define MAX_CURR_FRAME 4
#define STENA 1
#define KUST 2
#define BOOMB 3

using namespace sf;
int carta[13][15];
class Player;
class Boomb{
    public:
    int time_max;
    float cur_time;
    int cur_frame;
    Sprite sprite;
    int i, j;
    Player * pl;

    Boomb(){}
    Boomb(Player * pl, Texture &image, int time, int ii, int jj){
        sprite.setTexture(image);
        time_max = time;
        cur_time = 0;
        cur_frame = 0;
        i = ii;
        j = jj;
        carta[i][j] = 3;
    }
    bool update(float time){
        cur_time += 0.0035*time;
        //printf("%i\n", cur_time);
        if(cur_time >= time_max)
            return explo();
        sprite.setTextureRect(IntRect(4*int(cur_frame), 0, 40, 46));
        return false;
    }
    bool explo(){
        if(cur_frame < MAX_CURR_FRAME){
            cur_frame++;
            return false;
        }
        else{
            cur_frame = 0;
            carta[i][j] = 0;
            return true;
        }
    }


};

class Player{
public:
    float dx, dy;
    FloatRect rect;
    Sprite sprite;
    float currFrame;
    int max_num_boomb;
    int cur_num_boomb;
    Boomb boomb[15];
    int time_boomb;
    bool life;


    Player(Texture &image){
        sprite.setTexture(image);
        rect = FloatRect(46, 100, 37, 57);
        time_boomb = 10;
        dx = dy = 0;
        currFrame = 0;
        max_num_boomb = 2;
        cur_num_boomb = 0;
        life = true;
        //boomb = new Boomb[10];
    }
    void exp(){
        for(int i = 0; i < max_num_boomb-1; i++){
            boomb[i] = boomb[i+1];
        }

        cur_num_boomb--;
    }
    void addBoomb(Texture &image){
        int i = (rect.top-34)/46;
        int j = (rect.left+7)/46;
        if(cur_num_boomb < max_num_boomb && carta[i][j] != BOOMB){
            printf("ok\n");
            Boomb b(this, image, time_boomb, i, j);
            boomb[cur_num_boomb] = b;
            cur_num_boomb++;
            //carta[][] = 3;
        }
    }

    void update(float time){
        rect.left += dx*time;
        colisionX();
        rect.top += dy*time;
        colisionY();

        currFrame += 0.01*time;
        if(currFrame > MAX_CURR_FRAME)
            currFrame -= MAX_CURR_FRAME;

        if(dx < 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 60, 37, 58));
        if(dx > 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 121, 37, 58));
        if(dy < 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 183, 40, 58));
        if(dy > 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 0, 40, 58));

        sprite.setPosition(rect.left, rect.top);
        dx = dy = 0;
        for(int i = 0; i < max_num_boomb; i++){
            if(boomb[i].update(time))
                exp();
        }
    }
    void colisionX(){
        for(int i = (rect.top-34)/46; i < (rect.top+rect.height-68)/46; i++){
            for (int j = (rect.left+7)/46; j < (rect.left+rect.width-7)/46; j++){
                if(carta[i][j] == 1 || carta[i][j] == 2){
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
                if(carta[i][j] == 1 || carta[i][j] ==2){
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
        if(currFrame > MAX_CURR_FRAME)
            currFrame -= MAX_CURR_FRAME;

        if(dx < 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 60, 37, 58));
        if(dx > 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 121, 37, 58));
        if(dy < 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 183, 40, 58));
        if(dy > 0)
            sprite.setTextureRect(IntRect(42*int(currFrame), 0, 40, 58));

        sprite.setPosition(rect.left, rect.top);
    }
    void colisionX(){
        for(int i = (rect.top-34)/46; i < (rect.top+rect.height-68)/46; i++){
            for (int j = (rect.left+7)/46; j < (rect.left+rect.width-7)/46; j++){
                if(carta[i][j] == 1 || carta[i][j] == 2){
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
                if(carta[i][j] == 1 || carta[i][j] == 2){
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
    Image i_p, i_trava;
    i_p.loadFromFile("Blondy.png");
    i_p.createMaskFromColor(Color::White);
    i_trava.loadFromFile("Kust.png");
    i_trava.createMaskFromColor(Color::White);
    Texture t_fon1, t_k, t_trava, t_boomb;
    t_boomb.loadFromFile("k.png");
    t_fon1.loadFromFile("fon.png");
    t_k.loadFromFile("statuya2.png");
    t_trava.loadFromImage(i_trava);
    Sprite s_fon1, s_k, s_trava, s_boomb;
    s_fon1.setTexture(t_fon1);
    s_boomb.setTexture(t_boomb);
    s_k.setTexture(t_k);
    s_trava.setTexture(t_trava);
    Texture t_personazh;
	t_personazh.loadFromImage(i_p);
    //t_personazh.loadFromFile("XPspites1.png");

    Player pl(t_personazh);
    pl.sprite.setTextureRect(IntRect(0, 0, 40, 59));

    Enemy en1(t_personazh, 400, 546, 0.1, 0);
    en1.sprite.setTextureRect(IntRect(0, 0, 40, 59));
    int tmp;
    Clock clock;
    for(int i = 0; i < 13; i++){
        for (int j = 0; j < 15; j++){
            tmp = rand()%3;
            if(i == 0 || j == 0 || i == 12 || j == 14 ||
               (i%2 == 0 && j%2 == 0)){
                carta[i][j] = STENA;
            }
            else if(tmp == 2)
                carta[i][j] = KUST;
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
        else if(Keyboard::isKeyPressed(Keyboard::Space)){
            pl.addBoomb(t_boomb);
        }
        pl.update(time);
        en1.update(time);

        win.clear();
        win.draw(s_fon1);
        for(int i = 0; i < 13; i++){
            for (int j = 0; j < 15; j++){
                if(carta[i][j] == STENA){
                    s_k.setPosition(j*46, i*46+68);
                    win.draw(s_k);
                }
                else if(carta[i][j] == KUST){
                    s_trava.setPosition(j*46, i*46+68);
                    win.draw(s_trava);
                }
                else if(carta[i][j] == BOOMB){
                    s_boomb.setPosition(j*46, i*46+68);
                    win.draw(s_boomb);
                }
            }
        }

        //win.draw(s_fon1);
        win.draw(pl.sprite);
        win.draw(en1.sprite);
        if(!pl.life){
            win.draw(text);
            break;
        }
        win.display();
    }

    return 0;
}
