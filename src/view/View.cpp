#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "Model.hpp"
#include "View.hpp"

void View::erase_id(int id)
{
    entity_sprites.erase(id);
    entities_health_bar.erase(id);
    entities_max_health_bar.erase(id);
    entities_position_circle.erase(id);
}

void View::update_sprites(const std::vector<Entity> &entities, const std::vector<int> erase_vector)
{
    for (const int &i : erase_vector)
    {
        erase_id(i);
    }
    for (const Entity &entity : entities)
    {
        sf::Texture texture;
        if (texture.loadFromFile("img/" + entity.texture))
        {
            sf::Sprite sprite;
            textures[entity.texture] = texture;
            sprite.setTexture(textures[entity.texture]);
            sprite.setScale(sf::Vector2f(0.2, 0.2));
            sf::Vector2f sprite_scale = sprite.getScale();
            sprite.setPosition(entity.moveable->position-sf::Vector2f(25,25));
            update_entity_position_circle(entity);
            if (entity.entity_state == ATTACKTED)
                sprite.setColor(sf::Color(255, 128, 128));
            if (entity.entity_type == UNIT || entity.entity_type == BUILDING)
            {
                update_health_bar(entity);
                update_max_health_bar(entity);
            }
            entity_sprites[entity.id] = sprite;
        }
        else
            return;
    }
}

void View::update_health_bar(const Entity &entity)
{
    float health_bar_width = 5;
    float health_bar_length = 50;
    float health_ratio = float(entity.curr_health) / float(entity.max_health);
    sf::RectangleShape health_bar(sf::Vector2f(health_bar_length * health_ratio, health_bar_width));
    health_bar.setPosition(sf::Vector2f(0, 100) + entity.moveable->position);
    health_bar.setFillColor(sf::Color::Red);
    entities_health_bar[entity.id] = health_bar;
}

void View::update_max_health_bar(const Entity & entity)
{
    float health_bar_width = 5;
    float health_bar_length = 50;
    float out_line_width= 1;
    sf::RectangleShape max_health_bar(sf::Vector2f(health_bar_length,health_bar_width));
    max_health_bar.setPosition(sf::Vector2f(0, 100) + entity.moveable->position);
    max_health_bar.setFillColor(sf::Color(200,200,200));
    max_health_bar.setOutlineColor(sf::Color::Black);
    max_health_bar.setOutlineThickness(out_line_width);
    entities_max_health_bar[entity.id] = max_health_bar;
}

void View::update_entity_position_circle(const Entity& entity)
{
    float circle_radius=5;
    sf::CircleShape position_circle(circle_radius);
    position_circle.setPosition(entity.moveable->position);
    position_circle.setFillColor(sf::Color(100,100,100));
    entities_position_circle[entity.id] = position_circle;
}

View::View(Model *m, sf::RenderWindow *w) : model(m), window(w), move_speed(2), main_view(sf::FloatRect(0.f, 0.f, 800.f, 450.f)), zoom_rate(1.05)
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
    update_sprites(model->entity_vector(), model->erase_vector);
    for (const auto &[id, sprite] : entity_sprites)
    {
        window->draw(sprite);
    }
    for (const auto &[id, max_health_bar] : entities_max_health_bar)
    {
        window->draw(max_health_bar);
    }
    for (const auto &[id, health_bar] : entities_health_bar)
    {
        window->draw(health_bar);
    }
    for (const auto &[id, circle] : entities_position_circle)
    {
        window->draw(circle);
    }
}

void View::main_view_move(int x, int y)
{
    main_view.move(move_speed * x, move_speed * y);
}

void View::main_view_zoom(int r)
{
    if (r > 0)
    {
        main_view.zoom(1 / zoom_rate);
    }
    else if (r < 0)
    {
        main_view.zoom(zoom_rate);
    }
}
