#pragma once
#include "../../../OSDATA/userdata.h"
#include "../defaultInstance/defaultInstance.h"
//#include "../../../customClasses/list.h"
#include "../../Window/window.h"
#include "../connect4Instance/connect4Instance.h"
#include "../../../OSDATA/osdata.h"
#include "../../../customClasses/syncedList.h"



class ProgramMenuInstance : public DefaultInstance
{
public:
    private:
        Window* window;

    public:
        int lineNumber;
        uint32_t bgCol;

    public:
        ProgramMenuInstance(Window* window);
        void Init();
        void GetInput(char input);
        void StartTerminal();
        void StartConnect4();
        void Shutdown();
};