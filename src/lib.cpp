#include "lib.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib> // this is where srand() is defined
#include <ctime>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

void menu(sf::RenderWindow &window) //функция вызова окна меню
{
    sf::Font font;                  ///< шрифт
    font.loadFromFile("20686.ttf"); ///< загрузка шрифта
    sf::Text text1("", font, 50);   ///< формирование строки
    text1.setFillColor(sf::Color(0, 100, 255)); ///< заливка шрифта
    sf::Text text2("", font, 50);
    text2.setFillColor(sf::Color(0, 100, 255));
    sf::Text text3("", font, 20);
    text3.setFillColor(sf::Color(0, 100, 255));
    sf::Text text4("", font, 20);
    text4.setFillColor(sf::Color(0, 100, 255));

    text1.setString("new game"); //задаем строку тексту и вызываем
                                 //сформированную выше строку методом .str()
    text1.setPosition(100,
                      30); //задаем позицию текста, отступая от центра камеры

    text2.setString("exit"); //задаем строку тексту и вызываем сформированную
                             //выше строку методом .str()
    text2.setPosition(100,
                      150); //задаем позицию текста, отступая от центра камеры

    text3.setString(
        "rules: collect as many candies"); //задаем строку тексту и вызываем
                                           //сформированную выше строку методом
                                           //.str()
    text3.setPosition(300,
                      150); //задаем позицию текста, отступая от центра камеры

    text4.setString(
        "as possible in 10 seconds (max 100)"); //задаем строку тексту и
                                                //вызываем сформированную выше
                                                //строку методом .str()
    text4.setPosition(300,
                      190); //задаем позицию текста, отступая от центра камеры

    sf::Texture menuBackground;
    menuBackground.loadFromFile("images/2.png");
    sf::Sprite menuBg(menuBackground);
    bool isMenu = true;
    menuBg.setPosition(0, 0);

    while (isMenu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (sf::IntRect(100, 30, 300, 50)
                    .contains(sf::Mouse::getPosition(window)))
                isMenu = false; //если нажали первую кнопку, то выходим из меню
            if (sf::IntRect(100, 150, 300, 50)
                    .contains(sf::Mouse::getPosition(window))) {
                window.close();
                isMenu = false;
            }
        }

        window.draw(menuBg);
        window.draw(text1); //рисую текст
        window.draw(text2); //рисую текст
        window.draw(text3); //рисую текст
        window.draw(text4); //рисую текст
        window.display();
    }
}

Candy::Candy(sf::String F, int X, int Y, float W, float H) {
    File = F;
    w = W;
    h = H;
    life = true;
    image.loadFromFile("images/" + File);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    x = X;
    y = Y;
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

sf::FloatRect Candy::getRect() { return sf::FloatRect(x, y, w, h); }
void Candy::update(float time) {
    if (y > 300)
        y = 0;
    y += speed * time;
    sprite.setPosition(x, y);
}

Player::Player(sf::String F, int X, int Y, float W, float H) {
    playerScore = 0;
    life = true;
    File = F;
    w = W;
    h = H;
    image.loadFromFile("images/" + File);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    x = X;
    y = Y;
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

sf::FloatRect Player::getRect() { return sf::FloatRect(x, y, w, h); }

void Player::update(float time) {
    switch (select) {
    case 0:
        dx = -speed;
        dy = 0;
        break;
    case 1:
        dx = speed;
        dy = 0;
        break;
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

void Player::Left(float &shot, float time) {
    select = 0;
    speed = 0.1;
    shot += 0.005 * time;
    if (shot > 4)
        shot -= 4;
}

void Player::Right(float &shot, float time) {
    select = 1;
    speed = 0.1;
    shot += 0.005 * time;
    if (shot > 4)
        shot -= 4;
}