#ifndef UNIT_H
#define UNIT_H
#include <SFML/Graphics.hpp>
// 定义一个单位类
class Unit
{
public:
    int id;
    std::string texture;
    sf::Vector2f position;
    int health;
    float speed;
    int attackPower;

    Unit(int id, std::string type, sf::Vector2f pos, int hp, int spd, int atk);

    // 移动单位
    void move(sf::Vector2f direction);

    // 绘制单位
    void draw(sf::RenderWindow &window);
};
#endif