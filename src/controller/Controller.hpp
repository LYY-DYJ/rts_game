#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#include "View.hpp"
#include "Model.hpp"

using json=nlohmann::json;

class Controller {
public:
    Controller(sf::RenderWindow* window,Model* model,View* view);

    void handleInput();

    void rts_game_initialize(std::string rts_json_file);
    void add_entity_from_json(json entity_json);

private:
    sf::RenderWindow* window;
    Model* model;
    View* view;
    std::vector<int> base_id;
    int border_size;
    void view_move(sf::Vector2i mouse_position);
    void view_zoom(float delta);
};