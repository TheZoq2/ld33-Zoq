#ifndef H_PLAYER
#define H_PLAYER

#include "engine/humanentity.h"

class Player : public HumanEntity
{
public:
    Player(Vec2f size);
    virtual Player* clone();

    virtual void update(float time);
private:
};
#endif
