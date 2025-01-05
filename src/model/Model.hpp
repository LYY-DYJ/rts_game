#ifndef MODEL_H
#define MODEL_H
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <queue>
#include <stack>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Utils.hpp"

using json = nlohmann::json;

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
    std::unordered_map<int, Entity *> entities; // Model doesn't create entity but hold it and delete it
    std::queue<Model_event *> events_queue;
    std::queue<Model_event *> events_wait_queue;
    std::unordered_map<int, int> base_faction_id;
    Model();
    ~Model();
    int add_entity(Entity *entity);
    int add_base(Entity *entity);
    void attack(int id);
    std::vector<Entity *> entity_vector();
    std::vector<Entity *> entity_in_range(sf::Vector2f point, float range);
    Entity *entity_closest(sf::Vector2f point, float range);
    std::vector<Entity *> entity_in_sight(sf::Vector2f point, float range);
    bool is_way_blocked(sf::Vector2f position1,sf::Vector2f position2);
    void entities_act();
    void settle_event();
    void update();
};

class Model_event
{
public:
    virtual bool settle(Model *) = 0;
};

class Normal_attack_event : public Model_event
{
public:
    int id;
    int attack;
    Normal_attack_event(int id, int attack);
    bool settle(Model *);
};

class Reset_idle_event : public Model_event
{
public:
    int id;
    sf::Time duration = sf::milliseconds(300);
    sf::Clock clk;
    Reset_idle_event(int id);
    bool settle(Model *);
};

enum Entity_type
{
    UNIT,
    BUILDING,
    MOUNTAIN,
    RIVER
};

enum Entity_state
{
    IDLE,
    ATTACKTED
};

class Entity
{
public:
    int id;
    int faction;
    Entity_type entity_type;
    std::string texture;
    sf::Vector2f position;
    sf::Vector2f bulk;
    int max_health;
    int curr_health;
    float sight;
    Entity_state entity_state;
    Model *model;
    Moveable *moveable;
    Entity_factory *entity_factory;
    Strategy *strategy;
    Skill *skill;
    Entity();
    Entity(const Entity &);
    ~Entity();

    Entity(int faction, Entity_type entity_type, std::string texture, sf::Vector2f position, sf::Vector2f bulk, int max_health,float sight, Moveable *moveable, Entity_factory *entity_factory, Strategy *strategy, Skill *skill);
    void operator=(Entity &);
    void set_id(int id);
    void act();
    std::vector<Entity *> look_around();
    sf::Vector2f enemy_base_position();

    static Entity_type str2entity_type(std::string);
    static Entity *create_from_json(json enitity_json);
};

enum Move_type
{
    NO_MOVE,
    WALK
};

class Moveable
{
public:
    Move_type move_type;
    Moveable();
    virtual Moveable *clone() = 0;
    virtual void move(Entity *owner, sf::Vector2f direction) = 0;
    static Moveable *create_from_json(json moveable_json);
};

class No_move : public Moveable
{
public:
    No_move();
    Moveable *clone();
    void move(Entity *owner, sf::Vector2f direction);
};

class Walk : public Moveable
{
public:
    float speed;
    Walk(float speed);
    Moveable *clone();
    void move(Entity *owner, sf::Vector2f direction);
};

class Entity_factory
{
public:
    sf::Vector2f relative_position;
    bool entity_factory_type;
    ~Entity_factory() {};
    int entity_num;
    virtual Entity_factory *clone() = 0;
    virtual void add_entity(const Entity *) = 0;
    virtual void generate(Entity *owner, int i) = 0;
    static Entity_factory *create_from_json(json entity_factory_json);
};

class False_entity_factory : public Entity_factory
{
public:
    False_entity_factory();
    Entity_factory *clone();
    void add_entity(const Entity *) {};
    void generate(Entity *owner, int i) {};
};

class True_entity_factory : public Entity_factory
{
public:
    std::vector<Entity *> produceable_entity; // True_entity_factory's Enitity is created by True_entity_factory and hold by itself
    True_entity_factory();
    Entity_factory *clone();
    void add_entity(const Entity *);
    void generate(Entity *owner, int i); // new a Enitity and provide for model
};

class Strategy
{
public:
    virtual void reset() = 0;
    virtual Strategy *clone() = 0;
    virtual void control(Entity *entity) = 0;
    ~Strategy() {};
    static Strategy *create_from_json(json strategy_json);
};

class No_strategy : public Strategy
{
public:
    No_strategy() {};
    void reset() {};
    Strategy *clone();
    void control(Entity *entity) {};
};

class Random_strategy : public Strategy
{
private:
    bool initial = true;
    sf::Time refresh_gap;
    sf::Clock clk;
    sf::Vector2f direction;

public:
    Random_strategy(int refresh_gap_as_millsec);
    void reset();
    Strategy *clone();
    void control(Entity *entity);
};

enum Behavior_pattern
{
    WAIT,
    WALK_TO_DESTINATION,
    FIND_ENEMY,
    ATTACKING,
    BY_PASS_BLOCK,
};

class Normal_strategy : public Strategy
{
private:
    std::stack<Behavior_pattern> behavior_pattern_stack;
    bool initial;

public:
    bool is_destination_available;
    sf::Vector2f destination;
    Normal_strategy();
    void reset();
    Strategy *clone();
    void control(Entity *entity);
};

enum Skill_type
{
    ATTACK,
    NO_SKILL
};

class Skill
{
public:
    Skill_type skill_type;
    float range;
    virtual Skill *clone() = 0;
    virtual void release(Entity *owner) = 0;
    static Skill *create_from_json(json skill_json);
};

class No_skill : public Skill
{
public:
    No_skill();
    Skill *clone();
    void release(Entity *owner) {};
};

class Normal_attack : public Skill
{
public:
    sf::Clock clk;
    bool available;
    float cd_time; // as millisecond
    int attack;

    Normal_attack(float cd_time, float range, int attack);
    Skill *clone();
    void reset();
    void release(Entity *owner);
};

#endif