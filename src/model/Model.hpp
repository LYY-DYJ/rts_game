#ifndef MODEL_H
#define MODEL_H
#include<unordered_map>
class Model;
class Entity_factory;

enum Move_type{no_move,walk};

class Moveable
{
public:
    Move_type move_type;
    sf::Vector2f position;
    float speed;
    Moveable();
    virtual void move(sf::Vector2f direction)=0;
};

class No_move:public Moveable
{
public:
    No_move(sf::Vector2f position);
    void move(sf::Vector2f direction);
};

class Walk:public Moveable
{
public:
    Walk(sf::Vector2f position,float speed);
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
    Entity();
    Entity(int id,std::string texture,Moveable* moveable);
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
    ~Entity_factory(){};
    virtual void generate(int i)=0;
};

class False_entity_factory:public Entity_factory
{
    False_entity_factory();
    void generate(int i){};
};

class True_entity_factory:public Entity_factory
{
public:
    Model* model;
    std::vector<Entity> produceable_entity;
    sf::Vector2f produce_position;
    True_entity_factory(Model* model);
    void add_entity(Entity);
    void generate(int i);
};

#endif