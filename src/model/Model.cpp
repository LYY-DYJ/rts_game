#include<SFML/Graphics.hpp>
#include"Model.hpp"
#include"Utils.hpp"

Model::Model()
{
    id_max=-1;
}

void Model::add_entity(Entity entity)
{
    id_max++;
    entity.id=id_max;
    entity.model=this;
    entities[id_max]=entity;
}

std::vector<Entity> Model::entity_in_range(sf::Vector2f point,float range)
{
    std::vector<Entity> ev;
    for(auto& [id, entity] : entities)
    {
       if(distance(entity.moveable->position,point)<range)
       {
            ev.push_back(entity);
       }
    }
    return ev;
}

Entity* Model::entity_closest(sf::Vector2f point,float range)
{
    Entity* e=nullptr;
    float min_d=-1;
    for(auto& [id, entity] : entities)
    {
        float d=distance(entity.moveable->position,point);
        if((d<range&&d<min_d)||min_d<0)
        {
            min_d=d;
            e=&entity;
        }
    }
    return e;
}

std::vector<Entity> Model::entity_vector()
{
    std::vector<Entity> ev;
    for(auto& [id, entity] : entities)
    {
        ev.push_back(entity);
    }
    return ev;
}

void Model::entities_act()
{
    for(auto& [id, entity] : entities)
    {
        entity.act();
    }
}

void Model::settle_event()
{

}

void Model::update()
{
    entities_act();
}