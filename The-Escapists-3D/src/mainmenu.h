#pragma once

#include "main.h"

struct mainmenu {
    int option = 1;
    bool canAdvance = true;
    int currentMenu = 1;
    int lastMenu = 1;
    bool paused = false;
};

extern mainmenu mainMenu;

void MainMenu(){
    screen(sky, 0.5);
    if(Keys.s == 1 && mainMenu.option < 5 && mainMenu.canAdvance){ mainMenu.option++; mainMenu.canAdvance = false; }
    if(Keys.w == 1 && mainMenu.option > 1 && mainMenu.canAdvance){ mainMenu.option--; mainMenu.canAdvance = false; }
    PrintLn("The Escapitst 3D", 3, (32)*3, (32)*3, colors.white);
    PrintLn(currentLang[0], 2, (960-((currentLang[0].length())*16*2))/2, (128)*2, colors.white);
    if(mainMenu.option == 1) PrintLn(currentLang[0], 2, (960-((currentLang[0].length())*16*2))/2, (128)*2, colors.red);
    PrintLn(currentLang[1], 2, (960-((currentLang[1].length())*16*2))/2, (128+40)*2, colors.white);
    if(mainMenu.option == 2) PrintLn(currentLang[1], 2, (960-((currentLang[1].length())*16*2))/2, (128+40)*2, colors.red);
    PrintLn(currentLang[2], 2, (960-((currentLang[2].length())*16*2))/2, (128+80)*2, colors.white);
    if(mainMenu.option == 3) PrintLn(currentLang[2], 2, (960-((currentLang[2].length())*16*2))/2, (128+80)*2, colors.red);
    PrintLn(currentLang[3], 2, (960-((currentLang[3].length())*16*2))/2, (128+120)*2, colors.white);
    if(mainMenu.option == 4) PrintLn(currentLang[3], 2, (960-((currentLang[3].length())*16*2))/2, (128+120)*2, colors.red);
    PrintLn(currentLang[4], 2, (960-((currentLang[4].length())*16*2))/2, (128+160)*2, colors.white);
    if(mainMenu.option == 5) PrintLn(currentLang[4], 2, (960-((currentLang[4].length())*16*2))/2, (128+160)*2, colors.red);
    if(Keys.space){
        mainMenu.canAdvance = false;
        mainMenu.lastMenu = 1;
        if(mainMenu.option == 1) mainMenu.currentMenu = 2;
        if(mainMenu.option == 2) mainMenu.currentMenu = 3;
        if(mainMenu.option == 3) cout << "Multiplayer is under development!" << endl;
        if(mainMenu.option == 4) mainMenu.currentMenu = 5;
        if(mainMenu.option == 5) exit(0);
    }
}

void LevelSelect(){
    if(Keys.s == 1 && mainMenu.option < 5 && mainMenu.canAdvance){ mainMenu.option++; mainMenu.canAdvance = false; }
    if(Keys.w == 1 && mainMenu.option > 1 && mainMenu.canAdvance){ mainMenu.option--; mainMenu.canAdvance = false; }
    for(int i=0; i<mapCount; i++){
        PrintLn(mapNames[i], 2, (960-((8)*16*2))/2, (128+40*i)*2, colors.white);
        if(mainMenu.option == i+1) PrintLn(mapNames[i], 2, (960-((8)*16*2))/2, (128+40*i)*2, colors.red);
    }
    if(Keys.space && mainMenu.canAdvance){
        mainMenu.lastMenu = 2;
        player.currentMap = mainMenu.option;
        mainMenu.paused = false;
        gameState = 2;
    }
}

void LoadGameMenu(){
    if(Keys.space) mainMenu.currentMenu = 1;
}

void PauseMenu(){
    screen(sky, 0);
    if(Keys.s == 1 && mainMenu.option < 5 && mainMenu.canAdvance){ mainMenu.option++; mainMenu.canAdvance = false; }
    if(Keys.w == 1 && mainMenu.option > 1 && mainMenu.canAdvance){ mainMenu.option--; mainMenu.canAdvance = false; }
    PrintLn("The Escapitst 3D", 3, (32)*3, (32)*3, colors.white);
    PrintLn(currentLang[0], 2, (960-((currentLang[0].length())*16*2))/2, (128)*2, colors.white);
    if(mainMenu.option == 1) PrintLn(currentLang[0], 2, (960-((currentLang[0].length())*16*2))/2, (128)*2, colors.red);
    PrintLn(currentLang[1], 2, (960-((currentLang[1].length())*16*2))/2, (128+40)*2, colors.white);
    if(mainMenu.option == 2) PrintLn(currentLang[1], 2, (960-((currentLang[1].length())*16*2))/2, (128+40)*2, colors.red);
    PrintLn(currentLang[2], 2, (960-((currentLang[2].length())*16*2))/2, (128+80)*2, colors.white);
    if(mainMenu.option == 3) PrintLn(currentLang[2], 2, (960-((currentLang[2].length())*16*2))/2, (128+80)*2, colors.red);
    PrintLn(currentLang[3], 2, (960-((currentLang[3].length())*16*2))/2, (128+120)*2, colors.white);
    if(mainMenu.option == 4) PrintLn(currentLang[3], 2, (960-((currentLang[3].length())*16*2))/2, (128+120)*2, colors.red);
    PrintLn(currentLang[4], 2, (960-((currentLang[4].length())*16*2))/2, (128+160)*2, colors.white);
    if(mainMenu.option == 5) PrintLn(currentLang[4], 2, (960-((currentLang[4].length())*16*2))/2, (128+160)*2, colors.red);
    if(Keys.space){
        mainMenu.canAdvance = false;
        mainMenu.lastMenu = 4;
        if(mainMenu.option == 1) mainMenu.currentMenu = 2;
        if(mainMenu.option == 2) mainMenu.currentMenu = 3;
        if(mainMenu.option == 3) cout << "Multiplayer is under development!" << endl;
        if(mainMenu.option == 4) mainMenu.currentMenu = 5;
        if(mainMenu.option == 5) exit(0);
    }
    if(Keys.esc && mainMenu.canAdvance){ mainMenu.paused = !mainMenu.paused; mainMenu.canAdvance = false; }
}

void SettingsMenu(){
    if(Keys.s == 1 && mainMenu.option < 3 && mainMenu.canAdvance){ mainMenu.option++; mainMenu.canAdvance = false; }
    if(Keys.w == 1 && mainMenu.option > 1 && mainMenu.canAdvance){ mainMenu.option--; mainMenu.canAdvance = false; }
    PrintLn(currentLang[3], 3, (960-((currentLang[3].length())*16*2))/2, (32)*3, colors.white);
    PrintLn(currentLang[5] + to_string(settings.fullscreen), 2, (960-((currentLang[5].length() + to_string(settings.fullscreen).length())*16*2))/2, (128+0)*2, colors.white);
    if(mainMenu.option == 1) PrintLn(currentLang[5] + to_string(settings.fullscreen), 2, (960-((currentLang[5].length() + to_string(settings.fullscreen).length())*16*2))/2, (128+0)*2, colors.red);
    PrintLn(currentLang[6] + settings.langs[settings.currentLanguage], 2, (960-((currentLang[6].length() + settings.langs[settings.currentLanguage].length())*16*2))/2, (128+40)*2, colors.white);
    if(mainMenu.option == 2) PrintLn(currentLang[6] + settings.langs[settings.currentLanguage], 2, (960-((currentLang[6].length() + settings.langs[settings.currentLanguage].length())*16*2))/2, (128+40)*2, colors.red);
    PrintLn(currentLang[7], 2, (960-((currentLang[7].length()*16*2)))/2, (128+80)*2, colors.white);
    if(mainMenu.option == 3) PrintLn(currentLang[7], 2, (960-((currentLang[7].length()*16*2)))/2, (128+80)*2, colors.red);
    if(Keys.space && mainMenu.canAdvance){
        if(mainMenu.option == 1) settings.fullscreen = !settings.fullscreen;
        if(mainMenu.option == 2){
            if(settings.currentLanguage < 1) settings.currentLanguage++;
            else if(settings.currentLanguage >= 1) settings.currentLanguage = 0;
        }
        if(mainMenu.option == 3){
            SaveSettings();
            ApplySettings();
            mainMenu.currentMenu = mainMenu.lastMenu;
        }
        mainMenu.canAdvance = false;
    }
    if(Keys.esc) mainMenu.currentMenu = mainMenu.lastMenu;
}

void Menu(){
    if(mainMenu.currentMenu == 1) MainMenu();
    if(mainMenu.currentMenu == 2) LevelSelect();
    if(mainMenu.currentMenu == 3) LoadGameMenu();
    if(mainMenu.currentMenu == 4) PauseMenu();
    if(mainMenu.currentMenu == 5) SettingsMenu();
}

void pauseGame(){
    if(mainMenu.canAdvance) mainMenu.paused = !mainMenu.paused;
}