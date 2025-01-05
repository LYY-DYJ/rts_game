#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

Controller::Controller(sf::RenderWindow *w, Model *m, View *v)
{
    window = w;
    model = m;
    view = v;
    border_size = 20;
    game_is_paused = 0;
    game_over=0;
}

void Controller::run()
{
    handleInput();
    check_game_status();
}

void Controller::check_game_status()
{
    int lose_faction=who_lose();
    if(lose_faction>0)
    {
        losed_faction=lose_faction;
        game_over=true;
    }
}

int Controller::who_lose()
{
    for(auto [id,faction]:base_id_faction)
    {
        if(model->entities.count(id)==0)
        {
            int lose_faction=base_id_faction[id];
            base_id_faction.erase(id);
            return lose_faction;
        }
    }
    return -1;
}


void Controller::view_move(sf::Vector2i mouse_position)
{
    sf::Vector2u window_size = window->getSize();
    float left_border = static_cast<float>(border_size);
    float right_border = static_cast<float>(window_size.x - border_size);
    float top_border = static_cast<float>(border_size);
    float bottom_border = static_cast<float>(window_size.y - border_size);
    int x = mouse_position.x < left_border ? -1 : mouse_position.x > right_border ? 1
                                                                                  : 0;
    int y = mouse_position.y < top_border ? -1 : mouse_position.y > bottom_border ? 1
                                                                                  : 0;
    if (x != 0 || y != 0)
        view->main_view_move(x, y);
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
            Entity *closest_entity = model->entity_closest(worldPos, 50);
            if (closest_entity != nullptr)
            {
                int target_id = closest_entity->id;
                model->attack(target_id);
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                game_is_paused = !game_is_paused;
            }
        }
    }
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
    view_move(mouse_position);
    if(game_over)
        view->add_text_to_display(std::to_string(losed_faction)+" Losed");
    else if (game_is_paused)
        view->add_text_to_display("Game Paused");
    else 
        view->add_text_to_display("");
}

using json = nlohmann::json;

void Controller::rts_game_initialize(std::string rts_json_file)
{
    std::ifstream file(rts_json_file);
    std::string jsonStr;
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            jsonStr += line; // 将每一行添加到 jsonStr 中
        }
        file.close();
    }
    else
    {
        std::cerr << "Can't open rts_json_file" << std::endl;
    }

    json json_info = nlohmann::json::parse(jsonStr);
    for (const auto &base_json : json_info["base"])
    {
        std::cout << base_json << std::endl;
        int id=model->add_base(
        Entity::create_from_json(base_json));
        int faction=base_json["faction"];
        base_id_faction[id]=faction;
    }
    for (const auto &entity_json : json_info["entities"])
    {
        std::cout << entity_json << std::endl;
        model->add_entity(
        Entity::create_from_json(entity_json));
    }
}
