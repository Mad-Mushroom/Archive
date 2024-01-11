/*
 * Mad2D - MadEngine
 * Made by MadMushroom
 * 
 * licensed under GNU Generic Public License
 * <https://www.gnu.org/licenses/gpl-3.0.en.html>
 */

#pragma once

#include "../engine.h"

class Timer {
public:
    float Lifetime;

    void StartTimer(float lifetime);
    void UpdateTimer();
    bool TimerDone();
};