#include<SFML/Graphics.hpp>
#include"Model.hpp"

Model::Model()
{
    id_max=-1;
}

void Model::add_entity(Entity entity)
{
    id_max++;
    entity.id=id_max;
    entities[id_max]=entity;
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

void Model::update()
{
    for(auto& [id, entity] : entities)
    {
        entity.act();
    }
}