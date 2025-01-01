#include <Model.hpp>
#include <SFML/Graphics.hpp>

Resource::Resource(sf::Vector2f pos, int amt)
{
    position=pos;
    amount=amt;
}

// 绘制资源
void Resource::draw(sf::RenderWindow &window)
{
    sf::RectangleShape shape(sf::Vector2f(30, 30));
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Yellow);
    window.draw(shape);
}