#include<SFML/Graphics.hpp>
#include"Model.hpp"

Skill* No_skill::clone()
{
    Skill* new_skill;
    new_skill=new No_skill;
    return new_skill;
}

Normal_attack::Normal_attack(float cd_time,float range,int attack)
{

}


