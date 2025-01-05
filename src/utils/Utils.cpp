#include <math.h>
#include "Utils.hpp"

float distance(sf::Vector2f a, sf::Vector2f b)
{
    sf::Vector2f c = a - b;
    return sqrt(c.x * c.x + c.y * c.y);
}

float norm(sf::Vector2f vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float cross_product(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.y - a.y * b.x;
}

bool is_segment_intersect(sf::Vector2f a0, sf::Vector2f a1, sf::Vector2f b0, sf::Vector2f b1)
{
    return (cross_product(b0 - a0, a1 - a0) * cross_product(b1 - a0, a1 - a0) < 0 && cross_product(a0 - b0, b1 - b0) * cross_product(a1 - b0, b1 - b0) < 0);
}

bool is_segment_rectangle_intersect(sf::Vector2f a0,sf::Vector2f a1,sf::Vector2f origin,sf::Vector2f bulk)
{
    sf::Vector2f half_diagonal=0.5f*bulk;
    sf::Vector2f half_anti_diagnonal=sf::Vector2f(0.5f*bulk.x,-0.5f*bulk.y);
    return(is_segment_intersect(a0,a1,origin-half_diagonal,origin+half_diagonal)||is_segment_intersect(a0,a1,origin-half_anti_diagnonal,origin+half_anti_diagnonal));
}