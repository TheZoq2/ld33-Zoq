#include "player.h"

Player::Player(Vec2f size)
    : HumanEntity(size)
{
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

    if(sf::Joystick::isButtonPressed(0, 4))
    {
        HumanEntity::roll(-1);
    }
    else if(sf::Joystick::isButtonPressed(0, 5))
    {
        HumanEntity::roll(1);
    }

}

Player::Shape Player::getShape()
{
    return currentShape;
}
