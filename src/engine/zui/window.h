#ifndef H_UIWINDOW
#define H_UIWINDOW

#include <SFML/Graphics.hpp>

#include "uicomponent.h"
#include "../vec2f.h"

namespace zui
{
    class Window : public UIComponent
    {
    public:
        Window();
        ~Window();
    
        virtual void create(Vec2f pos, Vec2f size, sf::Color color);
    
        virtual void drawSelf(sf::RenderWindow* window, Vec2f totalPos);
    
        virtual void setPosition(Vec2f pos);
    protected:
    private:
        sf::Color color;
    
        sf::RectangleShape shape;
    };
}
#endif
