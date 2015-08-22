#ifndef H_UICOMPONENT
#define H_UICOMPONENT

#include <vector>
#include <map>
#include <utility>
#include <string>
#include <stdint.h>

#include <SFML/Graphics.hpp>

#include "inputcomponent.h"
#include "../vec2f.h"
#include "../mouseeventhandler.h"

namespace zui
{
class UIValueListener
{
public:
    virtual void onUIChange(InputComponent* changedComponent) = 0;
};

//Basic UI component interface. Contains functions for handling UIInput events aswell
//as drawing all children.
class UIComponent : public MouseListener
{
public:

    void draw(sf::RenderWindow* window, sf::Vector2f parentPos);
    bool posIsOnUI(Vec2f checkPos, Vec2f parentPos);

    virtual void setPosition(Vec2f pos);
    void setParent(UIComponent* parent);
    
    void addChildComponent(UIComponent* child);

    void addUIValueListener(UIValueListener* listener, std::string inputName);
    //Function called when a child component has been updated
    virtual void onInputChange(InputComponent* component); 
    virtual void notifyListeners(InputComponent* component);

    //Event listener for mouse movement.
    void onMouseMove(MouseData mouseData);
    void onMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed);
    virtual void handleMouseMove(MouseData mouseData, Vec2f parentPos);
    //Handle mouse button press and releases. Return true if the component should bock the press for
    //parent components
    virtual bool handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos);

protected:
    virtual void drawSelf(sf::RenderWindow* window, Vec2f actualPos) = 0;
    virtual bool posIsOnComponent(Vec2f checkPos, Vec2f actualPos);

    UIComponent();
    UIComponent(Vec2f pos);

    sf::Vector2f pos;
    Vec2f size;
    
    //std::vector<UIComponent*> components;
    std::vector< std::unique_ptr< UIComponent > > children;

    UIComponent* parent;
    
    std::vector< std::pair<std::string, UIValueListener*> > valueListeners;
};
}
#endif
