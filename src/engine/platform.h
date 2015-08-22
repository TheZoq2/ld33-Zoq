#ifndef H_PLATFORM
#define H_PLATFORM

#include <SFML/Graphics.hpp>

#include "vec2f.h"
#include "line.h"

class Platform
{
public:
    void create(Vec2f pos);
    void draw(sf::RenderWindow* window);

    void setPosition(Vec2f pos);

    Line::IntersectResult getCollision(Line* other);
    float getLocalX(float globalX);
    bool xIsOnPlatform(float localX);
    Vec2f getGlobalPos(float localX);
    
    void addPoint(Vec2f point);
    void addPoint(float x, float y);
private:
    void generateLines();

    std::vector<Vec2f> points;
    std::vector<Line> lines; //Generated each time points is updated

    Vec2f pos;
};
#endif
