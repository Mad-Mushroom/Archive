/* OpenOS stdio
 *
 * Made by MadMushroom
 * 
 * Copyright (c) 2023 MadMushroom
 */

#pragma once

#include "../Kernel.h"

void printf(const char* str, uint_8 color = DEFAULT_BACKGROUND | DEFAULT_FOREGROUND){
    PrintString(str, color);
}