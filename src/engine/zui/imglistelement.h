#ifndef H_IMGLISTELEMENT
#define H_IMGLISTELEMENT

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../vec2f.h"
#include "uicomponent.h"
#include "inputcomponent.h"

namespace zui
{
class ImgListElement :  public UIComponent, InputComponent 
{
public:
    ImgListElement(std::string imgPath, std::string valueName, Vec2f pos, Vec2f size);


    void setPosition(Vec2f pos);

    void setValue(bool val);
    bool boolValue();
    std::string getValueName();

    virtual void handleMouseMove(MouseData mouseData, Vec2f parentPos);
    //Handle mouse button press and releases. Return true if the component should bock the press for
    //parent components
    virtual bool handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos);
    
    static const std::string DEFAULT_NAME; 
protected:
    virtual void drawSelf(sf::RenderWindow* window, Vec2f actualPos);

private:
    enum State
    {
        DEFAULT,
        HOVERED,
        SELECTED
    };
    State state;

    float scale;

    std::string imgPath;
    std::string valueName;

    sf::Sprite sprite;
    sf::Texture texture;

    bool pointIsOnElement(Vec2f point, Vec2f actualPos);
};
}
#endif
