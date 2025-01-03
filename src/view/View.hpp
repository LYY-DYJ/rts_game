#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Model.hpp"

class View
{
private:
    sf::View main_view;
    float move_speed;
    float zoom_rate;
    std::unordered_map<std::string, sf::Texture> entity_texture;
    std::unordered_map<int, sf::Sprite> entity_sprites;

    // 更新每个unit的图形
    void update_sprites(const std::vector<Entity> &units);
    
public:
    sf::RenderWindow* window;
    Model* model;
    View(Model* model,sf::RenderWindow* window);

    void draw_all();
    // 画每个unit
    void draw_entities();
    // 移动主视角
    void main_view_move(int x,int y);
    // 缩放主视角
    void main_view_zoom(int r);
};
#endif