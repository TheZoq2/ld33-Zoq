#ifndef H_VEC2F
#define H_VEC2F

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Vec2f : public sf::Vector2f 
{
public:
    Vec2f();
    Vec2f(const sf::Vector2f& other);
    Vec2f(float x, float y);

    float length();

    Vec2f& operator=(const Vec2f& other);
    Vec2f& operator=(const sf::Vector2f& other);

    operator sf::Vector2i();
};
#endif
