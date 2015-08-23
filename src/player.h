#ifndef H_PLAYER
#define H_PLAYER

#include "engine/humanentity.h"
#include "hidingspot.h"

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

private:
    void transform();
    sf::Time transformFrequency;

    Shape currentShape;

    sf::Clock playerClock;
    sf::Time lastTransform;

    bool hidden;
    HidingSpot* hidingSpot;
};
#endif
