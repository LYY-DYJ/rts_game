#include<SFML/Graphics.hpp>
#include"Model.hpp"

Moveable::Moveable()
{
    move_type=NO_MOVE;
}

Moveable* Moveable::create_from_json(json moveable_json)
{
    if (moveable_json.contains("move_type")) {
        std::string move_type = moveable_json["move_type"];
        if (move_type == "NO_MOVE") {
            return new No_move();
        } else if (move_type == "WALK") {
            float speed = moveable_json["speed"];
            return new Walk(speed);
        }
    }
    throw std::runtime_error("Invalid move type");
}

No_move::No_move()
{
    move_type=NO_MOVE;
}
Moveable* No_move::clone()
{
    Moveable* new_moveable;
    new_moveable = new No_move(*this);
    return new_moveable;
}
void No_move::move(Entity* entity,sf::Vector2f direction){}

Walk::Walk(float spd)
{
    move_type=WALK;
    speed=spd;
}

Moveable* Walk::clone()
{
    Moveable* new_moveable;
    new_moveable = new Walk(*this);
    return new_moveable;
}

void Walk::move(Entity* entity,sf::Vector2f direction)
{
    entity->position+=direction*speed;
}