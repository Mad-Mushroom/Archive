#pragma once
#include "MStack/MStackS.h"

#include "../kernelStuff/stuff/kernelUtil.h"

#include "../WindowStuff/WindowManager/windowManager.h"

#define LIST_INCLUDE_GENERIC_DISK_INTERFACE
#define LIST_INCLUDE_TASK
#define LIST_INCLUDE_WINDOW
#include "../customClasses/list.h"
#undef LIST_INCLUDE_WINDOW
#undef LIST_INCLUDE_TASK
#undef LIST_INCLUDE_GENERIC_DISK_INTERFACE

struct OSData
{
    bool exit;
    bool booting;
    KernelInfo* kernelInfo;
    List<Window*> windows;
    List<Task*> osTasks;
    kernelFiles::ZIPFile* windowButtonZIP;
    kernelFiles::ZIPFile* windowIconZIP;
    Window* mainTerminalWindow;
    Window* debugTerminalWindow;
    bool showDebugterminal;
    bool drawBackground;
    bool enableStackTrace;
    int64_t crashCount = 0;
    int maxNonFatalCrashCount = 0;
    bool crashed = false;
    bool tempCrash = false;
    WindowManager::WindowPointerBufferThing* windowPointerThing;

    List<DiskInterface::GenericDiskInterface*> diskInterfaces;

    uint32_t wantedFps = 60;

};

extern OSData osData;