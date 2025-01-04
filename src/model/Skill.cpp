#include<SFML/Graphics.hpp>
#include"Model.hpp"

Skill* No_skill::clone()
{
    Skill* new_skill;
    new_skill=new No_skill;
    return new_skill;
}

Normal_attack::Normal_attack(float cd,float r,int atk)
{
    cd_time=cd;
    range=r;
    attack=atk;
    available=true;
}

Skill* Normal_attack::clone()
{
    Skill* new_skill;
    new_skill=new Normal_attack(*this);
    return new_skill;
}

void Normal_attack::reset()
{
    clk.restart();
    available=true;
}

void Normal_attack::release(Entity* entity)
{
    int target_id=entity->model->entity_closest(entity->moveable->position,range)->id;
    Model_event* e=new Normal_attack_event(target_id,attack);
    entity->model->events_queue.push(e);
}

