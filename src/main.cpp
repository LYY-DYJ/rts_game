#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"RTS Game");
    Model model(4000,2000);
    View view(&model,&window);
    Controller controller(&window,&view);
    

    // 初始化一些单位
    std::vector<Unit> units;
    model.add_unit("shuai_jimao.jpg", sf::Vector2f(50, 50), 100, 5, 10);
    model.add_unit("wuyu_xiaobai.jpg", sf::Vector2f(150, 150), 120, 4, 12);

    while (window.isOpen())
    {
        controller.handleInput();
        view.draw_all();
    }

    return 0;
}
