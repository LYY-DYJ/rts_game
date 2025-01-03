#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Model.hpp"
#include "Game_view.hpp"

int main()
{
    Model model(4000,2000);
    Game_view view(&model);

    // 初始化一些单位
    std::vector<Unit> units;
    model.add_unit("shuai_jimao.jpg", sf::Vector2f(50, 50), 100, 5, 10);
    model.add_unit("wuyu_xiaobai.jpg", sf::Vector2f(150, 150), 120, 4, 12);

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
        view.drawUnits();
    }

    return 0;
}
