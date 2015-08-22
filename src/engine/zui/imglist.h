#ifndef H_IMGLIST
#define H_IMGLIST

#include <vector>
#include <string>
#include <utility>
#include <memory>

#include <SFML/Graphics.hpp>

#include "uicomponent.h"
#include "inputcomponent.h"
#include "imglistelement.h"
#include "textbutton.h"

#include "../vec2f.h"

namespace zui
{
class ImgList : public UIComponent, InputComponent
{
public:
    //Elements is a vector with pairs of filename and value for each img element.
    //First is pair, last is value
    ImgList(Vec2f pos, Vec2f size, std::string name);
    ImgList(std::vector<std::pair<std::string, std::string>> elements, Vec2f pos, Vec2f size, std::string name);


    void setBackgroundColor(sf::Color bgColor);
    void setElements(std::vector< std::pair< std::string, std::string > > elements);

    void setActive(bool active);
    
    void onInputChange(InputComponent* component); 
    std::string stringValue();
    
    void handleMouseMove(MouseData mouseData, Vec2f parentPos);
    //Handle mouse button press and releases. Return true if the component should bock the press for
    //parent components
    bool handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos);
protected:
    virtual void drawSelf(sf::RenderWindow* window, Vec2f actualPos);
    
    virtual bool posIsOnComponent(Vec2f checkPos, Vec2f actualPos);
private:
    const float padding = 10; //Amount of padding in pixels between two elements
    const float imgSize = 100;

    std::vector< std::unique_ptr< ImgListElement> > listElements;

    InputComponent* selectedElement;

    sf::RectangleShape bgShape;
    sf::Color bgColor;

    std::unique_ptr< TextButton > okButton;

    std::string value;

    bool active;
};
}
#endif
