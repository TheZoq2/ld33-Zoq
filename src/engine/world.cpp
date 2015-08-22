#include "world.h"

World::World()
{
    gravity = 9.82;
}
World::~World()
{
}

void World::addEntityGroup(EntityGroup* group, float paralaxAmount)
{
    Layer layer; //The new layer to add;
    layer.eGroup = group;
    layer.paralaxAmount = paralaxAmount;

    layers.push_back(layer);
}

void World::draw(sf::RenderWindow* window, Vec2f cameraPos)
{
    sf::View view = window->getView();

    view.setCenter(cameraPos);

    window->setView(view);


    for(auto it : layers)
    {
        Layer layer = it;

        //Calculating the center for this layer
        //For now, paralax scrolling will only be done on the x-axis
        Vec2f paralaxPos = cameraPos;
        paralaxPos.x = cameraPos.x * layer.paralaxAmount;
        
        view.setCenter(paralaxPos);
        //window->setView(view);
        
        layer.eGroup->draw(window);
    }

    mainGroup.draw(window);
}
void World::update(float frameTime)
{
    this->mainGroup.update(frameTime);

    for(auto it : this->layers)
    {
        it.eGroup->update(frameTime);
    }
}


float World::getGravity()
{
    return gravity;
}
EntityGroup* World::getMainGroup()
{
    return &mainGroup;
}
