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
    move_type=no_move;
    position=pos;
}
Moveable* No_move::clone()
{
    Moveable* new_moveable;
    new_moveable = new No_move(*this);
    return new_moveable;
}
void No_move::move(sf::Vector2f direction){}

Walk::Walk(sf::Vector2f pos,float spd)
{
    move_type=walk;
    position=pos;
    speed=spd;
}

Moveable* Walk::clone()
{
    Moveable* new_moveable;
    new_moveable = new Walk(*this);
    return new_moveable;
}

void Walk::move(sf::Vector2f direction)
{
    position+=direction*speed;
}

Entity_factory* False_entity_factory::clone()
{
    Entity_factory* new_entity_factory;
    new_entity_factory = new False_entity_factory();
    return new_entity_factory;
}

True_entity_factory::True_entity_factory(Model* m)
{
    model=m;
    entity_factory_type=true;
    relative_position=sf::Vector2f(0,0);
}

Entity_factory* True_entity_factory::clone()
{
    Entity_factory* new_entity_factory;
    new_entity_factory = new True_entity_factory(model);
    return new_entity_factory;
}

void True_entity_factory::add_entity(const Entity& new_entity)
{
    produceable_entity.push_back(new_entity);
}

void True_entity_factory::generate(int i,sf::Vector2f owner_postion)
{   
    Entity new_entity;
    if(i>=produceable_entity.size())
        return;
    new_entity=produceable_entity.at(i);
    new_entity.moveable->position=relative_position+owner_postion;
    new_entity.strategy->reset();
    model->add_entity(new_entity);
}

Entity::Entity()
{
    id=-1;
    texture="dumb.jpg";
    moveable=new No_move(sf::Vector2f(0,0));
    entity_factory = new False_entity_factory();
    strategy = new Random_strategy(1000);
}

Entity::Entity(int i,std::string t,Moveable* m,Entity_factory* f,Strategy* s)
{
    id=i;
    texture=t;
    moveable=m;
    entity_factory=f;
    strategy=s;
}

Entity::Entity(const Entity& e)
{
    id=e.id;
    texture=e.texture;
    moveable=e.moveable->clone();
    entity_factory=e.entity_factory->clone();
    strategy=e.strategy->clone();
}

Entity::~Entity()
{
    delete moveable;
    delete entity_factory;
    delete strategy;
}

void Entity::operator=(Entity& e)
{
    id=e.id;
    texture=e.texture;
    moveable=e.moveable->clone();
    entity_factory=e.entity_factory->clone();
    strategy=e.strategy->clone();
}

void Entity::set_id(int i)
{
    id=i;
}

void Entity::act()
{
    strategy->control(this);
}



