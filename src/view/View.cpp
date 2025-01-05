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

void View::update_sprites(const std::vector<Entity *> entities, const std::vector<int> erase_vector)
{
    for (const int &i : erase_vector)
    {
        erase_id(i);
    }
    for (const Entity *entity : entities)
    {
        sf::Texture texture;
        if (textures.count("img/" + entity->texture) || texture.loadFromFile("img/" + entity->texture))
        {
            sf::Vector2f display_size(50, 50);
            sf::Sprite sprite;
            textures[entity->texture] = texture;
            sprite.setTexture(textures[entity->texture]);
            sprite.setScale(sf::Vector2f(display_size.x / texture.getSize().x, display_size.y / texture.getSize().y));
            sf::Vector2f sprite_scale = sprite.getScale();
            sprite.setPosition(entity->position - sf::Vector2f(25, 25));
            update_entity_position_circle(entity);
            if (entity->entity_state == ATTACKTED)
                sprite.setColor(sf::Color(255, 128, 128));
            if (entity->entity_type == UNIT || entity->entity_type == BUILDING)
            {
                update_health_bar(entity);
                update_max_health_bar(entity);
            }
            entity_sprites[entity->id] = sprite;
        }
        else
            return;
    }
}

void View::update_health_bar(const Entity *entity)
{
    float health_bar_width = 5;
    float health_bar_length = 50;
    float health_ratio = float(entity->curr_health) / float(entity->max_health);
    sf::RectangleShape health_bar(sf::Vector2f(health_bar_length * health_ratio, health_bar_width));
    health_bar.setPosition(sf::Vector2f(-25, 25) + entity->position);
    health_bar.setFillColor(sf::Color::Red);
    entities_health_bar[entity->id] = health_bar;
}

void View::update_max_health_bar(const Entity *entity)
{
    float health_bar_width = 5;
    float health_bar_length = 50;
    float out_line_width = 1;
    sf::RectangleShape max_health_bar(sf::Vector2f(health_bar_length, health_bar_width));
    max_health_bar.setPosition(sf::Vector2f(-25, 25) + entity->position);
    max_health_bar.setFillColor(sf::Color(200, 200, 200));
    max_health_bar.setOutlineColor(sf::Color::Black);
    max_health_bar.setOutlineThickness(out_line_width);
    entities_max_health_bar[entity->id] = max_health_bar;
}

void View::update_entity_position_circle(const Entity *entity)
{
    float circle_radius = 5;
    sf::CircleShape position_circle(circle_radius);
    position_circle.setPosition(entity->position);
    position_circle.setFillColor(sf::Color(100, 100, 100));
    entities_position_circle[entity->id] = position_circle;
}

View::View(Model *m, sf::RenderWindow *w) : model(m), window(w), move_speed(10), main_view(sf::FloatRect(0.f, 0.f, 800.f, 450.f)), zoom_rate(0.02)
{
    main_view_size=main_view.getSize();
    if (!font.loadFromFile("font/BAUHS93.TTF"))
    {
        std::cerr << "Could not load font" << std::endl;
    }
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Black);
    text.setFont(font);
    sf::FloatRect textRect = text.getLocalBounds();
    text_position = sf::Vector2i(main_view.getSize()) - 2 * sf::Vector2i(textRect.width, textRect.height);
}

void View::draw_all()
{
    window->setView(main_view);
    window->clear(sf::Color::White);
    draw_entities();
    draw_text();
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
    if (r > 0&&zoom_factor>zoom_rate)
    {
        zoom_factor -= zoom_rate;
        main_view.setSize(main_view_size*zoom_factor);
        text.setCharacterSize(50 / zoom_factor);
        text.setScale(1-zoom_rate,1-zoom_rate);
    }
    else if (r < 0)
    {
        zoom_factor += zoom_rate;
        main_view.setSize(main_view_size*zoom_factor);
        text.setCharacterSize(50 / zoom_factor);
        text.setScale(1+zoom_rate,1+zoom_rate);
    }
}

void View::add_text_to_display(std::string text)
{
    text_to_display = text;
}

void View::draw_text()
{
    text.setPosition(window->mapPixelToCoords(text_position));
    text.setString(text_to_display);
    window->draw(text);
}
