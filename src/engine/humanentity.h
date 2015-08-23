#ifndef H_HUMANENTITY
#define H_HUMANENTITY

#include <math.h>

#include "physicsentity.h"
#include "../bloodsplatter.h"

class HumanEntity : public PhysicsEntity
{
public:
    HumanEntity(Vec2f size);
    virtual HumanEntity* clone();

    virtual void update(float time);
    virtual void draw(sf::RenderWindow* window);

    virtual void kill();
    
    virtual Line* getCollisionLine();

    virtual void setWalkFrame(std::shared_ptr<sf::Texture> texture, int index);
protected:
    enum MoveState
    {
        NORMAL,
        ROLLING,
    };

    int maxSpeed;
    float maxAirAcceleration;
    int rollMilliseconds;
    float rollMultiplyer;
    float rollBaseMultiplyer;

    virtual void roll(int direction); //Direction is +/- 1

    float movementAmount; //Percentage of the max speed that the entity should move at right now

    sf::Clock rollClock; //TODO: Move to 'global'?
    sf::Time rollStart;
    
    int rollDirection;

    MoveState moveState;
    int movementDirection;

    Line collisionLine;

    std::shared_ptr<sf::Texture> bloodTexture;

    sf::Sprite walkSprite;
    std::shared_ptr<sf::Texture> walkFrames[2];

    void bleed();
private:
};
#endif
