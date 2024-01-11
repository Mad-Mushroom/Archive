/*
 * Mad2D - MadEngine
 * Made by MadMushroom
 * 
 * licensed under GNU Generic Public License
 * <https://www.gnu.org/licenses/gpl-3.0.en.html>
 */

#include "timer.h"

void Timer::StartTimer(float lifetime){
    this->Lifetime = lifetime;
}

void Timer::UpdateTimer(){
    if(this->Lifetime > 0) this->Lifetime -= GetFrameTime();
}

bool Timer::TimerDone(){
    return this->Lifetime <= 0;
}