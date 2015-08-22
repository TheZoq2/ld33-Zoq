#include "physicsentity.h"

PhysicsEntity::PhysicsEntity(Vec2f size)
{
    this->groundState = GroundState::FALLING;
    this->size = size;
    this->shape.setSize(size);
    shape.setOrigin(size.x / 2, size.y / 2);

    this->gravity = 9.82 * 90;
}

PhysicsEntity* PhysicsEntity::clone()
{
    return new PhysicsEntity(*this);
}

void PhysicsEntity::update(float time)
{
    Vec2f newPos = pos;

    switch(groundState)
    {
        case(ON_GROUND):
        {
            //Make sure the platform still exists
            if(group->platformExists(platformID) == true)
            {
                Platform* platform = group->getPlatformByID(platformID);

                //Calculate the new position
                platformX += velocity.x * time;

                //Check if the new position is also on the platform
                if(platform->xIsOnPlatform(platformX))
                {
                    newPos = platform->getGlobalPos(platformX);
                    newPos.y -= size.y / 2;
                }
                else //The entity fell off the platform
                {
                    groundState = FALLING;
                }

            }
            else
            {
                groundState = FALLING;
            }
            break;
        }
        case(RISING):
        {
            newPos = pos + velocity * time;
            velocity.y += gravity * time;

            if(velocity.y > 0)
            {
                groundState = FALLING;
            }

            break;
        }
        case(FALLING):
        {
            //TODO: Move X-Axis
            newPos.x += velocity.x * time;
            
            
            //Calculate feet position
            Vec2f feetPos = newPos;
            feetPos.x = newPos.x;
            feetPos.y = newPos.y + size.y / 2;

            //Move y-axis
            Vec2f fallingFeetPos = feetPos;
            fallingFeetPos.y += velocity.y * time;
            Line fallingLine(feetPos, fallingFeetPos);

            //Get collisions between 
            EntityGroup::PlatformCollisionResult collision = Entity::group->getPlatformCollision(feetPos, &fallingLine);
            
            if(collision.intResult.intersected == true)
            {
                //Change the state and remember the ID of the platform that was hit
                groundState = GroundState::ON_GROUND;
                platformID = collision.platformID;
                platformX = Entity::group->getPlatformByID(platformID)->getLocalX(collision.intResult.pos.x);

                velocity = Vec2f(0,0); //Kill all velocity

                newPos.y = collision.intResult.pos.y - size.y / 2.0f;
            }
            else
            {
                newPos = pos + velocity * time;
                velocity.y += gravity * time;
            }

            break;
        }

    } //End switch case

    //Update the position
    setPosition(newPos);
}
void PhysicsEntity::draw(sf::RenderWindow* window)
{
    window->draw(shape);
}

void PhysicsEntity::jump(float speed)
{
    groundState = GroundState::RISING;

    velocity.y = velocity.y - speed;
}

void PhysicsEntity::setPosition(Vec2f pos)
{
    Entity::setPosition(pos);

    this->shape.setPosition(pos);
}
