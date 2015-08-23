#include "player.h"

Player::Player(Vec2f size)
    : HumanEntity(size)
{
    transformFrequency = sf::seconds(10);
}
Player* Player::clone()
{
    return new Player(*this);
}

void Player::update(float time)
{
    HumanEntity::update(time);

    HumanEntity::movementAmount = sf::Joystick::getAxisPosition(0, sf::Joystick::X);

    //Deadzone
    if(std::abs(movementAmount) < 5)
    {
        movementAmount = 0;
    }

    if(sf::Joystick::isButtonPressed(0, 0))
    {
        jump(600);
    }

    if(sf::Joystick::isButtonPressed(0, 4))
    {
        if(!hidden)
        {
            HumanEntity::roll(-1);
        }
    }
    else if(sf::Joystick::isButtonPressed(0, 5))
    {
        if(!hidden)
        {
            HumanEntity::roll(1);
        }
    }

    if(playerClock.getElapsedTime() - lastTransform > transformFrequency)
    {
        transform();
        lastTransform = playerClock.getElapsedTime();
    }

    //Hiding feature
    std::vector<Entity*> entities = group->getEntities();

    float hidingDistance = 128;
    for(auto it : entities)
    {
        HidingSpot* spot = dynamic_cast<HidingSpot*>(it);

        //If this entity is a hiding spot
        if(spot != nullptr)
        {
            //If the player is a monster
            if(currentShape == MONSTER)
            {
                if(std::abs(spot->getPosition().x - pos.x) < hidingDistance)
                {
                    if(sf::Joystick::isButtonPressed(0, 3))
                    {
                        hidden = true;
                        this->hidingSpot = spot;
                        spot->setHidden(true);
                    }
                }
            }
        }
    }

    if(hidden)
    {
        //If the player isn't a monster
        if(currentShape == Shape::HUMAN)
        {
            hidden = false;
            this->hidingSpot->setHidden(false);
            this->hidingSpot = nullptr;
        }
        else
        {
            movementAmount = 0;
        }
    }
}
void Player::draw(sf::RenderWindow* window)
{
    if(hidden == false)
    {
        HumanEntity::draw(window);
    }
}

Player::Shape Player::getShape()
{
    return currentShape;
}

void Player::transform()
{
    if(currentShape == HUMAN)
    {
        currentShape = MONSTER;

        HumanEntity::maxSpeed = 220;

        shape.setFillColor(sf::Color(150,150,150));
    }
    else
    {
        currentShape = HUMAN;

        HumanEntity::maxSpeed = 150;

        shape.setFillColor(sf::Color(255,255,255));
    }
}
