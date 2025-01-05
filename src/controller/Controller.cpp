#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

using json = nlohmann::json;

Controller::Controller(sf::RenderWindow *w,Model* m,View* v)
{
    window = w;
    model = m;
    view=v;
    border_size=20;
}

void Controller::view_move(sf::Vector2i mouse_position)
{
    sf::Vector2u window_size = window->getSize();
    float left_border = static_cast<float>(border_size);
    float right_border = static_cast<float>(window_size.x - border_size);
    float top_border = static_cast<float>(border_size);
    float bottom_border = static_cast<float>(window_size.y - border_size);
    int x=mouse_position.x<left_border?-1:mouse_position.x>right_border?1:0;
    int y=mouse_position.y<top_border?-1:mouse_position.y>bottom_border?1:0;
    if(x!=0||y!=0)
        view->main_view_move(x,y);
}

void Controller::view_zoom(float delta)
{
    view->main_view_zoom(delta);
}

void Controller::handleInput()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            view_zoom(event.mouseWheelScroll.delta);
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
            sf::Vector2f worldPos = window->mapPixelToCoords(mouse_position);
            Entity* closest_entity=model->entity_closest(worldPos,50);
            if(closest_entity!=nullptr)
            {
                int target_id=closest_entity->id;
                model->attack(target_id);
            }
        }
    }
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
    view_move(mouse_position);

}

