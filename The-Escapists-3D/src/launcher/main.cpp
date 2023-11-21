#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include <math.h>

using namespace std;

struct Options {
    bool fullscreen;
};

Options options;

void startGame(Options options){
    string args;
    string command = "bin/escapists3d -launched " + args;
    if(options.fullscreen) args += "-fullscreen ";
    system(command.c_str());
    exit(0);
}

void drawButtons(){
    for(int i=640-200; i<640; i++){
        for(int j=360-50; j<360; j++){
            glPointSize(1);
            glColor3ub(255,255,255);
            glBegin(GL_POINTS);
            glVertex2i(i,j);
            glEnd();
        }
    }
}

void drawBackground(){
    for(int i=0; i<640; i++){
        for(int j=0; j<360; j++){
            glPointSize(1);
            glColor3ub(2,39,206);
            glBegin(GL_POINTS);
            glVertex2i(i,j);
            glEnd();
        }
    }
}

void init(){
    glClearColor(0,0.5,1.32,0);
}

void display(){
    drawBackground();
    drawButtons();
    glutPostRedisplay();
    glutSwapBuffers();
}

void ButtonDown(unsigned char key,int x,int y){
    if(key==32) startGame(options);
    if(key=='\n') startGame(options);
    glutPostRedisplay();
}

void ButtonUp(unsigned char key,int x,int y){
    glutPostRedisplay();
}

void SButtonDown(int key,int x,int y){
    if(key == GLUT_KEY_F11){
        options.fullscreen = true;
    }
}

void MouseDown(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(x > 640-200 && y > 360-50) startGame(options);
    }
}

void resize(int w,int h){
    glutReshapeWindow(960,640);
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,360);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-640/2 ,glutGet(GLUT_SCREEN_HEIGHT)/2-360/2);
    glutCreateWindow("The Escapists 3D Launcher");
    gluOrtho2D(0,640,360,0);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);
    glutSpecialFunc(SButtonDown);
    glutMouseFunc(MouseDown);
    glutMainLoop();
}