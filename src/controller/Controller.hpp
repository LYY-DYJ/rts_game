#include <SFML/Graphics.hpp>
#include <vector>
#include <nlohmann/json.hpp>
#include "View.hpp"
#include "Model.hpp"

using json=nlohmann::json;

class Controller {
public:
    Controller(sf::RenderWindow* window,Model* model,View* view);

    void run();
    bool game_is_paused;
    bool game_over;
    void rts_game_initialize(std::string rts_json_file);
    int add_entity_from_json(json entity_json);

private:
    sf::RenderWindow* window;
    Model* model;
    View* view;
    std::unordered_map<int,int> base_id_faction;
    int border_size;
    int losed_faction;
    void view_move(sf::Vector2i mouse_position);
    void view_zoom(float delta);
    void handleInput();
    void check_game_status();
    int who_lose();
};