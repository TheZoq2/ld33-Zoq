#ifndef H_GROUND
#define H_GROUND

#include <SFML/Graphics.hpp>

#include "vec2f.h"

class Ground
{
public:
    void create(std::vector<float> points);

    void draw(sf::RenderTarget* target);

    void setPosition(Vec2f pos);
private:
    std::vector<float> points;

    sf::VertexArray vertecies;

    float pointDistance;

    sf::Transform transform;
    sf::RenderStates renderStates;
    Vec2f pos;
};
#endif
