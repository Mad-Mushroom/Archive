#include "programMenuInstance.h"
#include "../../../cmdParsing/cstrTools.h"
#include "../../../memory/heap.h"
#include "../../../kernelStuff/stuff/cstr.h"

ProgramMenuInstance::ProgramMenuInstance(Window* window){
    this->window = window;
    this->instanceType = InstanceType::Default;
}

void ProgramMenuInstance::Init(){
    bgCol = 0x00000000;
    window->renderer->color = Colors.white;
    window->renderer->Clear(bgCol);
    window->renderer->putStr("== MushroomOS Manager ==", 1, 9*0);
    window->renderer->putStr("------------------------", 1, 9*1);
    window->renderer->putStr("= Programs =", 1, 9*4);
    window->renderer->putStr("[1] Terminal", 1, 9*6);
    window->renderer->putStr("[2] Connect 4", 1, 9*8);
    window->renderer->putStr("= Options =", 1, 9*12);
    window->renderer->putStr("[3] Shutdown", 1, 9*14);
    //window->renderer->putStr("*Type Number of program*", 1, 9*10);
    lineNumber = 10;
}

void ProgramMenuInstance::StartTerminal(){
    AddToStack();
            Window* oldActive = activeWindow;
            Window* mainWindow = (Window*)malloc(sizeof(Window), "Main Window");
            TerminalInstance* terminal = (TerminalInstance*)malloc(sizeof(TerminalInstance), "Terminal Instance");
            *terminal = TerminalInstance(&guestUser);
            *(mainWindow) = Window((DefaultInstance*)terminal, Size(600, 500), Position(10, 40), "MushroomOS Terminal", true, true, true);
            osData.windows.add(mainWindow);
            terminal->SetWindow(mainWindow);
            ((TerminalInstance*)mainWindow->instance)->Cls();
            ((TerminalInstance*)mainWindow->instance)->KeyboardPrintStart();
            activeWindow = mainWindow;          
            mainWindow->moveToFront = true;
            osData.mainTerminalWindow = mainWindow;
            if (oldActive != NULL)
            {
                osData.windowPointerThing->UpdateWindowBorder(oldActive);
            }
    RemoveFromStack();
    return;
}

void ProgramMenuInstance::StartConnect4(){
    AddToStack();
            Window* oldActive = activeWindow;
            Window* con4Window = (Window*)malloc(sizeof(Window), "Connect 4 Window");
            Connect4Instance* connect4 = (Connect4Instance*)malloc(sizeof(Connect4Instance), "Connect 4 Instance");
            *connect4 = Connect4Instance(con4Window);
            *(con4Window) = Window((DefaultInstance*)connect4, Size(200, 200), Position(10, 40), "Connect 4", true, true, true);
            osData.windows.add(con4Window);
            
            connect4->Init();
            
            activeWindow = con4Window;          
            con4Window->moveToFront = true;
            osData.mainTerminalWindow = con4Window;

            if (oldActive != NULL)
            {
                osData.windowPointerThing->UpdateWindowBorder(oldActive);
            }

    RemoveFromStack();
    return;
}

void ProgramMenuInstance::Shutdown(){
    osData.exit = true;
    return;
}

void ProgramMenuInstance::GetInput(char input){  
    if(input == '1'){
        StartTerminal();
    }
    if(input == '2'){
        StartConnect4();
    }
    if(input == '3'){
        Shutdown();
    }
    return;
}