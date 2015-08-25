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

    lastMoveChange = 0;
    nextMoveChange = 3 * (rand() % 1000) / 1000.0f;
}

void Civilian::update(float time)
{
    totalTime += time;

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
            movementAmount = 0.5 * wanderDir;
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

    //std::cout << movementAmount << std::endl;
    //std::cout << totalTime - lastMoveChange<< std::endl;

    //Changing the current wander direction
    if(totalTime - lastMoveChange > nextMoveChange)
    {
        nextMoveChange = 3 * (rand() % 1000) / 1000.0f;
        wanderDir = rand() % 3 - 1;
        lastMoveChange = totalTime;
    }

}
