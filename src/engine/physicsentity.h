#ifndef H_PHYSICSENTITY
#define H_PHYSICSENTITY

#include "world.h"
#include "platform.h"

class PhysicsEntity : public Entity
{
public:
    PhysicsEntity(Vec2f size);
    
    virtual PhysicsEntity* clone();

    virtual void draw(sf::RenderWindow* window);
    virtual void update(float time);

    virtual void setPosition(Vec2f pos);

    virtual void jump(float speed);
protected:
    enum GroundState
    {
        ON_GROUND,
        RISING,
        FALLING,
    };

    GroundState groundState;

    Vec2f velocity;
private:
    uint32_t platformID; // The platform where the entity is currently 'standing'
    float platformX; //The current xPosition on the platform

    //The size of the entity. Each physics entity is considered a square and this determines
    //the width and height of that square
    Vec2f size;


    sf::RectangleShape shape;

    float gravity;
};
#endif
