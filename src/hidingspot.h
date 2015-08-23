#ifndef H_HIDINGSPOT
#define H_HIDINGSPOT

#include "engine/spriteentity.h"

class HidingSpot : public SpriteEntity
{
public:
    virtual void create(std::shared_ptr<sf::Texture> defaultTexture, std::shared_ptr<sf::Texture> hiddenTexture);

    virtual HidingSpot* clone();

    virtual void setHidden(bool hidden);
private:
    std::shared_ptr<sf::Texture> defaultTexture;
    std::shared_ptr<sf::Texture> hiddenTexture;

    bool hidden;
};
#endif
