#ifndef RESOURCE_H
#define RESOURCE_H
#include<SFML/Graphics.hpp>
// 定义一个资源类


class Resource {
public:
    sf::Vector2f position;
    int amount;

    Resource(sf::Vector2f pos, int amt);

    // 绘制资源
    void draw(sf::RenderWindow& window);
};
#endif