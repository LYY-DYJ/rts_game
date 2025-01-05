#include<SFML/Graphics.hpp>
#include"Model.hpp"

Normal_attack_event::Normal_attack_event(int i,int atk)
{
    id=i;
    attack=atk;
}

bool Normal_attack_event::settle(Model* model)
{
    if(model->entities.count(id)==0)
        return true;
    model->entities[id].curr_health-=attack;
    model->entities[id].entity_state=ATTACKTED;
    Model_event* e=new Reset_idle_event(id);
    model->events_wait_queue.push(e);
    return true;
}

Reset_idle_event::Reset_idle_event(int i)
{
    id=i;
    clk.restart();
}

bool Reset_idle_event::settle(Model* model)
{
    if(model->entities.count(id)==0)
    {
        return true;
    } 
    else if(clk.getElapsedTime()>duration)
    {
        model->entities[id].entity_state=IDLE;
        return true;
    }
    else
    {
        return false;
    }
}