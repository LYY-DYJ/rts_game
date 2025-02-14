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

void View::draw_group(Order_group* group)
{
    if(group==nullptr)
        return;
    if(group_id!=Order_group::group_id)
    {
        entities_group_sign.clear();
    }
    group_id=Order_group::group_id;
    update_group_sign(group);
    if(group->is_setting)
    {
        group_rect=sf::RectangleShape(group->end_point-group->begin_point);
        group_rect.setPosition(group->begin_point);
        group_rect.setFillColor(sf::Color(0,0,255,100));
        group_rect.setOutlineColor(sf::Color(0,0,255));
        group_rect.setOutlineThickness(1);
        window->draw(group_rect);
    }
    for (const int &i : model->erase_vector)
        if(entities_group_sign.count(i))
            entities_group_sign.erase(i);
    for (const auto &[id, group_rect] : entities_group_sign)
    {
        window->draw(group_rect);
    }
}

void View::update_group_sign(Order_group* group)
{
    std::vector<Entity*> grouped_entities=group->get_group(model);
    for(Entity* entity:grouped_entities)
    {
        sf::RectangleShape group_sign=sf::RectangleShape(entity->bulk);
        group_sign.setOrigin(0.5f*group_sign.getLocalBounds().width,0.5f*group_sign.getLocalBounds().height);
        group_sign.setPosition(entity->position);
        group_sign.setFillColor(sf::Color(0,0,0,0));
        group_sign.setOutlineColor(sf::Color(0,0,255));
        group_sign.setOutlineThickness(1);
        entities_group_sign[entity->id]=group_sign;
    }

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
            sf::Sprite sprite;
            textures[entity->texture] = texture;
            sprite.setTexture(textures[entity->texture]);
            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
            sprite.setScale(sf::Vector2f(entity->bulk.x / texture.getSize().x, entity->bulk.y / texture.getSize().y));
            sprite.setPosition(entity->position);
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
    health_bar.setOrigin(health_bar_length/2,0);
    health_bar.setPosition(entity->position+sf::Vector2f(0,0.5*entity->bulk.y));
    health_bar.setFillColor(sf::Color::Red);
    entities_health_bar[entity->id] = health_bar;
}

void View::update_max_health_bar(const Entity *entity)
{
    float health_bar_width = 5;
    float health_bar_length = 50;
    float out_line_width = 1;
    sf::RectangleShape max_health_bar(sf::Vector2f(health_bar_length, health_bar_width));
    max_health_bar.setOrigin(health_bar_length/2,0);
    max_health_bar.setPosition(entity->position+sf::Vector2f(0,0.5*entity->bulk.y));
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
    main_view_size = main_view.getSize();
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
    draw_group(model->group);
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
    if (r > 0 && zoom_factor > zoom_rate)
    {
        zoom_factor -= zoom_rate;
        main_view.setSize(main_view_size * zoom_factor);
        text.setCharacterSize(50 / zoom_factor);
        text.setScale(1 - zoom_rate, 1 - zoom_rate);
    }
    else if (r < 0)
    {
        zoom_factor += zoom_rate;
        main_view.setSize(main_view_size * zoom_factor);
        text.setCharacterSize(50 / zoom_factor);
        text.setScale(1 + zoom_rate, 1 + zoom_rate);
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
