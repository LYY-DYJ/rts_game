#include <SFML/Graphics.hpp>
#include <Model.hpp>

Map::Map(int w, int h)
{
    width=w;
    height=h;
    // 初始化一些资源
    resources.push_back(Resource(sf::Vector2f(100, 100), 100));
    resources.push_back(Resource(sf::Vector2f(200, 200), 150));
}

void Map::draw(sf::RenderWindow &window)
{
    // 简单地绘制一个黑色背景表示地图
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::Black);
    window.draw(background);

    // 绘制资源
    for (Resource &resource : resources)
    {
        resource.draw(window);
    }
}