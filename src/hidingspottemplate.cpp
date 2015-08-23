#include "hidingspottemplate.h"

HidingSpotTemplate::HidingSpotTemplate(const HidingSpotTemplate& other)
{
    this->defaultPath = other.defaultPath;
    this->hiddenPath = other.hiddenPath;
    this->origin = other.origin;
    this->scale = other.scale;
    this->defaultTexture = other.defaultTexture;
    this->hiddenTexture = other.hiddenTexture;
}

HidingSpotTemplate::HidingSpotTemplate(std::string defaultPath, std::string hiddenPath, Vec2f origin, Vec2f scale)
{
    this->defaultPath = defaultPath;
    this->hiddenPath = hiddenPath;
    this->origin = origin;
    this->scale = scale;

    sf::Texture* newDTexture = new sf::Texture();
    newDTexture->loadFromFile(defaultPath);
    this->defaultTexture = std::shared_ptr<sf::Texture>(newDTexture);
    sf::Texture* newHTexture = new sf::Texture();
    newHTexture->loadFromFile(hiddenPath);
    this->hiddenTexture = std::shared_ptr<sf::Texture>(newHTexture);
}
HidingSpotTemplate& HidingSpotTemplate::operator=(const HidingSpotTemplate& other)
{
    defaultPath = other.defaultPath;
    hiddenPath = other.hiddenPath;
    origin = other.origin;
    scale = other.scale;
    this->defaultTexture = other.defaultTexture;
    this->hiddenTexture = other.hiddenTexture;
    
    return *this;
}
