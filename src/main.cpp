#include <SFML/Graphics.hpp>
#include <Model.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "RTS Game");
    window.setFramerateLimit(60);

    // 初始化地图
    Map map(800, 600);

    // 初始化一些单位
    std::vector<Unit> units;
    units.push_back(Unit(sf::Vector2f(50, 50), 100, 5, 10));
    units.push_back(Unit(sf::Vector2f(150, 150), 120, 4, 12));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 处理单位的移动，这里只是简单地向右移动
        for (Unit& unit : units) {
            unit.move(sf::Vector2f(1, 0));
        }

        // 清除窗口
        window.clear();

        // 绘制地图
        map.draw(window);

        // 绘制单位
        for (Unit& unit : units) {
            unit.draw(window);
        }

        // 显示绘制的内容
        window.display();
    }

    return 0;
}
