#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "Utils.hpp"

Model::Model()
{
    id_max = -1;
}

Model::~Model()
{
    for (auto [id, entity] : entities)
    {
        delete entity;
    }
    delete group;
}

int Model::add_entity(Entity *entity)
{
    id_max++;
    entity->id = id_max;
    entity->model = this;
    entities[id_max] = entity;
    return id_max;
}

int Model::add_base(Entity *entity)
{
    int id = add_entity(entity);
    base_faction_id[entity->faction] = id;
    return id;
}

void Model::attack(int id)
{
    Model_event *e = new Normal_attack_event(id, 500);
    events_queue.push(e);
}

void Model::order_change_group_destination(sf::Vector2f new_destination)
{
    if(group==nullptr)
        return;
    std::vector<Entity *> entities_grouped = group->get_group(this);
    for (Entity *entity : entities_grouped)
    {
        entity->strategy->order_change_destination(new_destination);
    }
}

std::vector<Entity *> Model::entity_in_range(sf::Vector2f point, float range)
{
    std::vector<Entity *> ev;
    for (auto [id, entity] : entities)
    {
        if (distance(entity->position, point) < range)
        {
            ev.push_back(entity);
        }
    }
    return ev;
}

std::vector<Entity *> Model::entity_in_sight(sf::Vector2f point, float range)
{
    std::vector<Entity *> ev;
    std::vector<Entity *> entities_in_sight_range = entity_in_range(point, range);
    for (Entity *entity : entities_in_sight_range)
    {
        if (!is_way_blocked(point, entity->position, entities_in_sight_range))
        {
            ev.push_back(entity);
        }
    }
    return ev;
}

bool Model::is_way_blocked(sf::Vector2f position1, sf::Vector2f position2, std::vector<Entity *> blocks)
{
    bool is_blocked = false;
    for (auto block : blocks)
    {
        if (block->entity_type == MOUNTAIN && is_segment_rectangle_intersect(position1, position2, block->position, block->bulk))
        {
            is_blocked = true;
        }
    }
    return is_blocked;
}

Entity *Model::entity_closest(sf::Vector2f point, float range)
{
    Entity *e = nullptr;
    float min_d = -1;
    for (auto [id, entity] : entities)
    {
        float d = distance(entity->position, point);
        if (d < range && (d < min_d || min_d < 0))
        {
            min_d = d;
            e = entity;
        }
    }
    return e;
}

std::vector<Entity *> Model::entity_vector()
{
    std::vector<Entity *> ev;
    for (auto [id, entity] : entities)
    {
        ev.push_back(entity);
    }
    return ev;
}

void Model::entities_act()
{
    for (auto [id, entity] : entities)
    {
        entity->act();
    }
}

void Model::settle_event()
{
    while (events_wait_queue.size() != 0)
    {
        events_queue.push(events_wait_queue.front());
        events_wait_queue.pop();
    }
    while (events_queue.size() != 0)
    {
        if (events_queue.front()->settle(this) == true)
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
    if (entities.empty())
        return;
    for (auto [id, entity] : entities)
    {
        if (entity->curr_health <= 0)
        {
            erase_vector.push_back(id);
        }
    }
    for (int id : erase_vector)
    {
        entities.erase(id);
    }
}

void Model::update()
{
    entities_act();
    settle_event();
}
