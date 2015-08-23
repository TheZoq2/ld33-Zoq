#include "bloodsplatter.h"

BloodSplatter::BloodSplatter()
    : PhysicsEntity(Vec2f(6, 6))
{
    const float minLifeTime = 0.5;
    const float maxLifeTime = 2;
    
    lifetime = minLifeTime + maxLifeTime * (rand() % 1000) / 1000.0f;
}

void BloodSplatter::create(std::shared_ptr<sf::Texture> texture)
{
    this->texture = texture;
    this->sprite.setTexture(*texture);

    this->sprite.setOrigin(Vec2f(3,3));
}
void BloodSplatter::update(float frameTime)
{
    PhysicsEntity::update(frameTime);

    timeAlive += frameTime;

    if(timeAlive > lifetime)
    {
        done = true;
    }
}

void BloodSplatter::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
}

void BloodSplatter::setPosition(Vec2f position)
{
    PhysicsEntity::setPosition(position);
    sprite.setPosition(position);
}

void BloodSplatter::giveSpeed(float minX, float minY, float maxX, float maxY)
{
    float speedX = minX + maxX * (rand() % 1000) / 1000.0f;
    float speedY = minY + maxY * (rand() % 1000) / 1000.0f;

    PhysicsEntity::velocity = Vec2f(speedX, speedY);
}
