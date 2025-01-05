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
    Controller controller(&window,&model,&view);
    

    // 初始化一些单位
    Strategy* s1 = new Random_strategy(1000);
    Moveable* m1=new Walk(sf::Vector2f(100,100),4);
    Entity_factory* f1=new False_entity_factory;
    Skill* sk1=new No_skill();
    Strategy* s2 = new Random_strategy(1000);
    Moveable* m2=new Walk(sf::Vector2f(200,200),4);
    Entity_factory* f2=new True_entity_factory(&model);
    Skill* sk2 = new No_skill();
    Entity ji=Entity(-1,UNIT,"shuai_jimao.jpg",&model,m1,f1,s1,sk1);
    Entity bai=Entity(-1,UNIT,"wuyu_xiaobai.jpg",&model,m2,f2,s2,sk2);
    bai.entity_factory->add_entity(bai);
    bai.entity_factory->add_entity(ji);
    model.add_entity(ji);
    model.add_entity(bai);


    while (window.isOpen())
    {
        controller.handleInput();
        model.update();
        view.draw_all();
    }

    return 0;
}
