#pragma once
#include <SFML/Graphics.hpp>
/// Menu
/**
* Функция вызова экрана меню, формирующая фон, текст и его параметры (шрифт, цвет), нажатие кнопок
*/
void menu(sf::RenderWindow& window);


/// Класс объкта конфета
/**
* Хранит в себе координаты спрайта, его размеры, текстуру, переменные отвечающие за жизнь, скорость спрайта
*/
class Candy 
{
public:
    float x;///< абсцисса спрайта
    float y;///< ордината спрайта
    float w;///< ширина спрайта, по которой он будет вырезаться из заданной картинки
    float h;///< длина спрайта, по которой он будет вырезаться из заданной картинки
    //float dx;///< смещение спрайта по оси абсцисс
    //float dy;///< смещение спрайта по оси ординат
    float speed = 0.1;///< скорость перемещения спрайта
    //int select = 0;///< определяет нажатие одной из двух кнопок (лево/право) 
    bool life;///< отвечает за жизнь спрайта
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Candy(sf::String F, int X, int Y, float W, float H);///< функция задающая значения, описанные в классе
    sf::FloatRect getRect();///< функция, берущая прямоугольник от размеров спрайта
    void update(float time);///< функция, отвечающая за обновление спрайта
};

/// Класс объкта игрока
/**
* Хранит в себе координаты спрайта, его размеры, текстуру, переменные отвечающие за жизнь, набранные очки, скорость и перемещение спрайта
*/
class Player 
{
public:
    float x;///< абсцисса спрайта
    float y;///< ордината спрайта
    float w;///< ширина спрайта, по которой он будет вырезаться из заданной картинки
    float h;///< длина спрайта, по которой он будет вырезаться из заданной картинки
    float dx;///< смещение спрайта по оси абсцисс
    float dy;///< смещение спрайта по оси ординат
    float speed = 0;///< скорость перемещения спрайта
    int select = 0;///< определяет нажатие одной из двух кнопок (лево/право) 
    bool life;///< отвечает за жизнь игрока
    int playerScore;///< хранит очки, набранные игроком
    sf::String File;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    Player(sf::String F, int X, int Y, float W, float H);///< функция задающая значения, описанные в классе
    sf::FloatRect getRect();///< функция, берущая прямоугольник от размеров спрайта
    void update(float time);///< функция, отвечающая за обновление спрайта
    void Left(float &shot, float time);///< функция, отвечающая за перемещение персонажа влево
    void Right(float &shot, float time);///< функция, отвечающая за перемещение персонажа вправо
};