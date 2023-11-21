#include "main.h"

float px,py,pdx,pdy,pa;
float frame1,frame2,fps;
int gameState=0, timer=0;
float fade=0;
bool fullscreen = false;
int poiS = 8;

ButtonKeys Keys;
Colors colors;
mainmenu mainMenu;
Player player;
Settings settings;

int All_Textures[196609];
int lost[28801];
int sky[28801];
int title[28801];
int sprites[9217];
int won[28801];
int hud[28801];

int font[73729];

int mapW[256][mapX * mapY];
int mapF[256][mapX * mapY];
int mapC[256][mapX * mapY];
int mapO[256][mapX * mapY];
int mapOZ[256][mapX * mapY];

int mapCount;
string mapNames[256];
string currentLang[256];

sprite sp[4];

void err(string msg){
    cout << "Error! " << msg << endl;
    exit(1);
}

void init(){
    glClearColor(0,0,0,0);
    px=150;
    py=400;
    pa=90;
    pdx=cos(degToRad(pa));
    pdy=-sin(degToRad(pa));

    sp[0].type=1;
    sp[0].state=1;
    sp[0].map=0;
    sp[0].x=1.5*64;
    sp[0].y=5*64;
    sp[0].z=20; //key
    sp[1].type=2;
    sp[1].state=1;
    sp[1].map=1;
    sp[1].x=1.5*64;
    sp[1].y=4.5*64;
    sp[1].z= 0; //light 1
    sp[2].type=2;
    sp[2].state=1;
    sp[2].map=1;
    sp[2].x=3.5*64;
    sp[2].y=4.5*64;
    sp[2].z= 0; //light 2
    sp[3].type=3;
    sp[3].state=1;
    sp[3].map=2;
    sp[3].x=2.5*64;
    sp[3].y=2*64;
    sp[3].z=20; //enemy
}

void display(){
    frame2=glutGet(GLUT_ELAPSED_TIME);
    fps=(frame2-frame1);
    frame1=glutGet(GLUT_ELAPSED_TIME);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(gameState==0){
        init();
        fade=0;
        timer=0;
        gameState=1;
    }
    if(gameState==1){
        Menu();
    }
    if(gameState==2){
        if(!mainMenu.paused){
            mainMenu.currentMenu = 4;
            if(Keys.esc) pauseGame();
            if(Keys.a==1){
                pa+=0.2*fps;
                pa=FixAng(pa);
                pdx=cos(degToRad(pa));
                pdy=-sin(degToRad(pa));
            }
            if(Keys.d==1){
                pa-=0.2*fps;
                pa=FixAng(pa);
                pdx=cos(degToRad(pa));
                pdy=-sin(degToRad(pa));
            }

            int xo=0;
            if(pdx<0){
                xo=-20;
            }
            else{
                xo=20;
            }
            int yo=0;
            if(pdy<0){
                yo=-20;
            }
            else{
                yo=20;
            }
            int ipx=px/64.0, ipx_add_xo=(px+xo)/64.0, ipx_sub_xo=(px-xo)/64.0;
            int ipy=py/64.0, ipy_add_yo=(py+yo)/64.0, ipy_sub_yo=(py-yo)/64.0;
            if(Keys.w==1){
                if(mapW[player.currentMap][ipy*mapX + ipx_add_xo]==0){
                    px+=pdx*0.2*fps;
                }
                if(mapW[player.currentMap][ipy_add_yo*mapX + ipx]==0){
                    py+=pdy*0.2*fps;
                }
            }
            if(Keys.s==1){
                if(mapW[player.currentMap][ipy*mapX + ipx_sub_xo]==0){
                    px-=pdx*0.2*fps;
                }
                if(mapW[player.currentMap][ipy_sub_yo*mapX + ipx]==0){
                    py-=pdy*0.2*fps;
                }
            }
            drawSky();
            drawRays2D();
            drawObjects();
            drawHud();
        }else{
            if(mainMenu.paused) Menu();
        }
        //drawSprite();
        /*if((int)px>>6==1 && (int)py>>6==1){
            fade=0;
            timer=0;
            gameState=3;
        }*/
    }

    if(gameState==3){
        screen(lost);
        timer+=1*fps;
        if(timer>2000){
            fade=0;
            timer=0;
            gameState=0;
        }
    }
    if(gameState==4){
        screen(won);
        timer+=1*fps;
        if(timer>2000){
            fade=0;
            timer=0;
            gameState=0;
        }
    }

    glutPostRedisplay();
    glutSwapBuffers();
}

void parseArguments(int argc, char* argv[]){
    bool tmp = false;
    if(argc <= 1) return;
	std::vector<std::string> args(argv, argv+argc);
  	for (size_t i = 1; i < args.size(); ++i){
		if(args[i] == "-fullscreen") toggleFullscreen();
        if(args[i] == "-launched") tmp = true;
  	}
    if(!tmp) exit(1);
}

int main(int argc, char* argv[]){
    cout << "== Escapists 3D Startup ==" << endl << endl;
    glutInit(&argc, argv);
    cout << "Initialized OpenGL." << endl;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    cout << "Initialized Display Mode." << endl;

    glutInitWindowSize(960,640);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-960/2 ,glutGet(GLUT_SCREEN_HEIGHT)/2-640/2);
    glutCreateWindow("The Escapists 3D");
    cout << "Initialized Window." << endl;

    gluOrtho2D(0,960,640,0);
    init();
    parseArguments(argc, argv);
    cout << "Initialized Game." << endl;
    
    cout << "Done Initializing." << endl;

    cout << "Loading Settings..." << endl;
    LoadSettings();
    if(settings.fullscreen) toggleFullscreen();

    cout << "Loading Language..." << endl;
    ReadLangFile(settings.langs[settings.currentLanguage]);

    cout << "Loading Map Data..." << endl;
	for(int i=1; i<=getMapCount(); i++){
        ReadMapDatFile(i);
    }

    cout << "Loading Texture Data..." << endl;
    ReadTextureDatFile("all");
    ReadTextureDatFile("lost");
    ReadTextureDatFile("sky");
    ReadTextureDatFile("sprites");
    ReadTextureDatFile("title");
    ReadTextureDatFile("won");
    ReadTextureDatFile("hud");

    cout << "Loading Font Data..." << endl;
    ReadFontDatFile("font");

    glutDisplayFunc(display);
    //glutReshapeFunc(resize);
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);
    glutSpecialFunc(SButtonDown);

    cout << "Done Loading." << endl;
    glutMainLoop();
}