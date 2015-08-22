#ifndef H_SKELEPART
#define H_SKELEPART

#include <string>

#include "../vec2f.h"

class SkeletonPart
{
public:
    SkeletonPart(int id);

    void setID(int id);
    void setParent(int parentID);
    void setName(std::string name);

    void setPosition(Vec2f pos);
    void setScale(Vec2f scale);
    void setAngle(float angle);
protected:
    Vec2f pos;
    Vec2f scale;
    float angle;
private:
    int id;
    int parentID;

    std::string name;
};
#endif
