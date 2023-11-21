#include "kernelStuff/stuff/kernelUtil.h"
#include "OSDATA/osStats.h"
#include "WindowStuff/SubInstances/guiInstance/guiInstance.h"
#include "WindowStuff/SubInstances/guiInstance/guiStuff/components/rectangle/rectangleComponent.h"
#include "WindowStuff/SubInstances/guiInstance/guiStuff/components/box/boxComponent.h"
#include "WindowStuff/SubInstances/guiInstance/guiStuff/components/text/textComponent.h"
#include "WindowStuff/SubInstances/guiInstance/guiStuff/components/button/buttonComponent.h"
#include "WindowStuff/SubInstances/guiInstance/guiStuff/components/textField/textFieldComponent.h"

void TestClickHandler(GuiComponentStuff::BaseComponent* btn, GuiComponentStuff::MouseClickEventInfo info)
{
    btn->position.y += 20;
}

void TestKeyHandler(GuiComponentStuff::BaseComponent* btn, GuiComponentStuff::KeyHitEventInfo info)
{
    btn->position.y -= 20;
}

uint8_t port64Val = 0;
bool keyboardWeird = false;
bool oldKeyboardWeird = false;

void IO_CHECK()
{
    uint8_t t = inb(0x64);
    if (t == 0x1C)
        return;
    port64Val = t;

    uint64_t now = PIT::TimeSinceBootMS();
    if (port64Val == 0x1D && (now - osStats.lastKeyboardCall > 4000))
    {
        port64Val = inb(0x60);
        keyboardWeird = true;
        
        uint8_t real = TranslateScancode2(port64Val);
        
        if (KeyboardScancodeState[real])
            HandleKeyboard(real | (0b10000000));
        else
            HandleKeyboard(real & (~0b10000000));
    }
    else if ((port64Val & 0b1 == 1) && (now - osStats.lastMouseCall > 2000))
    {
        uint8_t b = inb(0x60);
    }
}


extern "C" void _start(BootInfo* bootInfo)
{  
    osData.booting = false;
    osData.maxNonFatalCrashCount = 5;
    MStackData::stackPointer = 0;
    for (int i = 0; i < 1000; i++)
        MStackData::stackArr[i] = MStack();
    
    osData.enableStackTrace = RECORD_STACK_TRACE;
    AddToStack();
    osData.crashCount = 0;

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    osData.osTasks = List<Task*>(4);


    osData.kernelInfo = &kernelInfo;
    osData.exit = false;

    Window* debugTerminalWindow = osData.debugTerminalWindow;
    
    osData.drawBackground = true;
    
    
    GlobalRenderer->Clear(Colors.black);
    GlobalRenderer->DrawImage(bootInfo->bootImage, 0, 0, 1, 1);
    osData.booting = true;

    if (PIT::TicksSinceBoot != 0)
    {
        uint64_t endTime = PIT::TimeSinceBootMS() + 1000;
        while (PIT::TimeSinceBootMS() < endTime && osData.booting)
            asm("hlt");
        osData.booting = false;
    }
    else
    {
        GlobalRenderer->CursorPosition.x = 0;
        GlobalRenderer->CursorPosition.y = 0;
        
        GlobalRenderer->color = Colors.bred;
        GlobalRenderer->Println("ERROR: Interrupts are not working properly!");
        GlobalRenderer->color = Colors.yellow;
        GlobalRenderer->Println("Please reboot the system.");

        while (true)
            asm("hlt");
    }
    
    GlobalRenderer->Clear(Colors.black);

    Window* mainWindow;
    {
        mainWindow = (Window*)malloc(sizeof(Window), "Main window");
        TerminalInstance* terminal = (TerminalInstance*)malloc(sizeof(TerminalInstance), "Terminal Instance for main window");
        *terminal = TerminalInstance(&adminUser);

        *(mainWindow) = Window((DefaultInstance*)terminal, Size(600, 500), Position(5, 30), "Main Terminal", true, true, true);
        osData.windows.add(mainWindow);
        terminal->SetWindow(mainWindow);

        activeWindow = mainWindow;
        osData.mainTerminalWindow = mainWindow;
    }

    /*AddToStack();
    GuiInstance* testGui;
    GuiComponentStuff::BoxComponent* box;
    GuiComponentStuff::RectangleComponent* testRect;
    {
        Window* window = (Window*)malloc(sizeof(Window), "GUI Window");
        GuiInstance* gui = (GuiInstance*)malloc(sizeof(GuiInstance), "GUI Instance");
        *gui = GuiInstance(window);
        *(window) = Window((DefaultInstance*)gui, Size(400, 360), Position(500, 60), "Testing GUI Window", true, true, true);
        osData.windows.add(window);
        
        gui->Init();

        testGui = gui;

        {
            GuiComponentStuff::ComponentSize s = GuiComponentStuff::ComponentSize(60, 20);
            s.IsXFixed = false;
            s.ScaledX = 0.5;
            testRect = new GuiComponentStuff::RectangleComponent(Colors.purple, s, testGui->screen);
            testRect->position = GuiComponentStuff::Position(100, 20);
        }


        {
            box = new GuiComponentStuff::BoxComponent(
                testGui->screen, GuiComponentStuff::ComponentSize(240, 240), Colors.tblack
            );
            testGui->screen->children->add(box);
            box->position = GuiComponentStuff::Position(20, 30);

            {
                GuiComponentStuff::RectangleComponent* t = new GuiComponentStuff::RectangleComponent(
                    Colors.dgray, GuiComponentStuff::ComponentSize(180, 180), box);
                t->position = GuiComponentStuff::Position(0, 40);
                box->children->add(t);
            }

            {
                GuiComponentStuff::RectangleComponent* t = new GuiComponentStuff::RectangleComponent(
                    Colors.white, GuiComponentStuff::ComponentSize(20, 20), box);
                t->position = GuiComponentStuff::Position(40, 80);
                box->children->add(t);
            }

            {
                GuiComponentStuff::RectangleComponent* t = new GuiComponentStuff::RectangleComponent(
                    Colors.white, GuiComponentStuff::ComponentSize(20, 20), box);
                t->position = GuiComponentStuff::Position(120, 80);
                box->children->add(t);
            }

            {
                GuiComponentStuff::RectangleComponent* t = new GuiComponentStuff::RectangleComponent(
                    Colors.orange, GuiComponentStuff::ComponentSize(20, 20), box);
                t->position = GuiComponentStuff::Position(80, 120);
                box->children->add(t);
            }

            {
                GuiComponentStuff::RectangleComponent* t = new GuiComponentStuff::RectangleComponent(
                    Colors.bred, GuiComponentStuff::ComponentSize(20, 20), box);
                t->position = GuiComponentStuff::Position(20, 140);
                box->children->add(t);
            }

            {
                GuiComponentStuff::RectangleComponent* t = new GuiComponentStuff::RectangleComponent(
                    Colors.bred, GuiComponentStuff::ComponentSize(20, 20), box);
                t->position = GuiComponentStuff::Position(140, 140);
                box->children->add(t);
            }

            {
                GuiComponentStuff::RectangleComponent* t = new GuiComponentStuff::RectangleComponent(
                    Colors.bred, GuiComponentStuff::ComponentSize(100, 20), box);
                t->position = GuiComponentStuff::Position(40, 160);
                box->children->add(t);
            }
        }


        {
            GuiComponentStuff::TextComponent* txt = new GuiComponentStuff::TextComponent(testGui->screen, Colors.black, Colors.white, "Hello!\nThis is an amazing test.", 
            GuiComponentStuff::Position(200, 90));
            txt->id = 993344;
            testGui->screen->children->add(txt);
        }

        {
            GuiComponentStuff::ButtonComponent* btn = new GuiComponentStuff::ButtonComponent("CLICK\nME\nPLS", 
            Colors.black, Colors.dgray, Colors.gray, 
            Colors.bgreen, Colors.yellow, Colors.bred, 
            GuiComponentStuff::ComponentSize(150, 80),
            GuiComponentStuff::Position(210, 160), testGui->screen
            );
            btn->mouseClickedCallBack = TestClickHandler;
            btn->keyHitCallBack = TestKeyHandler;
            btn->id = 995544;
            
            testGui->screen->children->add(btn);
        }

        {
            GuiComponentStuff::TextFieldComponent* txtField = new GuiComponentStuff::TextFieldComponent(
            Colors.white,
            Colors.black,
            GuiComponentStuff::ComponentSize(150, 80),
            GuiComponentStuff::Position(100, 260), testGui->screen
            );
            
            testGui->screen->children->add(txtField);
        }

        testGui->screen->children->add(testRect);


        {
            uint64_t bleh = 0;
            *((int*)&bleh) = 1;
            testGui->SetBaseComponentAttribute(993344, GuiInstanceBaseAttributeType::POSITION_Y, bleh);
        }

        {
            uint64_t bleh = 0;
            *((uint32_t*)&bleh) = Colors.red;
            testGui->SetSpecificComponentAttribute(995544, 10, bleh);
        }

        {
            uint64_t bleh = 0;
            *((double*)&bleh) = 0.3;
            testGui->SetBaseComponentAttribute(995544, GuiInstanceBaseAttributeType::SIZE_SCALED_Y, bleh);
        }

        {
            uint64_t bleh = 0;
            *((bool*)&bleh) = false;
            testGui->SetBaseComponentAttribute(995544, GuiInstanceBaseAttributeType::SIZE_IS_FIXED_Y, bleh);
        }
    }
    RemoveFromStack();*/
    
    osData.windows.add(osData.debugTerminalWindow);

    osData.showDebugterminal = false;
            osData.windowPointerThing->UpdatePointerRect(
                osData.debugTerminalWindow->position.x - 1, 
                osData.debugTerminalWindow->position.y - 23, 
                osData.debugTerminalWindow->position.x + osData.debugTerminalWindow->size.width, 
                osData.debugTerminalWindow->position.y + osData.debugTerminalWindow->size.height
                );

    debugTerminalWindow->Log("Kernel initialised successfully!");

    //for (int i = 0; i < 8; i++)
    //    debugTerminalWindow->Log("<STAT>");
    //debugTerminalWindow->renderer->CursorPosition.y = 16 * 16;

    ((TerminalInstance*)mainWindow->instance)->Cls();
    ((TerminalInstance*)mainWindow->instance)->KeyboardPrintStart();
    
    osData.windowPointerThing->Clear();
    osData.windowPointerThing->RenderWindows();
    bool updateBorder = true;
    bool bgm = osData.drawBackground;
    int frame = 0;
    int tFrame = 0;
    uint64_t oldTime = PIT::TimeSinceBootMS();
    uint64_t fps = 1;

    uint64_t frameSum = 0;

    osData.wantedFps = 150;
    uint32_t TwantedFps = 1000;
    uint64_t timeForFps = 1000;


    while(!osData.exit)
    {
        AddToStack();
        freeCount = 0;
        mallocCount = 0;
        osStats.frameStartTime = PIT::TimeSinceBootMicroS();


        if (TwantedFps != osData.wantedFps)
        {
            TwantedFps = osData.wantedFps;
            timeForFps = 1000000 / osData.wantedFps;
        }

        if (++tFrame >= 1000)
            tFrame = 0;

        frame++;  
        if (frame >= 30)
        {
            uint64_t currTime = PIT::TimeSinceBootMS();
            if ((currTime - oldTime) == 0)
            {
                fps = 9999;
            }
            else
                fps = ((frame - 1)*1000) / (currTime - oldTime);
            oldTime = currTime;
            frame = 0;
        }
        RemoveFromStack();

        //testRect->position.x = frame * 5;

        //box->position.x = frame * 6;

        ProcessMousePackets();

        if (bgm != osData.drawBackground)
        {
            osData.windowPointerThing->RenderWindows();
            bgm = osData.drawBackground;
        }

        AddToStack();
        {
            uint64_t tS = PIT::TimeSinceBootMicroS();

            if (activeWindow != NULL)
            {
                updateBorder = true;
                if (activeWindow->moveToFront)
                {
                    activeWindow->moveToFront = false;
                    int index = osData.windows.getIndexOf(activeWindow);
                    if (index == osData.windows.getCount() - 1)
                    {
                        osData.windowPointerThing->UpdateWindowBorder(activeWindow);
                        osData.windowPointerThing->RenderWindow(activeWindow);
                    }
                    else if (index != -1)
                    {
                        Window* oldActive = osData.windows[osData.windows.getCount() - 1];
                        osData.windows.removeAt(index);
                        osData.windows.add(activeWindow);
                        
                        osData.windowPointerThing->UpdateWindowBorder(oldActive);

                        osData.windowPointerThing->RenderWindow(activeWindow);
                        osData.windowPointerThing->UpdateWindowBorder(activeWindow);
                    }
                }
            }
            else
            {
                if (updateBorder)
                {
                    updateBorder = false;
                    {
                        Window* oldActive = osData.windows[osData.windows.getCount() - 1];
                        
                        osData.windowPointerThing->UpdateWindowBorder(oldActive);
                    }
                }
            }

            for (int i = 0; i < osData.windows.getCount(); i++)
            {            
                Window* window = osData.windows[i];

                if (window == osData.debugTerminalWindow && !osData.showDebugterminal)
                    continue;
                
                if (window->hidden != window->oldHidden)
                {
                    window->oldHidden = window->hidden;
                    osData.windowPointerThing->UpdatePointerRect(
                        window->position.x - 1, 
                        window->position.y - 23, 
                        window->position.x + window->size.width, 
                        window->position.y + window->size.height
                        );
                }

                {
                    int x1 = window->position.x - 1;
                    int y1 = window->position.y - 23;
                    int sx1 = window->size.width + 3;
                    int sy1 = window->size.height + 25;

                    bool update = false;

                    int x2 = x1;
                    int y2 = y1;
                    int sx2 = sx1;
                    int sy2 = sy2;

                    Size nSize = window->newSize;
                    Position nPos = window->newPosition;


                    if (window->size != nSize)
                    {
                        window->Resize(nSize);
                        {
                            x2 = window->position.x - 1;
                            y2 = window->position.y - 23;
                            sx2 = window->size.width + 3;
                            sy2 = window->size.height + 25;

                            update = true;
                        }
                    }

                    if (window->position != nPos)
                    {
                        window->position = nPos;

                        x2 = window->position.x - 1;
                        y2 = window->position.y - 23;
                        sx2 = window->size.width + 3;
                        sy2 = window->size.height + 25;

                        update = true;
                    }

                    if (update)
                    {
                        int rx1 = min(x1, x2);
                        int ry1 = min(y1, y2);
                        int rx2 = max(x1 + sx1, x2 + sx2);
                        int ry2 = max(y1 + sy1, y2 + sy2);

                        int AR = (rx2 - rx1) * (ry2 - ry1);
                        int A1 = sx1 * sy1;
                        int A2 = sx2 * sy2;

                        if (AR <= A1+A2)
                        {
                            osData.windowPointerThing->UpdatePointerRect(rx1, ry1, rx2, ry2);
                        }
                        else
                        {
                            osData.windowPointerThing->UpdatePointerRect(x1, y1, x1 + sx1, y1 + sy1);
                            osData.windowPointerThing->UpdatePointerRect(x2, y2, x2 + sx2, y2 + sy2);
                        }
                    }
                }
                if (window->instance != NULL && (activeWindow == window || frame % 10 == (i%8)))
                {
                    if (window->instance->instanceType == InstanceType::Terminal)
                    {
                        TerminalInstance* termInst1 = (TerminalInstance*)window->instance;
                        if (termInst1->newTermInstance != NULL)
                        {
                            NewTerminalInstance* termInst2 = (NewTerminalInstance*)termInst1->newTermInstance;
                            termInst2->DoRender();
                        }
                    }   
                    else if (window->instance->instanceType == InstanceType::GUI)
                    {
                        GuiInstance* guiInst = (GuiInstance*)window->instance;
                        guiInst->Render();
                    }   
                }
                
            }

            osStats.totalWindowUpdateTime = PIT::TimeSinceBootMicroS() - tS;
        }
        RemoveFromStack();



        {
            uint64_t tS = PIT::TimeSinceBootMicroS();
            AddToStack();
            Taskbar::RenderTaskbar();
            MPoint mPos = MousePosition;
            DrawMousePointer2(osData.windowPointerThing->virtualScreenBuffer, mPos);
            osData.windowPointerThing->fps = fps;
            osData.windowPointerThing->Render();
            osData.windowPointerThing->UpdatePointerRect(mPos.x - 32, mPos.y - 32, mPos.x + 32, mPos.y + 32);
            osStats.totalRenderTime = PIT::TimeSinceBootMicroS() - tS;
            RemoveFromStack();
        }



        {
            AddToStack();
            uint64_t totTaskTemp = 0;
            uint64_t totOsTaskTemp = 0;

            uint64_t tS1 = PIT::TimeSinceBootMicroS();
            uint64_t tempVal = osStats.frameStartTime + timeForFps;


            {
                for (int i = 0; i < osData.windows.getCount(); i++)
                {     
                    Window* window = osData.windows[i];
                    if (window->instance == NULL)
                        continue;
                    if (window->instance->instanceType != InstanceType::Terminal)
                        continue;

                    TerminalInstance* terminal = (TerminalInstance*)window->instance;

                    if (terminal->tasks.getCount() != 0)
                    {
                        Task* task = terminal->tasks[0];
                        task->tempTime = 0;
                    }
                }
            }

            bool startThing = true;
            while (PIT::TimeSinceBootMicroS() < tempVal || startThing)
            {
                startThing = false;
                {
                    uint64_t tS = PIT::TimeSinceBootMicroS();
                    {
                        for (int i = 0; i < osData.windows.getCount(); i++)
                        {     
                            Window* window = osData.windows[i];
                            if (window->instance == NULL)
                                continue;
                            if (window->instance->instanceType != InstanceType::Terminal)
                                continue;

                            TerminalInstance* terminal = (TerminalInstance*)window->instance;

                            if (terminal->tasks.getCount() != 0)
                            {
                                uint64_t tS2 = PIT::TimeSinceBootMicroS();
                                Task* task = terminal->tasks[0];
                                DoTask(task);
                                task->tempTime += PIT::TimeSinceBootMicroS() - tS2;
                                if (task->GetDone())
                                {
                                    terminal->tasks.removeFirst();
                                    FreeTask(task);
                                    terminal->PrintUserIfNeeded();
                                }
                                else
                                {
                                    
                                    //Task not done
                                }
                            }
                        }
                    }
                    totTaskTemp += PIT::TimeSinceBootMicroS() - tS;
                }
                

                {
                    uint64_t tS = PIT::TimeSinceBootMicroS();
                    if (osData.osTasks.getCount() > 0)
                    {
                        uint64_t tS2 = PIT::TimeSinceBootMicroS();
                        Task* task = osData.osTasks[0];
                        DoTask(task);
                        task->tempTime += PIT::TimeSinceBootMicroS() - tS2;
                        if (task->GetDone())
                        {
                            osData.osTasks.removeFirst();
                            FreeTask(task);
                        }
                    }
                    totOsTaskTemp += PIT::TimeSinceBootMicroS() - tS;
                }
            }

            {
                for (int i = 0; i < osData.windows.getCount(); i++)
                {     
                    Window* window = osData.windows[i];
                    if (window->instance == NULL)
                        continue;
                    if (window->instance->instanceType != InstanceType::Terminal)
                        continue;

                    TerminalInstance* terminal = (TerminalInstance*)window->instance;

                    if (terminal->tasks.getCount() != 0)
                    {
                        Task* task = terminal->tasks[0];
                        task->actTime = task->tempTime;
                    }
                }
            }

            osStats.totalIdleTime = PIT::TimeSinceBootMicroS() - tS1;
            osStats.totalTaskTime = totTaskTemp;
            osStats.totalOsTaskTime = totOsTaskTemp;
            RemoveFromStack();
        }

        IO_CHECK();
        osStats.testThing = port64Val;
        if (keyboardWeird && !oldKeyboardWeird)
        {
            oldKeyboardWeird = true;
            
            Window* msgWindow;
            {


                msgWindow = (Window*)malloc(sizeof(Window), "Warning Window");
                Size size = Size(800, 16*10);
                Position pos = Position(((GlobalRenderer->framebuffer->Width - size.width) / 2), ((GlobalRenderer->framebuffer->Height) / 5));
                
                if (msgWindow != NULL)
                {
                    *(msgWindow) = Window(NULL, size, pos, "WARNING ABOUT YOUR PS/2 KEYBOARD", true, true, true);
                    osData.windows.add(msgWindow);

                    activeWindow = msgWindow;
                    msgWindow->moveToFront = true;
                }
            }
            
            if (msgWindow != NULL)
            {
                msgWindow->renderer->Clear(Colors.black);
                msgWindow->renderer->Println("------------------------------------------------", Colors.bred);
                msgWindow->renderer->Println("WARNING: Your PS/2 Keyboard is having issues!", Colors.bred);
                msgWindow->renderer->Println("------------------------------------------------", Colors.bred);
                msgWindow->renderer->Println();
                msgWindow->renderer->Println("It should still work but it will probably cause issues if used with the mouse at the same time.", Colors.yellow);
                msgWindow->renderer->Println("The issue should be fixable with a restart.", Colors.yellow);
                msgWindow->renderer->Println();

            }

            msgWindow->hidden = false;
            msgWindow->oldHidden = true;


            

        }

        osStats.frameEndTime = PIT::TimeSinceBootMicroS();
        osStats.totalFrameTime = osStats.frameEndTime - osStats.frameStartTime;
    }

    GlobalRenderer->Clear(Colors.black);
    GlobalRenderer->color = Colors.white;
    GlobalRenderer->Println("Shutting Down...\n");
    PIT::Sleep(800);
    GlobalRenderer->Println("Goodbye :)");
    PIT::Sleep(100);
    GlobalRenderer->Clear(Colors.black);

    RemoveFromStack();
    return;
}