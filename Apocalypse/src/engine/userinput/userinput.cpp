/*
 * Apocalypse Engine
 * Made by MadMushroom
 * 
 * licensed under GNU Generic Public License
 * <https://www.gnu.org/licenses/gpl-3.0.en.html>
 */

#include "userinput.h"

bool UserInputClass::KeyDown(int key){
    return IsKeyDown(key);
}

bool UserInputClass::KeyPressed(int key){
    return IsKeyPressed(key);
}

bool UserInputClass::KeyReleased(int key){
    return IsKeyReleased(key);
}

bool UserInputClass::KeyUp(int key){
    return IsKeyUp(key);
}

bool UserInputClass::MouseDown(int key){
    return IsMouseButtonDown(key);
}

bool UserInputClass::MousePressed(int key){
    return IsMouseButtonPressed(key);
}

bool UserInputClass::MouseReleased(int key){
    return IsMouseButtonReleased(key);
}

bool UserInputClass::MouseUp(int key){
    return IsMouseButtonUp(key);
}

Vector_2 UserInputClass::MousePosition(){
    return {GetMousePosition().x, GetMousePosition().y};
}