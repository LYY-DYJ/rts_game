#include <Model.hpp>

Unit::Unit(sf::Vector2f pos, int hp, int spd, int atk)
{
    position = pos;
    health = hp;
    speed = spd;
    attackPower = atk;
}

void Unit::move(sf::Vector2f direction)
{
    position += speed * direction;
}

void Unit::draw(sf::RenderWindow &window)
{
    sf::CircleShape shape(20);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}