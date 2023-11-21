/* OpenOS OS Info
 *
 * Made by MadMushroom
 * 
 * Copyright (c) 2023 MadMushroom
 */

#pragma once

#include "compileinfo.h"

#define VERBOSE false
#define LIGHT false

#define OS_VERSION "OpenOS Pre-Alpha [v0.6.6]"
#define OTHER_VERSION "OpenKernel [v0.6.2]\nShell [v0.6.5]\n"
#define BUILD_VERSION BUILD_NUMBER // Month;Day;Year;BuildNumber

#if VERBOSE == true
#define SVERSION "Dev Edition\n"
#endif
#if LIGHT == true
#define SVERSION "Light Edition\n"
#endif
#if VERBOSE == false && LIGHT == false
#define SVERSION "\n"
#endif

#define DEFAULT_BACKGROUND BACKGROUND_BLUE
#define DEFAULT_FOREGROUND FOREGROUND_WHITE