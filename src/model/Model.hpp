#ifndef MODEL_H
#define MODEL_H
#include<unordered_map>
#include<queue>
#include<SFML/Graphics.hpp>


class Model;
class Model_event;
class Entity;
class Entity_factory;
class Moveable;
class Strategy;
class Skill;

class Model
{
public:
    int id_max;
    std::vector<int> erase_vector;
    std::unordered_map<int,Entity> entities;
    std::queue<Model_event*> events_queue;
    std::queue<Model_event*> events_wait_queue;
    Model();
    void add_entity(Entity entity);
    void attack(int id);
    std::vector<Entity> entity_vector();
    std::vector<Entity> entity_in_range(sf::Vector2f point,float range);
    Entity* entity_closest(sf::Vector2f point,float range);
    void entities_act();
    void settle_event();
    void update();
};

class Model_event
{
public:
    virtual bool settle(Model*)=0;
};

class Normal_attack_event:public Model_event
{
public:
    int id;
    int attack;
    Normal_attack_event(int id,int attack);
    bool settle(Model*);
};

class Reset_idle_event:public Model_event
{
public:
    int id;
    sf::Time duration=sf::milliseconds(300);
    sf::Clock clk;
    Reset_idle_event(int id);
    bool settle(Model*);
};

enum Entity_type{UNIT,BUILDING,TERRAIN};

enum Entity_state{IDLE,ATTACKTED};

class Entity
{
public:
    int id;
    Entity_type entity_type;
    std::string texture;
    int health;    
    Entity_state entity_state;
    Model* model;
    Moveable* moveable;
    Entity_factory* entity_factory;
    Strategy* strategy;
    Skill* skill;
    Entity();
    Entity(const Entity&);
    ~Entity();
    Entity(int id,Entity_type entity_type,std::string texture,Model* model,Moveable* moveable,Entity_factory* entity_factory,Strategy* strategy);
    void operator=(Entity&);
    void set_id(int id);
    void act();
};

enum Move_type{NO_MOVE,WALK};

class Moveable
{
public:
    Move_type move_type;
    sf::Vector2f position;
    float speed;
    Moveable();
    virtual Moveable* clone()=0;
    virtual void move(sf::Vector2f direction)=0;

};

class No_move:public Moveable
{
public:
    No_move(sf::Vector2f position);
    Moveable* clone();
    void move(sf::Vector2f direction);
};

class Walk:public Moveable
{
public:
    Walk(sf::Vector2f position,float speed);
    Moveable* clone();
    void move(sf::Vector2f direction);
};

class Entity_factory
{
public:
    sf::Vector2f relative_position;
    bool entity_factory_type;
    ~Entity_factory(){};
    int entity_num;
    virtual Entity_factory* clone()=0;
    virtual void add_entity(const Entity&)=0;
    virtual void generate(int i,sf::Vector2f owner_postion)=0;
};

class False_entity_factory:public Entity_factory
{
public:
    False_entity_factory();
    Entity_factory* clone();
    void add_entity(const Entity&){};
    void generate(int i,sf::Vector2f owner_postion){};
};

class True_entity_factory:public Entity_factory
{
public:
    Model* model;
    std::vector<Entity> produceable_entity;
    True_entity_factory(Model* model);
    Entity_factory* clone();
    void add_entity(const Entity&);
    void generate(int i,sf::Vector2f owner_postion);
};

class Strategy
{
public:
    virtual void reset()=0;
    virtual Strategy* clone()=0;
    virtual void control(Entity* entity)=0;
    ~Strategy(){};
};

class No_strategy:public Strategy
{
public:
    No_strategy(){};
    void reset(){};
    Strategy* clone();
    void control(Entity* entity){};
};

class Random_strategy: public Strategy
{
private:
    bool initial=true;
    sf::Time refresh_gap;
    sf::Clock clk;
    sf::Vector2f direction;
public:
    Random_strategy(int refresh_gap_as_millsec);
    void reset();
    Strategy* clone();
    void control(Entity* entity);
};

class Skill
{
public:
    virtual Skill* clone()=0;
    virtual void release(Entity*)=0;
};

class No_skill:Skill
{
public:
    No_skill(){};
    Skill* clone();
    void release(Entity*){};
};

class Normal_attack:Skill
{
public:
    sf::Clock clk;
    bool available;
    float cd_time;//as millisecond
    float range;
    int attack;

    Normal_attack(float cd_time,float range,int attack);
    Skill* clone();
    void reset();
    void release(Entity*);
};

#endif