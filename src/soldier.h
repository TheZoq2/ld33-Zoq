#ifndef H_SOLDIER
#define H_SOLDIER

#include "player.h"

class Soldier : public HumanEntity
{
public:
    Soldier(Vec2f size, Player* player);
    
    virtual void update(float time);
    
private:
    enum DetectionState
    {
        NEUTRAL,
        SEARCHING,
        DETECTED,
    };
    DetectionState detectState;

    Player* player;

    Vec2f lastKnownPlayer;
};
#endif
