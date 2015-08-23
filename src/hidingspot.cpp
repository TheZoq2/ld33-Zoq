#include "hidingspot.h"

HidingSpot* HidingSpot::clone()
{
    return new HidingSpot(*this);
}
void HidingSpot::create(std::shared_ptr<sf::Texture> defaultTexture, std::shared_ptr<sf::Texture> hiddenTexture)
{
    SpriteEntity::create(defaultTexture);

    hidden = false;

    this->defaultTexture = defaultTexture;
    this->hiddenTexture = hiddenTexture;
}

void HidingSpot::setHidden(bool hidden)
{
    if(hidden)
    {
        SpriteEntity::sprite.setTexture(*(hiddenTexture.get()));
    }
    else
    {
        SpriteEntity::sprite.setTexture(*(defaultTexture.get()));
    }

    this->hidden = hidden;
}
