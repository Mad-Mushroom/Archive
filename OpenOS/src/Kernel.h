/* OpenOS Kernel
 *
 * Made by MadMushroom
 * 
 * Copyright (c) 2023 MadMushroom
 */

#pragma once

void license();
void shutdown(bool noShowMode);

void ALPHA();
void BETA();

/* Misc */
#include "misc/OS_Info.h"
#include "misc/KBScanCodeSet1.h"
#include "misc/TextModeColorCodes.h"
#include "misc/Typedefs.h"

/* System */
#include "system/panic.cpp"
#include "system/IO.cpp"
#include "system/IDT.cpp"
#include "system/memory/MemoryMap.cpp"
#include "system/memory/memory.cpp"
#include "system/memory/heap.cpp"

/* Driver */
#include "driver/VGA_Screen.cpp"
#include "driver/Keyboard.cpp"

/* Shell */
#include "shell/shell.cpp"
