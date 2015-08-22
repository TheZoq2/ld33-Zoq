#include "imglistelement.h"

using namespace zui;

const std::string ImgListElement::DEFAULT_NAME = "ImgListElement";

ImgListElement::ImgListElement(std::string imgPath, std::string valueName, Vec2f pos, Vec2f size)
    : UIComponent(pos), InputComponent(DEFAULT_NAME)
{
    UIComponent::size = size;

    this->imgPath = imgPath;
    this->valueName = valueName;

    this->texture.loadFromFile(imgPath);
    this->sprite.setTexture(texture);

    //Scaling the sprite to the correct size
    if(texture.getSize().x > texture.getSize().y)
    {
        scale = size.x / texture.getSize().x;
    }
    else
    {
        scale = size.y / texture.getSize().y;
    }

    this->sprite.setScale(scale, scale);
}

void ImgListElement::drawSelf(sf::RenderWindow* window, Vec2f actualPos)
{
    sf::Color spriteColor = sf::Color(255,255,255);

    if(state == State::HOVERED)
    {
        spriteColor = sf::Color(150,150,150);
    }
    else if(state == State::SELECTED)
    {
        spriteColor = sf::Color(150,255,150);
    }

    sprite.setColor(spriteColor);

    sprite.setPosition(actualPos);
    window->draw(sprite);
}

void ImgListElement::handleMouseMove(MouseData mouseData, Vec2f parentPos)
{
    Vec2f actualPos = pos + parentPos;
    UIComponent::handleMouseMove(mouseData, actualPos);

    if(posIsOnComponent((sf::Vector2f)mouseData.position, actualPos))
    {
        if(state == State::DEFAULT)
        {
            state = State::HOVERED;
        }
    }
    else
    {
        if(state != State::SELECTED)
        {
            state = State::DEFAULT;
        }
    }
}
bool ImgListElement::handleMouseButtonChange(sf::Mouse::Button button, Vec2f position, bool pressed, Vec2f parentPos)
{
    Vec2f actualPos = pos + parentPos;

    bool block = UIComponent::handleMouseButtonChange(button, position, pressed, parentPos);


    if(block == false)
    {
        if(button == sf::Mouse::Left && pressed == true)
        {
            if(posIsOnComponent(position, actualPos))
            {
                state = State::SELECTED;

                block = true;

                //Broadcast this to the parent if there is one
                if(parent != NULL)
                {
                    parent->onInputChange(this);
                }
            }
        }
    }
    return block;
}
void ImgListElement::setPosition(Vec2f pos)
{
    this->pos = pos;
}

bool ImgListElement::boolValue()
{
    return state == State::SELECTED;
}
void ImgListElement::setValue(bool val)
{
    if(val == false)
    {
        this->state = State::DEFAULT;
    }
    else
    {
        this->state = State::SELECTED;
    }
}
std::string ImgListElement::getValueName()
{
    return this->valueName;
}

///////////////////////////////////////////////////////////////////////////////////////
//                          Private functions
///////////////////////////////////////////////////////////////////////////////////////

