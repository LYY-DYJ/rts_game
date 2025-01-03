#include<string>
#include<SFML/Graphics.hpp>
#include"Model.hpp"

Moveable::Moveable()
{
    move_type=no_move;
    position=sf::Vector2f(0,0);
    speed=0;
}


No_move::No_move(sf::Vector2f pos)
{
    position=pos;
}

void No_move::move(sf::Vector2f direction){}

Walk::Walk(sf::Vector2f pos,float spd)
{
    position=pos;
    speed=spd;
}

void Walk::move(sf::Vector2f direction)
{
    position+=direction*speed;
}

Entity_factory::Entity_factory(Model* m)
{
    model=m;
    produce_position=sf::Vector2f(0,0);
}

void Entity_factory::add_entity(Entity new_entity)
{
    produceable_entity.push_back(new_entity);
}

void Entity_factory::generate(int i)
{   
    Entity new_entity=produceable_entity.at(i);
    model->add_entity(produceable_entity.at(i));
}

Entity::Entity()
{
    id=-1;
    texture="dumb.jpg";
    moveable=nullptr;
}

Entity::Entity(int i,std::string t,Moveable* m)
{
    id=i;
    texture=t;
    moveable=m;
}

void Entity::set_id(int i)
{
    id=i;
}

void Entity::act()
{
    moveable->move(sf::Vector2f(0,0.1));
}



