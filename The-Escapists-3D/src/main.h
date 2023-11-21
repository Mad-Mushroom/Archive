#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif
//#include <SFML/Audio.hpp>
#include <math.h>

using namespace std;

#define mapX 64      //map width
#define mapY 64      //map height
#define mapS 64      //map cube size

/* Functions */
void err(string msg);
void init();

/* Variables */
extern float px,py,pdx,pdy,pa;
extern float frame1,frame2,fps;
extern int gameState, timer;
extern float fade;
extern bool fullscreen;
extern int poiS;

typedef struct {
    int w,a,s,d,e,q,space,enter,esc;
} ButtonKeys;
extern ButtonKeys Keys;

struct Player {
    int health = 100, stamina = 100;
    int currentMap;
};
extern Player player;

typedef struct {
    int type;           //static, key, entity
    int state;          //on off
    int map;            //texture to show
    float x,y,z;        //position
} sprite;

/* Map Arrays */
extern int mapW[][mapX * mapY];
extern int mapF[][mapX * mapY];
extern int mapC[][mapX * mapY];
extern int mapO[][mapX * mapY];
extern int mapOZ[][mapX * mapY];

/* Texture Arrays */
extern int All_Textures[];
extern int lost[];
extern int sky[];
extern int title[];
extern int sprites[];
extern int won[];
extern int hud[];

extern int font[73729];

extern int mapCount;
extern string mapNames[256];
extern string currentLang[256];

extern sprite sp[4];

#include "customVariables.h"
//#include "audio.h"
#include "savegame.h"
#include "datRead.h"
#include "renderer.h"
#include "settings.h"
#include "mainmenu.h"
#include "input.h"