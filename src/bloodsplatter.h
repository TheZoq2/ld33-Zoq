#ifndef H_BLOODSPLATTER
#define H_BLOODSPLATTER

#include <SFML/Graphics.hpp>
#include <memory>

#include "engine/physicsentity.h"
#include "engine/spriteentity.h"

class BloodSplatter : public PhysicsEntity
{
public:
    BloodSplatter();

    virtual void create(std::shared_ptr<sf::Texture> texture);
    virtual void draw(sf::RenderWindow* window);

    virtual void update(float frameTime);

    virtual void setPosition(Vec2f position);

    virtual void giveSpeed(float minX, float minY, float maxX, float maxY);
private:
    float lifetime;
    float timeAlive;
    
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;

};

#endif
