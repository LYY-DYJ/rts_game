#include <SFML/Graphics.hpp>
#include "View.hpp"
#include "Model.hpp"
class Controller {
public:
    Controller(sf::RenderWindow* window,Model* model,View* view);

    void handleInput();

private:
    sf::RenderWindow* window;
    Model* model;
    View* view;
    int border_size;
    void view_move(sf::Vector2i mouse_position);
    void view_zoom(float delta);
};