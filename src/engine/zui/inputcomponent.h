#ifndef H_INPUTCOMPONENT
#define H_INPUTCOMPONENT

#include <string>
#include <vector>

#include "../vec2f.h"

namespace zui
{
    class InputComponent
    {
    public:
        InputComponent(std::string name);

        virtual bool boolValue();
        virtual int intValue();
        virtual float floatValue();
        virtual std::string stringValue();
        
        virtual void setValue(bool val);
        virtual void setValue(int val);
        virtual void setValue(float val);
        virtual void setValue(std::string val);

        std::string getName();
    private:
        std::string name;
    
        bool valueChanged;
    };
}
#endif
