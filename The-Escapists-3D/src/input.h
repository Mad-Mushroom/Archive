#pragma once

#include "main.h"

void ButtonDown(unsigned char key,int x,int y){
    if(key=='a') Keys.a=1;
    if(key=='d') Keys.d=1;
    if(key=='w') Keys.w=1;
    if(key=='s') Keys.s=1;
    if(key=='q') Keys.q=1;
    if(key=='\n') Keys.enter=1;
    if(key==32) Keys.space=1;
    if(key=='e'){
        Keys.e=1;
        int xo=0;
        if(pdx<0){
            xo=-25;
        }
        else{
            xo=25;
        }
        int yo=0;
        if(pdy<0){
            yo=-25;
        }
        else{
            yo=25;
        }
        int ipx_add_xo=(px+xo)/64.0;
        int ipy_add_yo=(py+yo)/64.0;
        if(mapW[player.currentMap][ipy_add_yo*mapX+ipx_add_xo]==4){
            mapW[player.currentMap][ipy_add_yo*mapX+ipx_add_xo]=0;
        }
    }
    if(key == 27) Keys.esc=1;

    glutPostRedisplay();
}

void ButtonUp(unsigned char key,int x,int y){
    if(key=='a') Keys.a=0;
    if(key=='d') Keys.d=0;
    if(key=='w') Keys.w=0;
    if(key=='s') Keys.s=0;
    if(key=='e') Keys.e=0;
    if(key=='q') Keys.q=0;
    if(key=='\n') Keys.enter=0;
    if(key==32) Keys.space=0;
    if(key == 27) Keys.esc=0;
    mainMenu.canAdvance = true;
    glutPostRedisplay();
}

void SButtonDown(int key,int x,int y){
    if(key == GLUT_KEY_F11) toggleFullscreen();
}