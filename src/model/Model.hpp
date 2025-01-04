#ifndef MODEL_H
#define MODEL_H
#include<unordered_map>
#include<SFML/Graphics.hpp>
class Model;
class Entity_factory;
class Strategy;

enum Move_type{no_move,walk};

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

class Entity
{
public:
    Model* model;
    int id;
    std::string texture;
    Moveable* moveable;
    Entity_factory* entity_factory;
    Strategy* strategy;
    Entity();
    Entity(const Entity&);
    ~Entity();
    Entity(int id,std::string texture,Moveable* moveable,Entity_factory* entity_factory,Strategy* strategy);
    void operator=(Entity&);
    void set_id(int id);
    void act();
};

class Model
{
public:
    int id_max;
    std::unordered_map<int,Entity> entities;
    Model();
    void add_entity(Entity entity);
    std::vector<Entity> entity_vector();
    void update();
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
    virtual void release()=0;
};

class No_skill:Skill
{
public:
    No_skill(){};
    Skill* clone();
    void release(){};
};

class Normal_attack:Skill
{
public:
    float cd_time;//as millisecond
    float range;
    
};
#endif