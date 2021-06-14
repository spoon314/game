#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> // this is where srand() is defined
#include <ctime>
#include <list>
#include <vector>

sf::RenderWindow window;

float speed = 0.1;
float CurrentFrame = 0;

void menu(sf::RenderWindow& window) {
    sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
    menuTexture1.loadFromFile("images/111.png");
    menuTexture2.loadFromFile("images/222.png");
    menuTexture3.loadFromFile("images/333.png");
    aboutTexture.loadFromFile("images/about.png");
    menuBackground.loadFromFile("images/Penguins.jpg");
    sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(100, 30);
    menu2.setPosition(100, 90);
    menu3.setPosition(100, 150);
    menuBg.setPosition(345, 0);

    while (isMenu)
    {
        menu1.setColor(sf::Color::White);
        menu2.setColor(sf::Color::White);
        menu3.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color(129, 181, 221));

        if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
        if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 2; }
        if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Blue); menuNum = 3; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
            if (menuNum == 2) { window.draw(about); window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
            if (menuNum == 3) { window.close(); isMenu = false; }

        }

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);

        window.display();
    }
}

class Object {
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
        sprite.setTextureRect(sf::IntRect(x, y, w, h));
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

class Player {
public:
    float x, y, w, h, dx, dy, speed = 0;
    int dir = 0, playerScore;
    bool life;
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Player(sf::String F, int X, int Y, float W, float H) {
        playerScore = 0;
        life = true;
        File = F;
        w = W; h = H;
        image.loadFromFile("images/" + File);
        //image.createMaskFromColor(sf::Color(41, 33, 59));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(sf::IntRect(x, y, w, h));
    }
    sf::FloatRect getRect() {
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
    window.create(sf::VideoMode(640, 300), "Test");
    window.setFramerateLimit(60); // количество кадров в секунду

    menu(window);

    std::list<Object*> candy;
    std::list<Object*>::iterator it;

    //std::vector<Object*>

    Player p("image.png", 200, 270, 32, 32);

    //Object o("1.png", rand() % 500 + 100, 0, 20, 18);

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
        candy.push_back(new Object("1.png", rand() % 600 + 30, rand() % -100 + 0, 20, 20));

    sf::Clock clock; // timer
    sf::Clock gameTimeClock;
    int gameTime = 0;


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();

        //if (p.life) 
        gameTime = gameTimeClock.getElapsedTime().asSeconds();

        clock.restart();
        time = time / 800;
        std::cout << gameTime << std::endl;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (gameTime = 10)
                std::cout << "!!!!!!!!!!!" << std::endl;
        }

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




        p.update(time);
        //o.update(time);



        for (it = candy.begin(); it != candy.end();)
        {
            Object* b = *it;
            b->update(time);
            if (b->life == false) { it = candy.erase(it); delete b; }
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


        window.clear();
        window.draw(p.sprite);
        for (it = candy.begin(); it != candy.end(); it++)
            window.draw((*it)->sprite);
        //window.draw(o.sprite);
        window.display();
    }

    return 0;
}
