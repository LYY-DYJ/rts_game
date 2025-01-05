#include<SFML/Graphics.hpp>
#include"Model.hpp"

// Entity_factory* Entity_factory::create_from_json(json entity_factory_json)
// {

// }

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

void True_entity_factory::add_entity(const Entity* new_entity)
{
    Entity* enitity_pointer=new Entity(*new_entity);
    produceable_entity.push_back(enitity_pointer);
    entity_num++;
}

void True_entity_factory::generate(int i,sf::Vector2f owner_postion)
{   
    if(i<0&&i>=-int(produceable_entity.size()))
        i=produceable_entity.size()+i;
    if(i>=int(produceable_entity.size())||i<0)
        return;
    Entity* new_entity= new Entity(*produceable_entity.at(i));
    new_entity->curr_health=new_entity->max_health;
    new_entity->position=relative_position+owner_postion;
    new_entity->strategy->reset();
    model->add_entity(new_entity);
}