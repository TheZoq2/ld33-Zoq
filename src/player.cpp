#include "player.h"

Player::Player(Vec2f size)
    : HumanEntity(size)
{
    transformFrequency = sf::seconds(10);
    attackFrequency = sf::seconds(0.5);
    attackDuration = sf::seconds(0.25);

    health = 1000;
    hidden = false;

    normalTexture = std::make_shared<sf::Texture>();
    normalWalkTexture = std::make_shared<sf::Texture>();
    monsterTexture = std::make_shared<sf::Texture>();
    monsterWalkTexture = std::make_shared<sf::Texture>();

    normalTexture->loadFromFile("../media/img/playerHuman.png");
    normalWalkTexture->loadFromFile("../media/img/playerHuman_walk.png");
    monsterTexture->loadFromFile("../media/img/playerDemon.png");
    monsterWalkTexture->loadFromFile("../media/img/playerDemon_walk.png");

    monsterAttackTexture.loadFromFile("../media/img/playerDemon_attack.png");
    //sprite.setOrigin(32,32);
    //sprite.setScale(2, 2);
    //sprite.setTexture(normalTexture);

    attackSprite.setOrigin(32,32);
    attackSprite.setScale(2, 2);
    attackSprite.setTexture(monsterAttackTexture);

    transformIndicator.setTexture(*normalTexture);
    transformIndicator.setColor(sf::Color(255,255,255, 100));
    transformIndicator.setScale(2, 2);
    transformIndicator.setOrigin(32,32);

    currentShape = MONSTER;
    transform();
}
Player::~Player()
{}
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
    else if(playerClock.getElapsedTime() - lastTransform > transformFrequency - sf::seconds(2))
    {
        showTransformIndicator = true;
    }
    else
    {
        showTransformIndicator = false;
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

    //Attack stuff
    if(!hidden && currentShape == MONSTER)
    {
        sf::Time sinceLastAttack = playerClock.getElapsedTime() - lastAttack;

        if(sinceLastAttack < attackDuration)
        {
            attack();
            attacking = true;
        }
        else if(sinceLastAttack > attackFrequency)
        {
            if(sf::Joystick::isButtonPressed(0, 2))
            {
                lastAttack = playerClock.getElapsedTime();
                attack();
                attacking = true;
            }
        }
        else
        {
            attacking = false;
        }
    }
    else
    {
        attacking = false;
    }
}
void Player::draw(sf::RenderWindow* window)
{
    if(hidden == false)
    {
        HumanEntity::draw(window);
        //sprite.setScale(2 * movementDirection, 2);
        ////HumanEntity::draw(window);
        //sprite.setPosition(pos);
        //window->draw(sprite);

        if(attacking)
        {
            attackSprite.setScale(2 * movementDirection, 2);
            attackSprite.setPosition(pos);
            window->draw(attackSprite);

        }
        if(showTransformIndicator)
        {
            transformIndicator.setScale(2 * movementDirection, 2);
            transformIndicator.setPosition(pos);
            window->draw(transformIndicator);
        }
    }
}

void Player::damage(float damage)
{
    if(currentShape == Shape::MONSTER)
    {
        health -= damage * 0.1;
    }
    else
    {
        health -= damage;
    }

    bleed();
    std::cout << health << std::endl;
}
float Player::getHealth()
{
    return health;
}

Player::Shape Player::getShape()
{
    return currentShape;
}
bool Player::isHidden()
{
    return hidden;
}
bool Player::canBeSeen()
{
    return getShape() == MONSTER && !isHidden();
}

//////////////////////////////////////////////////
//          Private members
//////////////////////////////////////////////////
void Player::transform()
{
    if(currentShape == HUMAN)
    {
        currentShape = MONSTER;

        HumanEntity::maxSpeed = 220;

        shape.setFillColor(sf::Color(150,150,150));
        //sprite.setTexture(monsterTexture);
        HumanEntity::setWalkFrame(monsterTexture, 0);
        HumanEntity::setWalkFrame(monsterWalkTexture, 1);

        transformIndicator.setTexture(*normalTexture);
    }
    else
    {
        currentShape = HUMAN;

        HumanEntity::maxSpeed = 150;

        shape.setFillColor(sf::Color(255,255,255));
        HumanEntity::setWalkFrame(normalTexture, 0);
        HumanEntity::setWalkFrame(normalWalkTexture, 1);
        transformIndicator.setTexture(*monsterTexture);
    }
}

void Player::attack()
{
    float armLength = 64;

    Line arm(Vec2f(pos.x, pos.y), Vec2f(pos.x + armLength * movementDirection, pos.y));

    std::vector<Entity*> entities = group->getEntities();
    //Loop through the entities and check for humans
    for(auto it : entities)
    {
        HumanEntity* human = dynamic_cast<HumanEntity*>(it);

        if(human != nullptr)
        {
            //make sure it isn't a player
            if(dynamic_cast<Player*>(human) == nullptr)
            {
                if(arm.getIntersect(human->getCollisionLine()).intersected)
                {
                    human->kill();
                }
            }
        }
    }

}
