#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"RTS Game");
    window.setFramerateLimit(60);
    Model model;
    View view(&model,&window);
    Controller controller(&window,&view);
    

    // 初始化一些单位
    Strategy* s0 = new Random_strategy(1000);
    Moveable* m0=new Walk(sf::Vector2f(100,100),4);
    Entity_factory* f0=new False_entity_factory;
    Strategy* s1 = new Random_strategy(1000);
    Moveable* m1=new Walk(sf::Vector2f(100,100),4);
    Entity_factory* f1=new False_entity_factory;
    Strategy* s2 = new Random_strategy(1000);
    Moveable* m2=new No_move(sf::Vector2f(200,200));
    Entity_factory* f2=new True_entity_factory(&model);
    model.add_entity(Entity(-1,"shuai_jimao.jpg",m1,f1,s1));
    model.add_entity(Entity(-1,"wuyu_xiaobai.jpg",m2,f2,s2));
    model.entities[1].entity_factory->add_entity(Entity(-1,"shuai_jimao.jpg",m0,f0,s0));

    while (window.isOpen())
    {
        controller.handleInput();
        model.update();
        view.draw_all();
    }

    return 0;
}
