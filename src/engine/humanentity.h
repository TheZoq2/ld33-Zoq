#ifndef H_HUMANENTITY
#define H_HUMANENTITY

#include "physicsentity.h"

class HumanEntity : public PhysicsEntity
{
public:
    HumanEntity(Vec2f size);
    virtual HumanEntity* clone();

    virtual void update(float time);
    virtual void draw(sf::RenderWindow* window);

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

private:
};
#endif
