#include "soldier.h"

Soldier::Soldier(Vec2f size, Player* player)
    : HumanEntity(size)
{
    this->player = player;
    shape.setFillColor(sf::Color(255, 0, 0));
}

void Soldier::update(float time)
{
    float sightRange = 300;

    //Get the player position
    Vec2f playerPos = player->getPosition();

    float playerDistance = pos.x - playerPos.x;
    float lastKnownDistance = pos.x - lastKnownPlayer.x;
    int lastKnownDirection = lastKnownDistance / std::abs(lastKnownDistance);

    if(std::abs(playerDistance) < sightRange && player->canBeSeen())
    {
        detectState = DetectionState::DETECTED;
    }

    switch(detectState)
    {
        case(NEUTRAL):
        {
            movementAmount = 0;
            break;
        }
        case(SEARCHING):
        {
            break;
        }
        case(DETECTED):
        {
            lastKnownPlayer = player->getPosition();

            if(player->isHidden())
            {
                detectState = SEARCHING;
            }
            break;
        }
    }

    if(detectState == SEARCHING || detectState == DETECTED)
    {
        movementAmount = -lastKnownDirection;
    }

    movementAmount *= 100;
    HumanEntity::update(time);
}
