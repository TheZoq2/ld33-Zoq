#ifndef H_STATIC_ENTITY
#define H_STATIC_ENTITY

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "entity.h"
#include "sprite.h"
#include "vec2f.h"

class SpriteEntity : public Entity
{
public:
    void create(std::shared_ptr<sf::Texture> texture);

    virtual SpriteEntity* clone();

    virtual void setPosition(Vec2f pos);
    virtual void setScale(Vec2f scale);

    virtual void draw(sf::RenderWindow* window);

    //Sets the origin of the sprite in percentage.
    virtual void setOrigin(Vec2f origin);

    virtual bool pointIsOnEntity(Vec2f point);
private:
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;

    Vec2f scale;
    Vec2f origin;
};

#endif
