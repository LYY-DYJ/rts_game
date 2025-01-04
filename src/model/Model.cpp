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

void Model::attack(int id)
{
    Model_event* e=new Normal_attack_event(id,50);
    events_queue.push(e);
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
        if(d<range&&(d<min_d||min_d<0))
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
    while(events_wait_queue.size()!=0)
    {
        events_queue.push(events_wait_queue.front());
        events_wait_queue.pop();
    }
    while(events_queue.size()!=0)
    {
        if(events_queue.front()->settle(this)==true)
        {
            delete events_queue.front();
            events_queue.pop();
        }
        else
        {
            events_wait_queue.push(events_queue.front());
            events_queue.pop();
        }
    }
    if(entities.empty())
        return;
    for(auto& [id, entity]: entities)
    {
        if(entity.health<=0)
        {
            entities.erase(id);
            erase_vector.push_back(id);
        }
    }
}

void Model::update()
{
    entities_act();
    settle_event();
}