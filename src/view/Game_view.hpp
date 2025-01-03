#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Model.hpp"

class Game_view
{
private:
    std::unordered_map<std::string, sf::Texture> unit_texture;
    std::unordered_map<int, sf::Sprite> unit_sprites;

    // 更新每个unit的图形
    void updateSprites(const std::vector<Unit> &units);

    // 渲染所有unit的图形
    void render();

public:
    sf::RenderWindow window;
    Model* model;
    Game_view(Model* model);

    // 画每个unit
    void drawUnits();

    bool isOpen() const;
    void close();
    bool pollEvent(sf::Event &event);
};
#endif