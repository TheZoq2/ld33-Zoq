#include "civilian.h"

Civilian::Civilian(Vec2f size, Player* player)
    : HumanEntity(size)
{
    this->player = player;

    scareState = NORMAL;

    shape.setFillColor(sf::Color(0,0,255));

    scareRange = 64 + 256 * (rand() %1000) / 1000.0;
    runDistance = scareRange + 256 * (rand() %1000) / 1000.0;

    HumanEntity::maxSpeed = 100 + 100 * (rand() %1000) / 1000.0;
}

void Civilian::update(float time)
{
    //Get the player position
    Vec2f playerPos = player->getPosition();

    float playerDistance = pos.x - playerPos.x;
    int playerDirection = playerDistance / std::abs(playerDistance);

    if(std::abs(playerDistance) < scareRange && player->canBeSeen())
    {
        scareState = RUNNING;
    }
    if(std::abs(playerDistance) > runDistance)
    {
        scareState = NORMAL;
    }

    switch(scareState)
    {
        case(NORMAL):
        {
            movementAmount = 0;
            break;
        }
        case(RUNNING):
        {
            movementAmount = playerDirection;
            break;
        }
    }

    movementAmount *= 100;
    HumanEntity::update(time);
}
