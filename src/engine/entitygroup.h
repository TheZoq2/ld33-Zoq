#ifndef H_ENTITYGROUP
#define H_ENTITYGROUP

#include <vector>
#include <stdint.h>

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "platform.h"

class Entity;

class EntityGroup
{
public:
    struct PlatformCollisionResult
    {
        uint32_t platformID;
        Line::IntersectResult intResult;
    };

    EntityGroup();

    //TODO: Make sure entity is only added once
    void addEntity(Entity* entity);
    void addPlatform(Platform* platform);

    void draw(sf::RenderWindow* window);
    void update(float frameTime);

    void onEntityDepthChange(Entity* entity);

    //std::vector<IDPlatform>* getPlatforms();
    Platform* getPlatformByID(uint32_t id);
    bool platformExists(uint32_t id);

    PlatformCollisionResult getPlatformCollision(Vec2f originPos, Line* line); 

    Entity* getFirstCollision(Vec2f point);
private:
    uint32_t nextPlatformID;

    struct IDPlatform
    {
        uint32_t id;
        Platform* platform;
    };

    //Insert an entity in the correct location in the entity vector based on depth
    void insertEntity(Entity* entity); 

    std::vector< std::unique_ptr< Entity > > entities;
    std::vector<IDPlatform> platforms;
};
#endif
