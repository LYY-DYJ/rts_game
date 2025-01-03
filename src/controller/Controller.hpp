#include <SFML/Graphics.hpp>
#include "View.hpp"
#include "Model.hpp"
class Controller {
public:
    Controller(sf::Window* window,View* view);

    void handleInput();

private:
    sf::Window* window;
    View* view;
    int border_size;
    void view_move(sf::Vector2i mouse_position);
    void view_zoom(float delta);
};