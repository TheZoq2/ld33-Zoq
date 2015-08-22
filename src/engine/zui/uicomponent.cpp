#include "uicomponent.h"

using namespace zui;

UIComponent::UIComponent()
{
    this->pos = Vec2f(0,0);
    this->size = Vec2f(0, 0);
    this->parent = NULL;

}
UIComponent::UIComponent(Vec2f pos)
    : UIComponent()
{
    this->pos = pos;
}


void UIComponent::setPosition(Vec2f pos)
{
    this->pos = pos;
}
void UIComponent::setParent(UIComponent* parent)
{
    this->parent = parent;
}

void UIComponent::draw(sf::RenderWindow* window, sf::Vector2f parentPos)
{
    sf::Vector2f totalPos = pos + parentPos;
    //Draw this component, then draw all parent components above that
    this->drawSelf(window, totalPos);

    for(uint16_t i = 0; i < children.size(); i++)
    {
        children.at(i)->draw(window, totalPos);
    }
}

bool UIComponent::posIsOnUI(Vec2f checkPos, Vec2f parentPos)
{
    bool result = false;

    Vec2f actualPos = parentPos + pos;

    result = result || posIsOnComponent(checkPos, actualPos);

    for(auto& it : children)
    {
        result = result || it->posIsOnUI(checkPos, actualPos);
    }

    return result;
}
bool UIComponent::posIsOnComponent(Vec2f checkPos, Vec2f actualPos)
{
    if(checkPos.x >= actualPos.x && checkPos.x <= actualPos.x + size.x && checkPos.y >= actualPos.y && checkPos.y <= actualPos.y + size.y)
    {
        return true;
    }
    return false;
}

void UIComponent::addUIValueListener(UIValueListener* listener, std::string componentName)
{
    std::pair<std::string, UIValueListener*> pair(componentName, listener);
    this->valueListeners.push_back(pair);
}
void UIComponent::addChildComponent(UIComponent* child)
{
    this->children.push_back(std::unique_ptr<UIComponent>(child));

    child->setParent(this);
}


void UIComponent::onInputChange(InputComponent* component)
{
    notifyListeners(component);

    //Notify the parent of the change if one exists
    if(parent != NULL)
    {
        parent->onInputChange(component);
    }
}
void UIComponent::notifyListeners(InputComponent* component)
{
    //Iterating over the listeners to check if a listener is listening for this specific component
    for(auto it : valueListeners)
    {
        if(it.first.compare(component->getName()) == 0)
        {
            it.second->onUIChange(component);
        }
    }
}

void UIComponent::onMouseMove(MouseData mouseData)
{
    this->handleMouseMove(mouseData, Vec2f(0,0));
}
void UIComponent::onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed)
{
    this->handleMouseButtonChange(button, position, pressed, Vec2f(0,0));
}
void UIComponent::handleMouseMove(MouseData mouseData, Vec2f parentPos)
{
    for(auto& it : children)
    {
        it->handleMouseMove(mouseData, parentPos + pos);
    }
}
bool UIComponent::handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos)
{
    bool isBlocked = false;
    for(auto& it : children)
    {
        if(it->handleMouseButtonChange(button, position, pressed, parentPos))
        {
            isBlocked = true;
        }
    }

    return isBlocked; 
}
