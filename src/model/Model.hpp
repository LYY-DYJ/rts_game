#ifndef MODEL_H
#define MODEL_H
#include<unordered_map>
#include<Map.hpp>
#include<Resource.hpp>
#include<Unit.hpp>

class Model
{
public:
    int id_max;
    Map map;
    std::unordered_map<int,Unit> units;
    Model(int map_w,int map_h);
    void add_unit(std::string type, sf::Vector2f pos, int hp, int spd, int atk);
    std::vector<Unit> units_vector();
};
#endif