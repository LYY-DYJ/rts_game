#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "Utils.hpp"

int Order_group::group_id = 0;

Order_group::Order_group(sf::Vector2f begin_point, int faction)
{
    this->begin_point = begin_point;
    this->end_point = end_point;
    this->faction = faction;
    this->is_setting = true;
    group_id++;
}

void Order_group::set_end_point(sf::Vector2f end_point, int faction)
{
    if (faction != this->faction)
        return;
    this->end_point = end_point;
}

std::vector<Entity *> Order_group::get_group(Model *model)
{
    if (is_setting)
    {
        entities_in_group.clear();
        for (auto [id, entity] : model->entities)
        {
            if (entity->faction == this->faction && is_in_rectangle(entity->position, begin_point, end_point))
            {
                entities_in_group.push_back(entity);
            }
        }
    }
    return entities_in_group;
}