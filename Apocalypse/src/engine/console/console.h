/*
 * Mad2D - MadEngine
 * Made by MadMushroom
 * 
 * licensed under GNU Generic Public License
 * <https://www.gnu.org/licenses/gpl-3.0.en.html>
 */

#pragma once

#include "../engine.h"

class ConsoleClass {
public:
    int TotalLogs;
    int TotalWarnings;
    int TotalErrors;

    void Print(const char* text);
    void Log(const char* message);
    void Error(const char* message);
    void Warning(const char* message);
};

extern ConsoleClass Console;