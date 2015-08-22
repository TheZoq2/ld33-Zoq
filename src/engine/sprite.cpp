#include "sprite.h"

Sprite::Sprite(sf::Texture* texture)
{
    this->texture = texture;
    
    this->sfSprite = new sf::Sprite(*texture);
}
Sprite::~Sprite()
{
    //Cleanup the pointers
    delete sfSprite;
}

void Sprite::draw(sf::RenderWindow* window, sf::Vector2f cameraPos)
{
    sf::Vector2f drawPosition = cameraPos + position;
    
    this->sfSprite->setPosition(drawPosition);

    window->draw(*this->sfSprite);
}

//Setter functions
void Sprite::setPosition(sf::Vector2f position)
{
    this->position = position;

    this->sfSprite->setPosition(position);
}
void Sprite::setPosition(float x, float y)
{
    this->position.x = x;
    this->position.y = y;

    this->setPosition(sf::Vector2f(x, y));
}
void Sprite::setScale(sf::Vector2f scale)
{
    this->scale = scale;

    this->sfSprite->setScale(scale);
}
void Sprite::setScale(float x, float y)
{
    this->scale.x = x;
    this->scale.y = y;

    this->setScale(sf::Vector2f(x, y));
}
void Sprite::setAngle(float angle)
{
    this->angle = angle;
    this->sfSprite->setRotation(angle);
}
