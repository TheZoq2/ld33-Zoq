#ifndef H_HIDINGSPOTTEMPLATE
#define H_HIDINGSPOTTEMPLATE

#include <SFML/Graphics.hpp>
#include "engine/vec2f.h"
#include <memory>

class HidingSpotTemplate
{
public:
    HidingSpotTemplate(const HidingSpotTemplate& other);
    HidingSpotTemplate(std::string defaultPath, std::string hiddenPath, Vec2f origin, Vec2f scale);
    
    HidingSpotTemplate& operator=(const HidingSpotTemplate& other);

    std::string defaultPath;
    std::string hiddenPath;

    std::shared_ptr<sf::Texture> defaultTexture;
    std::shared_ptr<sf::Texture> hiddenTexture;

    Vec2f origin;
    Vec2f scale;
};
#endif
