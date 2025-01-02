#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Model.hpp"
#include "Game_view.hpp"

int main()
{
    Game_view view;
    // 初始化地图
    Map map(800, 600);

    // 初始化一些单位
    std::vector<Unit> units;
    units.push_back(Unit(0, "shuai_jimao.jpg", sf::Vector2f(50, 50), 100, 5, 10));
    units.push_back(Unit(1, "wuyu_xiaobai.jpg", sf::Vector2f(150, 150), 120, 4, 12));

    while (view.isOpen())
    {
        sf::Event event;
        while (view.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                view.close();
            }
        }
        for (Unit &unit : units)
        {
            unit.move(sf::Vector2f(1, 0));
        }
        view.drawUnits(units);
    }

    return 0;
}
