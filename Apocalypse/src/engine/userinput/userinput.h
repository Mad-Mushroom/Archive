/*
 * Mad2D - MadEngine
 * Made by MadMushroom
 * 
 * licensed under GNU Generic Public License
 * <https://www.gnu.org/licenses/gpl-3.0.en.html>
 */

#pragma once

#include "../engine.h"

class UserInputClass {
public:
    bool KeyDown(int key);
    bool KeyPressed(int key);
    bool KeyReleased(int key);
    bool KeyUp(int key);

    bool MouseDown(int key);
    bool MousePressed(int key);
    bool MouseReleased(int key);
    bool MouseUp(int key);

    Vector_2 MousePosition();
};

extern UserInputClass UserInput;