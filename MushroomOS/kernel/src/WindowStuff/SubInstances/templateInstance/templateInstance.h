#pragma once
#include "../../../OSDATA/userdata.h"
#include "../defaultInstance/defaultInstance.h"
//#include "../../../customClasses/list.h"
#include "../../Window/window.h"



class TemplateInstance : public DefaultInstance
{
public:
    private:
        Window* window;

    public:
        char userInput[260];
        int inputLen = 0;
        uint32_t bgCol;

    public:
    TemplateInstance(Window* window);
    void Init();
    void Free();
};