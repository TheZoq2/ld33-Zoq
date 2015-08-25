#ifndef H_PLAYER
#define H_PLAYER

#include "engine/humanentity.h"
#include "hidingspot.h"
#include "bloodsplatter.h"
#include "soldier.h"

class Soldier;

class Player : public HumanEntity
{
public:
    enum Shape
    {
        HUMAN,
        MONSTER,
    };


    Player(Vec2f size);
    virtual ~Player();
    virtual Player* clone();

    virtual void update(float time);
    virtual void draw(sf::RenderWindow* window);

    virtual void damage(float damage);
    virtual float getHealth();

    Shape getShape();
    bool isHidden();
    bool canBeSeen();

    virtual int getScore();
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

    float health;

    //sf::Texture normalTexture;
    //sf::Texture monsterTexture;
    std::shared_ptr<sf::Texture> normalTexture;
    std::shared_ptr<sf::Texture> normalWalkTexture;
    std::shared_ptr<sf::Texture> monsterTexture;
    std::shared_ptr<sf::Texture> monsterWalkTexture;


    sf::Texture monsterAttackTexture;
    //sf::Sprite sprite;
    sf::Sprite attackSprite;

    bool attacking;
    bool showTransformIndicator;
    sf::Sprite transformIndicator;

    int score;
};
#endif
