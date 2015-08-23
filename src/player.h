#ifndef H_PLAYER
#define H_PLAYER

#include "engine/humanentity.h"
#include "hidingspot.h"
#include "bloodsplatter.h"

class Player : public HumanEntity
{
public:
    enum Shape
    {
        HUMAN,
        MONSTER,
    };

    Player(Vec2f size);
    virtual Player* clone();

    virtual void update(float time);
    virtual void draw(sf::RenderWindow* window);

    Shape getShape();
    bool isHidden();
    bool canBeSeen();
private:
    void attack();

    void transform();
    sf::Time transformFrequency;
    sf::Time attackFrequency;
    sf::Time attackDuration;

    Shape currentShape;

    sf::Clock playerClock;
    sf::Time lastTransform;
    sf::Time lastAttack;

    bool hidden;
    HidingSpot* hidingSpot;

};
#endif
