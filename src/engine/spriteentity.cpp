#include "spriteentity.h"

void SpriteEntity::create(std::shared_ptr<sf::Texture> texture)
{
    this->sprite.setTexture(*texture);
    this->texture = texture;
}

SpriteEntity* SpriteEntity::clone()
{
    return new SpriteEntity(*this);
}

void SpriteEntity::setPosition(Vec2f pos)
{
    Entity::setPosition(pos);
    this->sprite.setPosition(pos);
}
void SpriteEntity::setScale(Vec2f scale)
{
    sprite.setScale(scale);
}

void SpriteEntity::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}

void SpriteEntity::setOrigin(Vec2f origin)
{
    this->origin = origin;

    Vec2f coordOrigin;
    coordOrigin.x = sprite.getTextureRect().width * origin.x;
    coordOrigin.y = sprite.getTextureRect().height * origin.y;

    this->sprite.setOrigin(coordOrigin);
}

bool SpriteEntity::pointIsOnEntity(Vec2f point)
{
    sf::FloatRect spriteShape = sprite.getGlobalBounds();

    if(spriteShape.contains(point))
    {
        return true;
    }
    return false;
}
