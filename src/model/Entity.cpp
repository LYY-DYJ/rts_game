#include<string>
#include<SFML/Graphics.hpp>
#include"Model.hpp"

Moveable::Moveable()
{
    move_type=NO_MOVE;
    position=sf::Vector2f(0,0);
    speed=0;
}


No_move::No_move(sf::Vector2f pos)
{
    move_type=NO_MOVE;
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
    move_type=WALK;
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

False_entity_factory::False_entity_factory()
{
    entity_num=0;
}

Entity_factory* False_entity_factory::clone()
{
    Entity_factory* new_entity_factory;
    new_entity_factory = new False_entity_factory(*this);
    return new_entity_factory;
}

True_entity_factory::True_entity_factory(Model* m)
{
    model=m;
    entity_factory_type=true;
    entity_num=0;
    relative_position=sf::Vector2f(0,0);
}

Entity_factory* True_entity_factory::clone()
{
    Entity_factory* new_entity_factory;
    new_entity_factory = new True_entity_factory(*this);
    return new_entity_factory;
}

void True_entity_factory::add_entity(const Entity& new_entity)
{
    produceable_entity.push_back(new_entity);
    entity_num++;
}

void True_entity_factory::generate(int i,sf::Vector2f owner_postion)
{   
    Entity new_entity;
    if(i<0&&i>=-int(produceable_entity.size()))
        i=produceable_entity.size()+i;
    if(i>=int(produceable_entity.size())||i<0)
        return;
    new_entity=produceable_entity.at(i);
    new_entity.curr_health=new_entity.max_health;
    new_entity.moveable->position=relative_position+owner_postion;
    new_entity.strategy->reset();
    model->add_entity(new_entity);
}

Entity::Entity()
{
    id=-1;
    curr_health=max_health=100;
    entity_state=IDLE;
    model=nullptr;
    texture="dumb.jpg";
    moveable=new No_move(sf::Vector2f(0,0));
    entity_factory = new False_entity_factory();
    strategy = new No_strategy();
    skill = new No_skill();
}

Entity::Entity(int i,Entity_type et,std::string t,Model* mo,Moveable* m,Entity_factory* f,Strategy* s,Skill* sk)
{
    id=i;
    entity_type=et;
    texture=t;
    curr_health=max_health=100;
    entity_state=IDLE;
    model=mo;
    moveable=m;
    entity_factory=f;
    strategy=s;
    skill=sk;
}

Entity::Entity(const Entity& e)
{
    id=e.id;
    entity_type=e.entity_type;
    texture=e.texture;
    max_health=e.max_health;
    curr_health=e.curr_health;
    entity_state=e.entity_state;
    model=e.model;
    moveable=e.moveable->clone();
    entity_factory=e.entity_factory->clone();
    strategy=e.strategy->clone();
    skill=e.skill->clone();
}

Entity::~Entity()
{
    delete moveable;
    delete entity_factory;
    delete strategy;
    delete skill;
}

void Entity::operator=(Entity& e)
{
    id=e.id;
    entity_type=e.entity_type;
    texture=e.texture;
    max_health=e.max_health;
    curr_health=e.curr_health;
    entity_state=e.entity_state;
    model=e.model;
    moveable=e.moveable->clone();
    entity_factory=e.entity_factory->clone();
    strategy=e.strategy->clone();
    skill =e.skill->clone();
}

void Entity::set_id(int i)
{
    id=i;
}

void Entity::act()
{
    strategy->control(this);
}



