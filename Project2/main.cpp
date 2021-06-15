#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> // this is where srand() is defined
#include <ctime>
#include <list>
#include <vector>
#include <sstream>

sf::RenderWindow window;

float speed = 0.1;
float CurrentFrame = 0;
   
void menu(sf::RenderWindow& window) 
{
    sf::Font font;//шрифт 
    font.loadFromFile("20686.ttf");//передаем нашему шрифту файл шрифта
    sf::Text text1("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пиксел€х);//сам объект текст (не строка)
    text1.setFillColor(sf::Color(0, 100, 255));//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
    sf::Text text2("", font, 50);
    text2.setFillColor(sf::Color(0, 100, 255));
    sf::Text text3("", font, 20);
    text3.setFillColor(sf::Color(0, 100, 255));
    sf::Text text4("", font, 20);
    text4.setFillColor(sf::Color(0, 100, 255));

    std::ostringstream playerScoreString;    // объ€вили переменную
    text1.setString("new game");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
    text1.setPosition(100, 30);//задаем позицию текста, отступа€ от центра камеры
    
    text2.setString("exit");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
    text2.setPosition(100, 150);//задаем позицию текста, отступа€ от центра камеры

    text3.setString("rules: collect as many candies");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
    text3.setPosition(300, 150);//задаем позицию текста, отступа€ от центра камеры

    text4.setString("as possible in 10 seconds (max 100)");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
    text4.setPosition(300, 190);//задаем позицию текста, отступа€ от центра камеры

    sf::Texture menuBackground;
    menuBackground.loadFromFile("images/775.png");
    sf::Sprite menuBg(menuBackground);
    bool isMenu = true;
    menuBg.setPosition(0, 0);

    while (isMenu)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window)))
                isMenu = false;//если нажали первую кнопку, то выходим из меню 
            if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window)))
            {
                window.close();
                isMenu = false;
            }
        }

        window.draw(menuBg);
        window.draw(text1);//рисую этот текст
        window.draw(text2);//рисую этот текст
        window.draw(text3);//рисую этот текст
        window.draw(text4);//рисую этот текст
        window.display();
    }
}

class Object 
{
public:
    float x, y, w, h, dx, dy, speed = 0.1;
    int dir = 0;
    bool life;
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Object(sf::String F, int X, int Y, float W, float H) {
        File = F;
        w = W; h = H;
        life = true;
        image.loadFromFile("images/" + File);
        //image.createMaskFromColor(sf::Color(41, 33, 59));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
    }
    sf::FloatRect getRect() {
        return sf::FloatRect(x, y, w, h);
    }
    void update(float time) {
        if (y > 300)
            y = 0;
        y += speed * time;
        sprite.setPosition(x, y);
    }
    //virtual void update(float time) = 0;
};

class Player 
{
public:
    float x, y, w, h, dx, dy, speed = 0;
    int dir = 0, playerScore;
    bool life;
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Player(sf::String F, int X, int Y, float W, float H) 
    {
        playerScore = 0;
        life = true;
        File = F;
        w = W; h = H;
        image.loadFromFile("images/" + File);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
    }

    sf::FloatRect getRect() 
    {
        return sf::FloatRect(x, y, w, h);
    }

    void update(float time) {
        switch (dir)
        {
        case 0: dx = -speed; dy = 0; break;
        case 1: dx = speed; dy = 0; break;
        }
        if (x > 610)
            x = 610;
        else if (x < 0)
            x = 0;
        else
            x += dx * time;

        speed = 0;
        sprite.setPosition(x, y);
    }
};

int main()
{
    sf::Font font;//шрифт 
    font.loadFromFile("20686.ttf");//передаем нашему шрифту файл шрифта
    sf::Text text("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пиксел€х);//сам объект текст (не строка)
    text.setFillColor(sf::Color(0, 100, 255));//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый

    window.create(sf::VideoMode(640, 300), "Test");
    window.setFramerateLimit(60); // количество кадров в секунду

    menu(window);

    std::list<Object*> candy;
    std::list<Object*>::iterator it;

    sf::Texture backtexture;
    backtexture.loadFromFile("images/775.png");

    sf::Sprite backsprite;
    backsprite.setTexture(backtexture);
    backsprite.setPosition(0, 0);

    Player p("image.png", 200, 270, 32, 32);

    srand(time(NULL));
    for (int i = 0; i < 100; i++) 
        candy.push_back(new Object("1.png", rand() % 600 + 30, rand() % -500 + 0, 20, 18));

    sf::Clock clock; // timer
    sf::Clock gameTimeClock;
    int gameTime = 0;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        gameTime = gameTimeClock.getElapsedTime().asSeconds();

        clock.restart();
        time = time / 800;
        std::cout << gameTime << std::endl;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (p.life) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                p.dir = 0; p.speed = 0.1;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 4) CurrentFrame -= 4;
                p.sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 32, 0, 32, 32));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                p.dir = 1; p.speed = 0.1;
                CurrentFrame += 0.005 * time;
                if (CurrentFrame > 4)
                    CurrentFrame -= 4;
                p.sprite.setTextureRect(sf::IntRect(int(CurrentFrame) * 32, 32, 32, 32));
            }
        }
        p.update(time);

        for (it = candy.begin(); it != candy.end();)
        {
            Object* b = *it;
            b->update(time);
            if (b->life == false)
            {
                it = candy.erase(it);
                delete b;
            }
            else it++;
        }

        for (it = candy.begin(); it != candy.end(); it++)
        {
            if ((*it)->getRect().intersects(p.getRect()))
            {
                (*it)->life = false;
                p.playerScore += 1;
            }
        }

        for (it = candy.begin(); it != candy.end(); it++)
            (*it)->update(time);

        if (gameTime == 10)
        {
            gameTime = 0;
            p.life = false;
        }

        window.clear();
        window.draw(backsprite);

        std::ostringstream playerScoreString;    // объ€вили переменную
        playerScoreString << p.playerScore;		//занесли в нее число очков, то есть формируем строку
        text.setString("score:" + playerScoreString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str() 
        text.setPosition(320, 10);//задаем позицию текста, отступа€ от центра камеры
        window.draw(text);//рисую этот текст

        window.draw(p.sprite);

        for (it = candy.begin(); it != candy.end(); it++)
            window.draw((*it)->sprite);

        window.display();
    }

    return 0;
}
