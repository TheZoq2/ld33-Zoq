#include "entity.h"

Entity::Entity()
{
    this->depth = 0; //Setting the default depth
    this->done = false;
}

void Entity::setPosition(Vec2f pos)
{
    this->pos = pos;
}
void Entity::setDepth(int depth)
{
    this->depth = depth;

    //Notify the group of the change in depth
    if(group != NULL)
    {
        group->onEntityDepthChange(this);
    }
}
void Entity::setGroup(EntityGroup* group)
{
    this->group = group;
}

int Entity::getDepth()
{
    return this->depth;
}
Vec2f Entity::getPosition()
{
    return pos;
}
bool Entity::isDone()
{
    return done;
}
void Entity::setDone(bool done)
{
    this->done = done;
}

bool Entity::pointIsOnEntity(Vec2f point)
{
    return false;
}
