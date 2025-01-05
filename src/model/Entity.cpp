#include<string>
#include<SFML/Graphics.hpp>
#include"Model.hpp"

Entity::Entity()
{
    id=-1;
    curr_health=max_health=100;
    position=sf::Vector2f(0,0);
    bulk=sf::Vector2f(0,0);
    entity_state=IDLE;
    model=nullptr;
    texture="dumb.jpg";
    moveable=new No_move();
    entity_factory = new False_entity_factory();
    strategy = new No_strategy();
    skill = new No_skill();
}

Entity::Entity(int faction,Entity_type et,std::string t,sf::Vector2f p,sf::Vector2f b,int max_h,Moveable* m,Entity_factory* f,Strategy* s,Skill* sk)
{
    this->faction=faction;
    entity_type=et;
    texture=t;
    position=p;
    bulk=b;
    curr_health=max_health=max_h;
    entity_state=IDLE;
    moveable=m;
    entity_factory=f;
    strategy=s;
    skill=sk;
}

Entity::Entity(const Entity& e)
{
    faction=e.faction;
    id=e.id;
    entity_type=e.entity_type;
    texture=e.texture;
    position=e.position;
    bulk=e.bulk;
    max_health=e.max_health;
    curr_health=e.curr_health;
    entity_state=e.entity_state;
    model=e.model;
    moveable=e.moveable->clone();
    entity_factory=e.entity_factory->clone();
    strategy=e.strategy->clone();
    skill=e.skill->clone();
}

Entity::~Entity()
{
    delete moveable;
    delete entity_factory;
    delete strategy;
    delete skill;
}

void Entity::operator=(Entity& e)
{
    faction=e.faction;
    id=e.id;
    entity_type=e.entity_type;
    texture=e.texture;
    position=e.position;
    bulk=e.bulk;
    max_health=e.max_health;
    curr_health=e.curr_health;
    entity_state=e.entity_state;
    model=e.model;
    moveable=e.moveable->clone();
    entity_factory=e.entity_factory->clone();
    strategy=e.strategy->clone();
    skill =e.skill->clone();
}

void Entity::set_id(int i)
{
    id=i;
}

void Entity::act()
{
    strategy->control(this);
}

Entity_type Entity::str2entity_type(std::string str)
{
    if (str == "UNIT") {
        return UNIT;
    } else if (str == "BUILDING") {
        return BUILDING;
    } else if (str == "TERRAIN") {
        return TERRAIN;
    } else {
        throw std::runtime_error("Invalid Entity_type string: " + str);
    }
}

Entity* Entity::create_from_json(json entity_json)
{
    int entity_faction=entity_json["faction"];
    Entity_type entity_type=Entity::str2entity_type(entity_json["entity_type"]);
    std::string texture=entity_json["texture"];
    int max_health=entity_json["max_health"];
    sf::Vector2f position=sf::Vector2f(entity_json["position"][0],entity_json["position"][1]);
    sf::Vector2f bulk=sf::Vector2f(entity_json["bulk"][0],entity_json["bulk"][1]);
    Moveable* moveable=Moveable::create_from_json(entity_json["moveable"]);
    Entity_factory* entity_factory=Entity_factory::create_from_json(entity_json["entity_factory"]);
    Strategy* strategy=Strategy::create_from_json(entity_json["strategy"]);
    Skill* skill=Skill::create_from_json(entity_json["skill"]);
    Entity* new_entity =new Entity(entity_faction,entity_type,texture,position,bulk,max_health,moveable,entity_factory,strategy,skill);
    return new_entity;
}


