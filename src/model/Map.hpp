#ifndef MAP_H
#define MAP_H
#include <Resource.hpp>
#include <vector>

// 定义一个地图类
class Map {
public:
    int width;
    int height;
    std::vector<Resource> resources;
    //初始化
    Map(int w, int h);

    // 绘制地图
    void draw(sf::RenderWindow& window);
};
#endif