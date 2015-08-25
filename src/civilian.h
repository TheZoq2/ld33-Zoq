#ifndef H_CIVILIAN
#define H_CIVILIAN

#include "engine/humanentity.h"
#include "engine/vec2f.h"

#include "player.h"

class Civilian : public HumanEntity
{
public:
    Civilian(Vec2f size, Player* player);

    virtual void update(float time);
private:
    enum ScareState
    {
        NORMAL,
        RUNNING,
    };

    ScareState scareState;

    Player* player;

    float scareRange;
    float runDistance;

    float totalTime;
    float lastMoveChange;
    int wanderDir;
    float nextMoveChange;
};
#endif
