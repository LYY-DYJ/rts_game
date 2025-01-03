#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Model.hpp"
#include "View.hpp"

void View::update_sprites(const std::vector<Unit> &units)
{
    for (const Unit &unit : units)
    {
        sf::Texture texture;
        if (texture.loadFromFile("img/"+unit.texture))
        {
            sf::Sprite sprite;
            unit_texture[unit.texture] = texture;
            sprite.setTexture(unit_texture[unit.texture]);
            sprite.setPosition(unit.position);
            sprite.setScale(sf::Vector2f(0.2, 0.2));
            unit_sprites[unit.id] = sprite;
        }
        else 
            return;
    }
}

View::View(Model* m,sf::RenderWindow* w) :model(m), window(w),move_speed(2),main_view(sf::FloatRect(0.f, 0.f, 800.f, 450.f)),zoom_rate(1.05)
{
}

void View::draw_all()
{
    window->setView(main_view);
    window->clear(sf::Color::White);
    draw_units();
    window->display();
}

void View::draw_units()
{
    update_sprites(model->units_vector());
    for (const auto &[id, sprite] : unit_sprites)
    {
        window->draw(sprite);
    }
}

void View::main_view_move(int x,int y)
{
    main_view.move(move_speed*x,move_speed*y);
}

void View::main_view_zoom(int r)
{
    if(r>0)
    {
        main_view.zoom(1/zoom_rate);
    }
    else if(r<0)
    {
        main_view.zoom(zoom_rate);
    }
}
