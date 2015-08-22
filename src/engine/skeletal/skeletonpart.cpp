#include "skeletonpart.h"

SkeletonPart::SkeletonPart(int id)
{
    this->id = id;
}

void SkeletonPart::setID(int id)
{
    this->id = id;
}
void SkeletonPart::setParent(int parentID)
{
    this->parentID = parentID;
}
void SkeletonPart::setName(std::string name)
{
    this->name = name;
}
void SkeletonPart::setPosition(Vec2f pos)
{
    this->pos = pos;
}
void SkeletonPart::setScale(Vec2f scale)
{
    this->scale = scale;
}
void SkeletonPart::setAngle(float angle)
{
    this->angle = angle;
}
