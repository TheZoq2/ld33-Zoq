#include "inputcomponent.h"

using namespace zui;

InputComponent::InputComponent(std::string name)
{
    this->name = name;
}

std::string InputComponent::getName()
{
    return this->name;
}

bool InputComponent::boolValue()
{
    std::cout << "Component " << name << " does not support bool values. Returning false" << std::endl;
    return false;
}
int InputComponent::intValue()
{
    std::cout << "Component " << name << " does not support int values. Returning 0" << std::endl;
    return 0;
}
float InputComponent::floatValue()
{
    std::cout << "Component " << name << " does not support float values. Returning 0" << std::endl;
    return false;
}
std::string InputComponent::stringValue()
{
    std::cout << "Component " << name << " does not support bool values. Returning ''" << std::endl;
    return "";
}

void InputComponent::setValue(bool val)
{
    std::cout << "Component " << name << " can not be set to a bool value (" << val << ")" << std::endl;
}
void InputComponent::setValue(int val)
{
    std::cout << "Component " << name << " can not be set to a int value (" << val << ")" << std::endl;
}
void InputComponent::setValue(float val)
{
    std::cout << "Component " << name << " can not be set to a float value (" << val << ")" << std::endl;
}
void InputComponent::setValue(std::string val)
{
    std::cout << "Component " << name << " can not be set to a string value (" << val << ")" << std::endl;
}
