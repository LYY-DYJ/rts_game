#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"RTS Game");
    Model model;
    View view(&model,&window);
    Controller controller(&window,&view);
    

    // 初始化一些单位
    Moveable* m0=new Walk(sf::Vector2f(100,100),10);
    Moveable* m1=new No_move(sf::Vector2f(200,200));
    model.add_entity(Entity(-1,"shuai_jimao.jpg",m0));
    model.add_entity(Entity(-1,"wuyu_xiaobai.jpg",m1));

    while (window.isOpen())
    {
        controller.handleInput();
        model.update();
        view.draw_all();
    }

    return 0;
}
