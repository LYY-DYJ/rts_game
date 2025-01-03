#include<SFML/Graphics.hpp>
#include"Model.hpp"

Model::Model(int map_w,int map_h):map(map_w,map_h)
{
    id_max=0;
    void add_unit(std::string type, sf::Vector2f pos, int hp, int spd, int atk);
}

void Model::add_unit(std::string type, sf::Vector2f pos, int hp, int spd, int atk)
{
    int id=id_max;
    id_max++;
    units[id]=Unit(id,type,pos,hp,spd,atk);
}

std::vector<Unit> Model::units_vector()
{
    std::vector<Unit> uv;
    for(auto& [id, unit] : units)
    {
        uv.push_back(unit);
    }
    return uv;
}