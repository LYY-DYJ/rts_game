#include <unordered_map>
#include <random>
#include <SFML/Graphics.hpp>
#include "Model.hpp"

Strategy *Strategy::create_from_json(json strategy_json)
{
    if (strategy_json["strategy_type"] == "No_strategy")
    {
        return new No_strategy();
    }
    if (strategy_json["strategy_type"] == "Random_strategy")
    {
        return new Random_strategy(strategy_json["refresh_gap"]);
    }
    if (strategy_json["strategy_type"] == "Normal_strategy")
    {
        return new Normal_strategy();
    }
    else
    {
        std::cout << "Unknown strategy_type" << std::endl;
        return new No_strategy();
    }
}

Strategy *No_strategy::clone()
{
    Strategy *new_strategy;
    new_strategy = new No_strategy;
    return new_strategy;
}

Random_strategy::Random_strategy(int r)
{
    refresh_gap = sf::milliseconds(r);
}

Strategy *Random_strategy::clone()
{
    Strategy *new_strategy;
    new_strategy = new Random_strategy(*this);
    return new_strategy;
}

void Random_strategy::reset()
{
    initial = true;
    clk.restart();
}

void Random_strategy::control(Entity *entity)
{

    if (initial)
    {
        direction = sf::Vector2f(1, 0);
        initial = false;
    }
    entity->moveable->move(entity, direction);
    if (clk.getElapsedTime() >= refresh_gap)
    {
        clk.restart();
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 engine(seed);
        std::uniform_int_distribution<int> distribution(0, 99);
        int random_number = distribution(engine);
        direction = sf::Vector2f(random_number / 2 - 0.5, random_number % 2 - 0.5);
        if (entity->entity_factory->entity_num != 0)
            entity->entity_factory->generate(entity, random_number % entity->entity_factory->entity_num);
    }
}

Normal_strategy::Normal_strategy()
{
    initial = true;
    behavior_pattern_stack.push(WALK_TO_DESTINATION);
    is_destination_available = false;
}

Strategy *Normal_strategy::clone()
{
    Strategy *new_strategy;
    new_strategy = new Normal_strategy();
    return new_strategy;
}

void Normal_strategy::reset()
{
    initial = true;
    behavior_pattern_stack.push(WALK_TO_DESTINATION);
    is_destination_available = false;
}

void Normal_strategy::control(Entity *owner)
{
    std::vector<Entity *> entities_in_sight = owner->model->entity_in_sight(owner->position, owner->sight);

    bool is_enemy = false;
    bool enemy_out_skill_range = true;
    sf::Vector2f enemy_position;
    for (Entity *entity : entities_in_sight)
    {
        if (entity->faction != 0 && entity->faction != owner->faction)
        {
            is_enemy = true;
            enemy_position = entity->position;
            if (distance(enemy_position, owner->position) < owner->skill->range)
            {
                enemy_out_skill_range = false;
            }
        }
    }
    if (behavior_pattern_stack.top() == WAIT)
    {
        if (is_enemy == true && enemy_out_skill_range == true)
            behavior_pattern_stack.push(FIND_ENEMY);
        else if (is_enemy == true && enemy_out_skill_range == false)
            behavior_pattern_stack.push(ATTACKING);
    }
    else if (behavior_pattern_stack.top() == WALK_TO_DESTINATION)
    {
        if (is_enemy == true && enemy_out_skill_range == true)
            behavior_pattern_stack.push(FIND_ENEMY);
        else if (is_enemy == true && enemy_out_skill_range == false)
            behavior_pattern_stack.push(ATTACKING);
        else
        {
            if (is_destination_available != true)
            {
                destination = owner->enemy_base_position();
                is_destination_available = true;
            }
            if (owner->model->is_way_blocked(owner->position, destination,entities_in_sight))
                behavior_pattern_stack.push(BY_PASS_BLOCK);
            else
                owner->moveable->move(owner, destination - owner->position);
        }
    }
    else if (behavior_pattern_stack.top() == BY_PASS_BLOCK)
    {
        if (is_enemy == true && enemy_out_skill_range == true)
            behavior_pattern_stack.push(FIND_ENEMY);
        else if (is_enemy == true && enemy_out_skill_range == false)
            behavior_pattern_stack.push(ATTACKING);
        else if (owner->model->is_way_blocked(owner->position, destination,entities_in_sight))
            owner->moveable->move(owner, sf::Vector2f((destination - owner->position).y, -(destination - owner->position).x));
        else
        {
            behavior_pattern_stack.pop();
            behavior_pattern_stack.push(WALK_TO_DESTINATION);
        }
    }
    else if (behavior_pattern_stack.top() == FIND_ENEMY)
    {
        if (is_enemy == true && enemy_out_skill_range == true)
            owner->moveable->move(owner, enemy_position - owner->position);
        else if (is_enemy == true && enemy_out_skill_range == false)
        {
            behavior_pattern_stack.pop();
            behavior_pattern_stack.push(ATTACKING);
        }
        else
            behavior_pattern_stack.pop();
    }
    else if (behavior_pattern_stack.top() == ATTACKING)
    {
        if (is_enemy == true && enemy_out_skill_range == true)
        {
            behavior_pattern_stack.pop();
            behavior_pattern_stack.push(FIND_ENEMY);
        }
        else if (is_enemy == true && enemy_out_skill_range == false)
        {
            owner->skill->release(owner);
        }
        else
            behavior_pattern_stack.pop();
    }
}