#include "button.h"

using namespace zui;

Button::Button(Vec2f pos, std::string name)
    : UIComponent(pos),
    InputComponent(name)
{

}

bool Button::boolValue()
{
    if(state == State::CLICKED)
    {
        return true;
    }

    return false;
}
int Button::intValue()
{
    return (int) state;
}
float Button::floatValue()
{
    return (float) state;
}
std::string  Button::stringValue()
{
    switch(state)
    {
        case OFF:
            return "released";
        case CLICKED:
            return "clicked";
        case PRESSED:
            return "held";
    }
    return "";
}
