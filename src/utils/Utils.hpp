#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>
float distance(sf::Vector2f a,sf::Vector2f b);
float norm(sf::Vector2f vector);
float cross_product(sf::Vector2f a,sf::Vector2f b);
bool is_segment_intersect(sf::Vector2f a0,sf::Vector2f a1,sf::Vector2f b0,sf::Vector2f b1);
bool is_segment_rectangle_intersect(sf::Vector2f a0,sf::Vector2f a1,sf::Vector2f origin,sf::Vector2f bulk);
#endif