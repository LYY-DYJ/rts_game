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
    float zoom_factor = 1.0f;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<int, sf::Sprite> entity_sprites;
    std::unordered_map<int, sf::RectangleShape> entities_health_bar;
    std::unordered_map<int, sf::RectangleShape> entities_max_health_bar;
    std::unordered_map<int, sf::CircleShape> entities_position_circle;
    std::string text_to_display;
    sf::Font font;
    sf::Text text;
    sf::Vector2f main_view_size;
    sf::Vector2i text_position;

public:
    sf::RenderWindow* window;
    Model* model;
    View(Model* model,sf::RenderWindow* window);

    // 更新每个unit的图形
    void update_sprites(const std::vector<Entity*> entities,const std::vector<int> erase_list);

    void update_entity_position_circle(const Entity* entity);

    void update_health_bar(const Entity* entity);

    void update_max_health_bar(const Entity* entity);

    void erase_id(int id);
    
    void add_text_to_display(std::string text);

    void draw_text();

    void draw_all();
    // 画每个entity
    void draw_entities();
    // 移动主视角
    void main_view_move(int x,int y);
    // 缩放主视角
    void main_view_zoom(int r);
};

class Actor
{
    
};

#endif