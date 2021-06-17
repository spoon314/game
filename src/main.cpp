#include "lib.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib> // this is where srand() is defined
#include <ctime>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

int main() {
    float shot = 0;
    sf::Font font;
    font.loadFromFile("20686.ttf"); //передаем нашему шрифту файл шрифта
    sf::Text text(
        "", font,
        30); //создаем объект текст. закидываем в объект текст строку, шрифт,
             //размер шрифта(в пикселях);//сам объект текст (не строка)
    text.setFillColor(
        sf::Color(0, 100, 255)); //покрасили текст в красный. если убрать эту
                                 //строку, то по умолчанию он белый

    sf::RenderWindow window(sf::VideoMode(640, 300), "Test");
    window.setFramerateLimit(60); // количество кадров в секунду

    menu(window);

    std::list<std::unique_ptr<Candy>> candy;
    std::list<std::unique_ptr<Candy>>::iterator it;

    sf::Texture backtexture;
    backtexture.loadFromFile("images/2.png");

    sf::Sprite backsprite;
    backsprite.setTexture(backtexture);
    backsprite.setPosition(0, 0);

    Player p("3.png", 200, 270, 32, 32);

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
        candy.push_back(std::make_unique<Candy>("1.png", rand() % 600 + 30,
                                                rand() % -500 + 0, 20, 18));

    sf::Clock clock; // timer
    sf::Clock gameTimeClock;
    int gameTime = 0;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();

        gameTime = gameTimeClock.getElapsedTime().asSeconds();

        clock.restart();
        time = time / 800;
        // std::cout << gameTime << std::endl;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (p.life) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                p.Left(shot, time);
                p.sprite.setTextureRect(sf::IntRect(int(shot) * 32, 0, 32, 32));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                p.Right(shot, time);
                p.sprite.setTextureRect(
                    sf::IntRect(int(shot) * 32, 32, 32, 32));
            }
        }
        
        p.update(time);

        for (it = candy.begin(); it != candy.end();) {
            if ((*it)->life == false) {
                it = candy.erase(it);
            } else
                it++;
        }

        for (it = candy.begin(); it != candy.end(); it++) {
            if ((*it)->getRect().intersects(p.getRect())) {
                (*it)->life = false;
                p.playerScore += 1;
            }
        }

        for (it = candy.begin(); it != candy.end(); it++)
            (*it)->update(time);

        if (gameTime == 10) {
            gameTime = 0;
            p.life = false;
        }

        window.clear();
        window.draw(backsprite);

        std::ostringstream playerScoreString;
        playerScoreString << p.playerScore;
        text.setString("score:" + playerScoreString.str());
        text.setPosition(320, 10);
        window.draw(text);

        window.draw(p.sprite);

        for (it = candy.begin(); it != candy.end(); it++)
            window.draw((*it)->sprite);

        window.display();
    }

    return 0;
}