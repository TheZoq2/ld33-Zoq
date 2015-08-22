#ifndef H_TEXTBUTTON
#define H_TEXTBUTTON

#include "button.h"
#include "../vec2f.h"

#include <memory>
#include <SFML/Graphics.hpp>

namespace zui
{
class TextButton : public Button
{
public:
    struct ButtonColor
    {
        sf::Color defaultColor;
        sf::Color hoverColor;
        sf::Color pressColor;
    };
    TextButton(std::string name);
    TextButton(std::string name, Vec2f pos, Vec2f size, ButtonColor colors, std::string text);

    void setPosition(Vec2f pos);
    Vec2f getSize();

    void handleMouseMove(MouseData mouseData, Vec2f parentPos);
    bool handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos);
protected:
    virtual void drawSelf(sf::RenderWindow* window, Vec2f actualPos);

    virtual void changeState(State state);
private:

    sf::RectangleShape box;
    sf::Text textDisplay;

    ButtonColor colors;

    std::string text;
    
    sf::Font font;
};
}
#endif
