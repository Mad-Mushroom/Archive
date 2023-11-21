#include "main.h"

int main(void){
    gfx_Begin();

    while(!os_GetCSC()){
        r_draw2DRays(testMap);
    }
    gfx_End();

    return 0;
}