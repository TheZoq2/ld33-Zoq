#include "window.h"

zui::Window::Window()
{}
zui::Window::~Window()
{}

void zui::Window::create(Vec2f pos, Vec2f size, sf::Color color)
{
    UIComponent::size = size;
    this->color = color;
    UIComponent::pos = pos;
    
    this->shape.setSize(size);
    this->shape.setFillColor(color);
    
}

void zui::Window::setPosition(Vec2f pos)
{
    UIComponent::setPosition(pos);
    this->shape.setPosition(pos);
}

void zui::Window::drawSelf(sf::RenderWindow* window, Vec2f totalPos)
{
    this->shape.setPosition(totalPos);
    window->draw(shape);
    
}
