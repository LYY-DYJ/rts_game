#include <SFML/Graphics.hpp>
#include "Model.hpp"

Skill *Skill::create_from_json(json skill_json)
{
    if (skill_json["skill_type"] == "No_skill")
    {
        return new No_skill();
    }
    else if (skill_json["skill_type"] == "Normal_attack")
    {
        return new Normal_attack(skill_json["cd_time"], skill_json["range"], skill_json["attack"]);
    }
    else
    {
        std::cout << "Unknown skill_type" << std::endl;
        return new No_skill();
    }
}

No_skill::No_skill()
{
    skill_type = NO_SKILL;
    range = 0;
}

Skill *No_skill::clone()
{
    Skill *new_skill;
    new_skill = new No_skill;
    return new_skill;
}

Normal_attack::Normal_attack(float cd, float r, int atk)
{
    skill_type = ATTACK;
    cd_time = cd;
    range = r;
    attack = atk;
    available = true;
}

Skill *Normal_attack::clone()
{
    Skill *new_skill;
    new_skill = new Normal_attack(*this);
    return new_skill;
}

void Normal_attack::reset()
{
    clk.restart();
    available = true;
}

void Normal_attack::release(Entity *entity)
{
    if (clk.getElapsedTime() > sf::milliseconds(cd_time))
    {
        clk.restart();
        int target_id = -1;
        std::vector<Entity *> entities_in_range = entity->model->entity_in_range(entity->position, range);
        for (int i = 0; i < int(entities_in_range.size()) && target_id == -1; i++)
        {
            int tmp = entities_in_range[i]->faction;
            if (tmp != entity->faction && tmp != 0)
            {
                target_id = entities_in_range[i]->id;
            }
        }
        Model_event *e = new Normal_attack_event(target_id, attack);
        entity->model->events_queue.push(e);
    }
}
