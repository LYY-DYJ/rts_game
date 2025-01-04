#include<math.h>
#include "Utils.hpp"

float distance(sf::Vector2f a,sf::Vector2f b)
{
    sf::Vector2f c=a-b;
    return sqrt(c.x*c.x+c.y*c.y);
}