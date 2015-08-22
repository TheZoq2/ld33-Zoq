#ifndef H_PLAYER
#define H_PLAYER

#include "engine/humanentity.h"

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

    Shape getShape();
private:
    Shape currentShape;
};
#endif
