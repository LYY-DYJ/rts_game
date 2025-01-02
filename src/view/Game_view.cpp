#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Model.hpp"
#include "Game_view.hpp"

void Game_view::updateSprites(const std::vector<Unit> &units)
{
    for (const Unit &unit : units)
    {
        sf::Texture texture;
        if (texture.loadFromFile("img/"+unit.texture))
        {
            sf::Sprite sprite;
            unit_texture[unit.id] = texture;
            sprite.setTexture(unit_texture[unit.id]);
            sprite.setPosition(unit.position);
            sprite.setScale(sf::Vector2f(0.2, 0.2));
            unit_sprites[unit.id] = sprite;
        }
        else 
            return;
    }
}

void Game_view::render()
{
    window.clear(sf::Color::White);
    for (const auto &[id, sprite] : unit_sprites)
    {
        window.draw(sprite);
    }
    window.display();
}

Game_view::Game_view() : window(sf::VideoMode::getDesktopMode(), "RTS Game")
{
}

void Game_view::drawUnits(const std::vector<Unit> &units)
{
    updateSprites(units);
    render();
}

void Game_view::close()
{
    window.close();
}

bool Game_view::isOpen() const
{
    return window.isOpen();
}

bool Game_view::pollEvent(sf::Event &event)
{
    return window.pollEvent(event);
}
