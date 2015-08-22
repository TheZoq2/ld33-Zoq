#ifndef H_SKELE_BONE
#define H_SKELE_BONE

#include "skeletonpart.h"

class Bone : public SkeletonPart
{
public:
    Bone(float length, int id)
private:
    std::vector<SkeletonPart*> children;

    float length; //The length of the bone
};
#endif
