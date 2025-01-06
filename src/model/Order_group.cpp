#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "Utils.hpp"

Order_group::Order_group(sf::Vector2f begin_point,int faction)
{
    this->begin_point=begin_point;
    this->faction=faction;
}

void Order_group::set_end_point(sf::Vector2f end_point,int faction)
{
    if(faction!=this->faction)
        return;
    this->end_point=end_point;
}

std::vector<Entity*> Order_group::get_group(Model* model)
{
    std::vector<Entity*> entities_in_group;
    for(auto [id,entity]:model->entities)
    {
        if(entity->faction==this->faction&&is_in_rectangle(entity->position,begin_point,end_point))
        {
            entities_in_group.push_back(entity);
        }
    }
    return entities_in_group;
}