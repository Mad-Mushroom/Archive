#pragma once

#include "main.h"

void r_drawPixel(int x, int y, int color);
void r_drawStraightLine(int x, int y, int length, int direction, int color);
void r_drawRect(int x, int y, int width, int height, int color);
void r_draw2DRays(int[] mapdata);