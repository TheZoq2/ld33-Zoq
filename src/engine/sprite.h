#ifndef H_SPRITE
#define H_SPRITE

#include "SFML/Graphics.hpp"

class Sprite
{
public:
    Sprite(sf::Texture* texture);
    ~Sprite();

    void draw(sf::RenderWindow* window, sf::Vector2f cameraPos);

    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);
    void setScale(sf::Vector2f scale);
    void setScale(float x, float y);
    void setAngle(float angle);

private:
    sf::Sprite* sfSprite;
    sf::Texture* texture;

    sf::Vector2f position;
    sf::Vector2f scale;
    float angle;
};

#endif
