#ifndef H_PARTICLEEFFECT
#define H_PARTICLEEFFECT

#include "vec2f.h"

class ParticleEffect
{
public:

    struct Keyframe
    {
        float time; //Time after last keyframe
        Vec2f minSpeed;
        Vec2f maxSpeed;
        
        Vec2f size;
    };
private:
    struct Particle
    {
        float lifetime;

        Vec2f pos;
        Vec2f speed;

        Vec2f size;
    };

    Vec2f emitterPos;
    Vec2f 
};
#endif
