#pragma once

#include "main.h"

/* color stuff */
struct ColorRGB {
    int red,green,blue;
};

struct Colors {
    const ColorRGB black = {0,0,0};
    const ColorRGB white = {255,255,255};
    const ColorRGB red = {255,0,0};
    const ColorRGB green = {0,255,0};
    const ColorRGB blue = {0,0,255};
    const ColorRGB yellow = {255,255,0};
    const ColorRGB magenta = {255,0,255};
    const ColorRGB cyan = {0,255,255};
};

extern Colors colors;

bool to_bool(std::string const& s) {
     return s != "0";
}