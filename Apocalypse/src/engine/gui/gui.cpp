#include "gui.h"

void GUIElement::DrawElement(){
    DrawRectangle(Position.x, Position.y, Position.x, Position.y, BackgroundColor);
    DrawTextEx(font, Text, {Position.x, Position.y}, FontSize, 2, ForegroundColor);

    clicked = false;

    if(GetMousePosition().x >= Position.x && GetMousePosition().x <= Position.x + Position.x){
        if(GetMousePosition().y >= Position.y && GetMousePosition().y <= Position.y + Position.y){
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) clicked = true;
        }
    }
}

void GuiClass::AddElement(GUIElement element){
    Elements.push_back(element);
    ElementCount++;
}

void GuiClass::SetDefaultFont(Font font){
    DefaultFont = font;
}