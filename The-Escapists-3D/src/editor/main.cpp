#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include <math.h>

using namespace std;

#define mapX 64      //map width
#define mapY 64      //map height

extern int mapW[mapX * mapY];
extern int mapF[mapX * mapY];
extern int mapC[mapX * mapY];
extern int mapO[mapX * mapY];
extern int mapOZ[mapX * mapY];

void drawMap(){
    for(int x=0; x<32; x++){
        for(int y=0; y<32; y++){
            int pixel=(y*1536+x)*3;
            //int red   =font[pixel+0];
            //int green =font[pixel+1];
            //int blue  =font[pixel+2];
            glPointSize(1);
            glColor3ub(255,255,255);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
        }
    }
}

void init(){
    glClearColor(0,0.2,1.5,0);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap();
    glutPostRedisplay();
    glutSwapBuffers();
}

void ButtonDown(unsigned char key,int x,int y){
    glutPostRedisplay();
}

void ButtonUp(unsigned char key,int x,int y){
    glutPostRedisplay();
}

void SButtonDown(int key,int x,int y){
    
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280,720);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-1280/2 ,glutGet(GLUT_SCREEN_HEIGHT)/2-720/2);
    glutCreateWindow("The Escapists 3D Map Editor");
    gluOrtho2D(0,1280,720,0);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);
    glutSpecialFunc(SButtonDown);
    glutMainLoop();
}