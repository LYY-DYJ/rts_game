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
    void view_move(sf::Vector2i mouse_position);
    
};