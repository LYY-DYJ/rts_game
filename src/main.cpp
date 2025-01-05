#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600,900),"RTS Game");
    window.setFramerateLimit(60);
    Model model;
    View view(&model,&window);
    Controller controller(&window,&model,&view);
    
    controller.rts_game_initialize("content/rts_game.json");

    while (window.isOpen())
    {
        controller.run();
        if(!(controller.game_is_paused||controller.game_over))
        {
            model.update();
        }
        view.draw_all();
    }

    return 0;
}
