#include "renderer.h"

void r_drawPixel(int x, int y, int color){
    gfx_SetColor(color);
    gfx_SetPixel(x, y);
}

void r_drawStraightLine(int x, int y, int length, int direction, int color){
    if(direction == 0){
        for(int i=x; i<length; i++){
            r_drawPixel(i, y, color);
        }
    }
    if(direction == 1){
        for(int i=y; i<length; i++){
            r_drawPixel(x, i, color);
        }
    }
}

void r_drawRect(int x, int y, int width, int height, int color){
    for(int i=x; i<width; i++){
        for(int j=y; j<height; j++){
            r_drawPixel(i, j, color);
        }
    }
}

void r_draw2DRays(int[] mapdata){

}