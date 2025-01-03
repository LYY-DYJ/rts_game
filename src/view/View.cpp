#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Model.hpp"
#include "View.hpp"

void View::update_sprites(const std::vector<Entity> &entities)
{
    for (const Entity &entity : entities)
    {
        sf::Texture texture;
        if (texture.loadFromFile("img/"+entity.texture))
        {
            sf::Sprite sprite;
            entity_texture[entity.texture] = texture;
            sprite.setTexture(entity_texture[entity.texture]);
            sprite.setPosition(entity.moveable->position);
            sprite.setScale(sf::Vector2f(0.2, 0.2));
            entity_sprites[entity.id] = sprite;
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
    draw_entities();
    window->display();
}

void View::draw_entities()
{
    update_sprites(model->entity_vector());
    for (const auto &[id, sprite] : entity_sprites)
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
