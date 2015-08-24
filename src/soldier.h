#ifndef H_SOLDIER
#define H_SOLDIER

#include "player.h"

class Player;

class Soldier : public HumanEntity
{
public:
    Soldier(Vec2f size, Player* player);
    
    virtual void update(float time);
    virtual void updateSword(float time);
    virtual void draw(sf::RenderWindow* window);
    
    virtual void attack();

    virtual void setSwordTexture(std::shared_ptr<sf::Texture> swordTexture);

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

    float sightRange;
    float attackRange;
    
    enum SwingState
    {
        READY,
        FORWARD,
        BACK
    };

    sf::Sprite swordSprite;
    float swordAngle;
    float realAngle;
    SwingState swingState;
    bool swingDealtDamage;

    float totalTime;
    float lastMoveChange;
    int wanderDir;
};
#endif
