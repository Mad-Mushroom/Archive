#pragma once

#include "../engine.h"

using namespace std;

class GUIElement {
public:
    string Name;
    bool clicked;

    Vector_2 Position;
    Vector_2 Size;

    const char* Text;
    Font font;
    int FontSize;
    Color ForegroundColor;
    Color BackgroundColor;

    void DrawElement();
};

class GuiClass {
public:
    vector<GUIElement> Elements;
    int ElementCount;

    Font DefaultFont;

    void AddElement(GUIElement element);
    void SetDefaultFont(Font font);
};

extern GuiClass GUI;