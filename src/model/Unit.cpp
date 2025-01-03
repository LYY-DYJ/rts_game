#include <Model.hpp>

Unit::Unit()
{
    id=-1;
    texture="dumb.jpg";
    position = sf::Vector2f(0,0);
    health = 0;
    speed = 0;
    attackPower = 0;
}

Unit::Unit(int i, std::string t, sf::Vector2f pos, int hp, int spd, int atk)
{
    id=i;
    texture=t;
    position = pos;
    health = hp;
    speed = spd;
    attackPower = atk;
}

void Unit::move(sf::Vector2f direction)
{
    position += speed * direction;
}
