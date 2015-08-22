#include "ground.h"

void Ground::create(std::vector<float> points)
{
    this->pointDistance = 10;
    this->points = points;
    this->renderStates.transform = transform;

    float bottomLevel = 1000;

    //Creating the vertex array
    vertecies = sf::VertexArray(sf::TrianglesStrip, points.size() * 2);

    for(unsigned int i = 0; i < points.size(); i++)
    {
        vertecies[i].position = sf::Vector2f(i * pointDistance, points[i]);
        vertecies[i+1].position = sf::Vector2f(i * pointDistance, bottomLevel);

        vertecies[i].color = sf::Color::Green;
        vertecies[i + 1].color = sf::Color::Green;

        std::cout << vertecies[i].position.y << vertecies[i + 1].position.y << std::endl;
    }
}

void Ground::draw(sf::RenderTarget* target)
{
    target->draw(vertecies, renderStates);
}

void Ground::setPosition(Vec2f pos)
{
    this->pos = pos;
    this->transform.translate(pos);
}
