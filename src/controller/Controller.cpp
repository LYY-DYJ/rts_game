#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

Controller::Controller(sf::Window *w,View* v)
{
    window = w;
    view=v;
}

void Controller::view_move(sf::Vector2i mouse_position)
{
    int border_size = 10;
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

void Controller::handleInput()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
    view_move(mouse_position);

}