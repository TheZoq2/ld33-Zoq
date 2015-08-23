#include "humanentity.h"

HumanEntity::HumanEntity(Vec2f size)
    : PhysicsEntity(size)
{
    moveState = NORMAL;

    maxSpeed = 180;
    maxAirAcceleration = 1000;
    rollMilliseconds = 1000;
    rollMultiplyer = 1.5;
    rollBaseMultiplyer = 0.5;
    
    
    movementDirection = 1;

    bloodTexture = std::make_shared<sf::Texture>();
    bloodTexture->loadFromFile("../media/img/blood.png");

    walkSprite.setOrigin(32,32);
    walkSprite.setScale(2, 2);
    walkFrames[0] = std::make_shared<sf::Texture>();
    walkFrames[1] = std::make_shared<sf::Texture>();

    walkFrames[0]->loadFromFile("../media/img/playerDemon.png");
    walkFrames[1]->loadFromFile("../media/img/playerDemon_walk.png");
    walkSprite.setTexture(*walkFrames[0]);
}
HumanEntity* HumanEntity::clone()
{
    return new HumanEntity(*this);
}

void HumanEntity::update(float time)
{
    PhysicsEntity::update(time);

    switch(moveState)
    {
        case NORMAL:
        {
            if(groundState == GroundState::ON_GROUND)
            {
                velocity.x = (maxSpeed * 2 * movementAmount / 100.0f); 
            }
            else
            {
                float addedVel = (maxAirAcceleration*time * 2 * movementAmount / 100.0f) ;

                velocity.x += addedVel;

                if(velocity.x > maxSpeed)
                {
                    velocity.x = maxSpeed;
                }
                else if(velocity.x < -maxSpeed)
                {
                    velocity.x = -maxSpeed;
                }
            }
            break;
        }
        case ROLLING:
        {
            float rolledTime = (rollClock.getElapsedTime() - rollStart).asMilliseconds();
            
            float newMultiplyer = rollMultiplyer * (1 - (rolledTime / rollMilliseconds)) + rollBaseMultiplyer;

            velocity.x = newMultiplyer * maxSpeed * rollDirection;

            if(rolledTime > rollMilliseconds)
            {
                moveState = NORMAL;
            }
        }
    }

    //Calculating the last movement direction
    if(velocity.x > 0)
    {
        movementDirection = 1;
    }
    else if(velocity.x < 0)
    {
        movementDirection = -1;
    }

    collisionLine = Line(Vec2f(pos.x, pos.y-size.y/2), Vec2f(pos.x, pos.y+size.y/2));
}

void HumanEntity::draw(sf::RenderWindow* window)
{
    //PhysicsEntity::draw(window);

    //collisionLine.draw(window);
    if(movementAmount != 0)
    {
        float sinValue = sin(rollClock.getElapsedTime().asSeconds() * 10.0f);
        int textureIndex = round((sinValue + 1) / 2.0f);

        //std::cout << sinValue << "    " << textureIndex<< std::endl;
        walkSprite.setTexture(*walkFrames[textureIndex]);
    }
    else
    {
        walkSprite.setTexture(*walkFrames[0]);
    }
    
    walkSprite.setScale(movementDirection * 2 , 2);
    walkSprite.setPosition(pos);

    window->draw(walkSprite);
}

Line* HumanEntity::getCollisionLine()
{
    return &collisionLine;
}

void HumanEntity::kill()
{
    done = true;

    bleed();
}

void HumanEntity::setWalkFrame(std::shared_ptr<sf::Texture> texture, int index)
{
    walkFrames[index] = texture;
    walkSprite.setTexture(*walkFrames[index]);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void HumanEntity::roll(int direction)
{
    if(moveState == MoveState::NORMAL && groundState == GroundState::ON_GROUND)
    {
        rollStart = rollClock.getElapsedTime();

        velocity.x = maxSpeed * direction * rollMultiplyer;
        this->rollDirection = direction;

        this->moveState = ROLLING;
    }
}

void HumanEntity::bleed()
{
    //Creating blood splats
    for(unsigned int i = 0; i < 40; i++)
    {
        BloodSplatter* splatter = new BloodSplatter();
        splatter->create(bloodTexture);
        
        float maxSpeedX = 200;
        float minSpeedX = -200;
        float minSpeedY = -500;
        float maxSpeedY = 30;

        if(movementDirection == 1)
        {
            float buffer = minSpeedX;
            minSpeedX = -maxSpeedX;
            maxSpeedX = -buffer;
        }

        Vec2f position = this->getPosition();
        position.x += 16 * (rand() % 1000) / 1000.0f;
        position.y += 64 * (rand() % 1000) / 1000.0f;

        splatter->giveSpeed(minSpeedX, minSpeedY, maxSpeedX, maxSpeedY);
        splatter->setPosition(position);

        //Add the blood to the entity group
        group->addEntity(splatter);
    }
}
