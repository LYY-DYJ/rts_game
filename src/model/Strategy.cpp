#include<unordered_map>
#include<SFML/Graphics.hpp>
#include"Model.hpp"

Strategy* No_strategy::clone()
{
    Strategy* new_strategy;
    new_strategy =new No_strategy;
    return new_strategy;
}

Random_strategy::Random_strategy(int r)
{
    refresh_gap=sf::milliseconds(r);
}

Strategy* Random_strategy::clone()
{
    Strategy* new_strategy;
    new_strategy = new Random_strategy(*this);
    return new_strategy;
}

void Random_strategy::reset()
{
    initial=true;
    clk.restart();
}

void Random_strategy::control(Entity* entity)
{
    
    if(initial)
    {
        direction=sf::Vector2f(1,0);
        initial=false;
    }
    entity->moveable->move(direction);
    if(clk.getElapsedTime()>=refresh_gap)
    {
        clk.restart();
        int rand_num=rand()%4;
        direction=sf::Vector2f(rand_num/2-0.5,rand_num%2-0.5);
        if(entity->entity_factory->entity_num!=0)
            entity->entity_factory->generate(rand_num%entity->entity_factory->entity_num,entity->moveable->position);
    }
}