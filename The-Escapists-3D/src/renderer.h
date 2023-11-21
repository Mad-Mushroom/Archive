#pragma once

#include "main.h"

int depth[120];

float degToRad(float a){
    return a*M_PI/180.0;
}

float FixAng(float a){
    if(a>359) {
        a-=360;
    }
    if(a<0) {
        a+=360;
    }
    return a;
}

void drawRays2D(){
    int r,mx,my,mp,dof;
    float vx,vy,rx,ry,ra,xo,yo,disV,disH;

    ra=FixAng(pa+30);

    for(r=0; r<120; r++)
    {
        int vmt=0,hmt=0;
        dof=0;
        disV=100000;
        float Tan=tan(degToRad(ra));
        if(cos(degToRad(ra))> 0.001) {
            rx=(((int)px>>6)<<6)+64;
            ry=(px-rx)*Tan+py;
            xo= 64;
            yo=-xo*Tan;
        }
        else if(cos(degToRad(ra))<-0.001) {
            rx=(((int)px>>6)<<6) -0.0001;
            ry=(px-rx)*Tan+py;
            xo=-64;
            yo=-xo*Tan;
        }
        else {
            rx=px;
            ry=py;
            dof=64;
        }

        while(dof<64)
        {
            mx=(int)(rx)>>6;
            my=(int)(ry)>>6;
            mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && mapW[player.currentMap][mp]>0) {
                vmt=mapW[player.currentMap][mp]-1;
                dof=64;
                disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);
            }
            else {
                rx+=xo;
                ry+=yo;
                dof+=1;
            }
        }
        vx=rx;
        vy=ry;

        dof=0;
        disH=100000;
        Tan=1.0/Tan;
        if(sin(degToRad(ra))> 0.001) {
            ry=(((int)py>>6)<<6) -0.0001;
            rx=(py-ry)*Tan+px;
            yo=-64;
            xo=-yo*Tan;
        }
        else if(sin(degToRad(ra))<-0.001) {
            ry=(((int)py>>6)<<6)+64;
            rx=(py-ry)*Tan+px;
            yo= 64;
            xo=-yo*Tan;
        }
        else {
            rx=px;
            ry=py;
            dof=64;
        }

        while(dof<64)
        {
            mx=(int)(rx)>>6;
            my=(int)(ry)>>6;
            mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && mapW[player.currentMap][mp]>0) {
                hmt=mapW[player.currentMap][mp]-1;
                dof=64;
                disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);
            }
            else {
                rx+=xo;
                ry+=yo;
                dof+=1;
            }
        }

        float shade=1;
        glColor3f(0,0.8,0);
        if(disV<disH) {
            hmt=vmt;
            shade=0.5;
            rx=vx;
            ry=vy;
            disH=disV;
            glColor3f(0,0.6,0);
        }

        int ca=FixAng(pa-ra);
        disH=disH*cos(degToRad(ca));
        int lineH = (mapS*640)/(disH);
        float ty_step=32.0/(float)lineH;
        float ty_off=0;
        if(lineH>640) {
            ty_off=(lineH-640)/2.0;
            lineH=640;
        }
        int lineOff = 320 - (lineH>>1);

        depth[r]=disH;
        int y;
        float ty=ty_off*ty_step;
        float tx;
        if(shade==1) {
            tx=(int)(rx/2.0)%32;
            if(ra>180) {
                tx=31-tx;
            }
        }
        else        {
            tx=(int)(ry/2.0)%32;
            if(ra>90 && ra<270) {
                tx=31-tx;
            }
        }
        for(y=0; y<lineH; y++)
        {
            int pixel=((int)ty*32+(int)tx)*3+(hmt*32*32*3);
            int red   =All_Textures[pixel+0]*shade;
            int green =All_Textures[pixel+1]*shade;
            int blue  =All_Textures[pixel+2]*shade;
            glPointSize(poiS);
            glColor3ub(red,green,blue);
            glBegin(GL_POINTS);
            glVertex2i(r*8,y+lineOff);
            glEnd();
            ty+=ty_step;
        }

        for(y=lineOff+lineH; y<640; y++){
            float dy=y-(640/2.0), deg=degToRad(ra), raFix=cos(degToRad(FixAng(pa-ra)));
            tx=px/2 + cos(deg)*158*2*32/dy/raFix;
            ty=py/2 - sin(deg)*158*2*32/dy/raFix;
            int mp=mapF[player.currentMap][(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
            int pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
            int red   =All_Textures[pixel+0]*0.7;
            int green =All_Textures[pixel+1]*0.7;
            int blue  =All_Textures[pixel+2]*0.7;
            glPointSize(poiS);
            glColor3ub(red,green,blue);
            glBegin(GL_POINTS);
            glVertex2i(r*8,y);
            glEnd();

            mp=mapC[player.currentMap][(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
            pixel=(((int)(ty)&31)*32 + ((int)(tx)&31))*3+mp*3;
            red   =All_Textures[pixel+0];
            green =All_Textures[pixel+1];
            blue  =All_Textures[pixel+2];
            if(mp>0) {
                glPointSize(poiS);
                glColor3ub(red,green,blue);
                glBegin(GL_POINTS);
                glVertex2i(r*8,640-y);
                glEnd();
            }
        }

        ra=FixAng(ra-0.5);
    }
}

/*void drawSprites(){
    int x,y,s;
    if(px<sp[0].x+30 && px>sp[0].x-30 && py<sp[0].y+30 && py>sp[0].y-30) {
        sp[0].state=0;
    }
    if(px<sp[3].x+30 && px>sp[3].x-30 && py<sp[3].y+30 && py>sp[3].y-30) {
        gameState=4;
    }
    int spx=(int)sp[3].x>>6,          spy=(int)sp[3].y>>6;
    int spx_add=((int)sp[3].x+15)>>6, spy_add=((int)sp[3].y+15)>>6;
    int spx_sub=((int)sp[3].x-15)>>6, spy_sub=((int)sp[3].y-15)>>6;
    if(sp[3].x>px && mapW[player.currentMap][spy*8+spx_sub]==0) {
        sp[3].x-=0.04*fps;
    }
    if(sp[3].x<px && mapW[player.currentMap][spy*8+spx_add]==0) {
        sp[3].x+=0.04*fps;
    }
    if(sp[3].y>py && mapW[player.currentMap][spy_sub*8+spx]==0) {
        sp[3].y-=0.04*fps;
    }
    if(sp[3].y<py && mapW[player.currentMap][spy_add*8+spx]==0) {
        sp[3].y+=0.04*fps;
    }
    for(s=0; s<4; s++) {
        float sx=sp[s].x-px;
        float sy=sp[s].y-py;
        float sz=sp[s].z;
        float CS=cos(degToRad(pa)), SN=sin(degToRad(pa));
        float a=sy*CS+sx*SN;
        float b=sx*CS-sy*SN;
        sx=a;
        sy=b;
        sx=(sx*108.0/sy)+(120/2);
        sy=(sz*108.0/sy)+( 80/2);
        int scale=32*80/b;
        if(scale<0) {
            scale=0;
        }
        if(scale>120) {
            scale=120;
        }
        float t_x=0, t_y=31, t_x_step=31.5/(float)scale, t_y_step=32.0/(float)scale;
        for(x=sx-scale/2; x<sx+scale/2; x++) {
            t_y=31;
            for(y=0; y<scale; y++) {
                if(sp[s].state==1 && x>0 && x<120 && b<depth[x]) {
                    int pixel=((int)t_y*32+(int)t_x)*3+(sp[s].map*32*32*3);
                    int red   =sprites[pixel+0];
                    int green =sprites[pixel+1];
                    int blue  =sprites[pixel+2];
                    if(red!=255 && green!=0 && blue!=255) {
                        glPointSize(poiS);
                        glColor3ub(red,green,blue);
                        glBegin(GL_POINTS);
                        glVertex2i(x*8,sy*8-y*8);
                        glEnd();
                    }
                    t_y-=t_y_step;
                    if(t_y<0) {
                        t_y=0;
                    }
                }
            }
            t_x+=t_x_step;
        }
    }
}*/

void drawSprite(int sprite, int posX, int posY, int posZ) {
    float sx=posX-px;
    float sy=posY-py;
    float sz=posZ;
    float CS=cos(degToRad(pa)), SN=sin(degToRad(pa));
    float a=sy*CS+sx*SN;
    float b=sx*CS-sy*SN;
    sx=a;
    sy=b;
    sx=(sx*108.0/sy)+(120/2);
    sy=(sz*108.0/sy)+( 80/2);
    int scale=32*80/b;
    if(scale<0) {
        scale=0;
    }
    if(scale>120) {
        scale=120;
    }
    float t_x=0, t_y=31, t_x_step=31.5/(float)scale, t_y_step=32.0/(float)scale;
    for(int x=sx-scale/2; x<sx+scale/2; x++) {
        t_y=31;
        for(int y=0; y<scale; y++) {
            if(x>0 && x<120 && b<depth[x]) {
                int pixel=((int)t_y*32+(int)t_x)*3+(sprite*32*32*3);
                int red   =sprites[pixel+0];
                int green =sprites[pixel+1];
                int blue  =sprites[pixel+2];
                if(red == 255 && green == 0 && blue == 255){
                    //glPointSize(size); glColor3ub(red,green,blue); glBegin(GL_POINTS); glVertex2i(x*size+posX,y*size+posY); glEnd();
                }else{
                    glPointSize(poiS);
                    glColor3ub(red,green,blue);
                    glBegin(GL_POINTS);
                    glVertex2i(x*8,sy*8-y*8);
                    glEnd();
                }
                t_y-=t_y_step;
                if(t_y<0) {
                    t_y=0;
                }
            }
        }
        t_x+=t_x_step;
    }
}

void drawObjects() {
    drawSprite(1, 1.5*64, 4.5*64, 1);
    for(int x=0; x<mapX; x++){
        for(int y=0; y<mapY; y++){
            if(mapO[player.currentMap][(mapX*y)+x] > 0){
                drawSprite(mapO[player.currentMap][(mapX*y)+x]-1, (x+0.5)*64, (y+0.5)*64, mapOZ[player.currentMap][(mapX*y)+x]);
            }
        }
    }
}

void drawSky(){
   int x,y;
    for(y=0; y<40; y++){
        for(x=0; x<120; x++){
            int xo=(int)pa*2-x;
            if(xo<0){
                xo+=120;
            }
            xo=xo % 120;
            int pixel=(y*120+xo)*3;
            int red   =sky[pixel+0];
            int green =sky[pixel+1];
            int blue  =sky[pixel+2];
            glPointSize(poiS);
            glColor3ub(red,green,blue);
            glBegin(GL_POINTS);
            glVertex2i(x*8,y*8);
            glEnd();
        }
    }
}

void screen(int screen[], float opacity = 1){
    int x,y;
    for(y=0; y<80; y++){
        for(x=0; x<120; x++){
            int pixel=(y*120+x)*3;
            int red   =screen[pixel+0];
            int green =screen[pixel+1];
            int blue  =screen[pixel+2];
            if(red == 255 && green == 0 && blue == 255){
                
            }else{
                red   =screen[pixel+0]*fade;
                green =screen[pixel+1]*fade;
                blue  =screen[pixel+2]*fade;
                glPointSize(poiS);
                glColor3ub(red,green,blue);
                glBegin(GL_POINTS);
                glVertex2i(x*8,y*8);
                glEnd();
            }
        }
    }
    if(fade<opacity){
        fade+=0.001*fps;
    }
    if(fade>1){
        fade=1;
    }
}

void toggleFullscreen(bool onlyTrue = false){
    if(onlyTrue){
        glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_WIDTH));
        poiS = 16;
        glutFullScreen();
    }else{
        fullscreen = !fullscreen;

        if(fullscreen){ glutReshapeWindow(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_WIDTH)); poiS = 16; glutFullScreen(); }
        if(!fullscreen){ glutReshapeWindow(960,640); poiS = 8; }
    }
}

void resize(int w,int h){
    if(!fullscreen) glutReshapeWindow(960,640);
}

void PutChar(char character, int size, int posX, int posY, ColorRGB color = colors.white){
     int charIndex=0;
     char allChars[]={
        ' ','!','\"','#','$','%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?',
        '@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','[','\\',']','^','_',
        '`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','{','|','}','~',' ',
    };
     for(int i=0; i<96; i++){
          if(character == allChars[i]){
               charIndex = i;
          }
     }

     int x=0,y=0;
     for(y=0;y<16;y++){
          for(x=0;x<16;x++){
               if(charIndex==39){

               }else{
                    int sx = x+16*charIndex;
                    int pixel=(y*1536+sx)*3;
                    int red   =font[pixel+0];
                    int green =font[pixel+1];
                    int blue  =font[pixel+2];
                    if(red == 255 && green == 0 && blue == 255){
                         //glPointSize(size); glColor3ub(red,green,blue); glBegin(GL_POINTS); glVertex2i(x*size+posX,y*size+posY); glEnd();
                    }else{
                         glPointSize(size*(poiS/8)); glColor3ub(color.red,color.green,color.blue); glBegin(GL_POINTS); glVertex2i(x*size+(posX),y*size+(posY)); glEnd();
                    }
               }
          }	
     }
}

void PrintLn(string str, int size, int posX, int posY, ColorRGB color = colors.white){
     int x=0;
     for(unsigned int i = 0; i < str.length(); i++){
          PutChar(str[i], size, posX+x, posY, color);
          x+=size*16;
     }
}

void drawHud(){
    screen(hud);
    PrintLn(to_string(player.health) + "%", 2, 60, 530, colors.white);
    PrintLn(to_string(player.health) + "%", 2, 60, 595, colors.white);
}