#include "soldier.h"

Soldier::Soldier(Vec2f size, Player* player)
    : HumanEntity(size)
{
    this->player = player;
    shape.setFillColor(sf::Color(255, 0, 0));

    sightRange = 200 + 200 * (rand() % 1000) / 1000.0f;
    attackRange = 64 + 64 * (rand() % 1000) / 1000.0f;
    swingState = READY;
}

void Soldier::update(float time)
{
    HumanEntity::update(time);
    float sightRange = 300;
    float attackRange = 128;

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
        if(std::abs(lastKnownDistance) < attackRange)
        {
            movementAmount = 0;

            //attack
            if(detectState == DETECTED)
            {
                attack();
            }
        }
        else
        {
            movementAmount = -lastKnownDirection;
        }
    }

    movementAmount *= 100;

    updateSword(time);
}
void Soldier::draw(sf::RenderWindow* window)
{
    HumanEntity::draw(window);

    swordSprite.setPosition(pos);
    window->draw(swordSprite);
}

void Soldier::attack()
{
    if(swingState == READY)
    {
        swingState = FORWARD;
    }
}
void Soldier::updateSword(float time)
{
    float swordLength = 128;

    if(swingState != READY)
    {
        float swingAmount = 1;
        float targetAngle = M_PI / 6;

        if(swingState == BACK)
        {
            swingAmount = 0.5;
            targetAngle = -M_PI / 2;
        }
        
        float angleDiff = targetAngle - swordAngle;
        
        if(std::abs(angleDiff) < 0.3)
        {
            if(swingState == FORWARD)
            {
                swingState = BACK;
            }
            else if(swingState == BACK)
            {
                swingState = READY;
            }
        }

        swordAngle += angleDiff * swingAmount * time;
        
        std::cout << swordAngle << std::endl;
    }
    else
    {
        swordAngle = - M_PI / 2;
    }

    swordSprite.setRotation(swordAngle / M_PI * 360);
}

void Soldier::setSwordTexture(std::shared_ptr<sf::Texture> texture)
{
    this->swordSprite.setTexture(*texture);
    this->swordSprite.setOrigin(texture->getSize().x / 2, 50); 
    this->swordSprite.setScale(2,2);
}
