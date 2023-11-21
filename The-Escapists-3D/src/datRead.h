#pragma once

#include "main.h"

void ReadMapDatFile(int map){
	string filename = "data/map/map" + to_string(map) + ".dat";
	ifstream inputFile(filename);
	if(!inputFile.is_open()) err("Could not load map" + to_string(map) + "!");
    int cycl = 0, tmp = 0;
	string mapName;
	getline(inputFile, mapName);
	mapNames[mapCount] = mapName;
	mapCount++;
	while(inputFile.is_open() && inputFile.good()){
		string inp;
		inputFile >> inp;
		if(tmp == 0) mapW[mapCount][cycl] = atoi(inp.c_str());
		if(tmp == 1) mapF[mapCount][cycl] = atoi(inp.c_str());
		if(tmp == 2) mapC[mapCount][cycl] = atoi(inp.c_str());
		if(tmp == 3) mapO[mapCount][cycl] = atoi(inp.c_str());
		if(tmp == 4) mapOZ[mapCount][cycl] = atoi(inp.c_str());
        cycl++;
		if(cycl >= 64*64){ cycl = 0; tmp++; }
	}
}

int getMapCount(){
	DIR *dp;
	int i = 0;
	struct dirent *ep;     
	dp = opendir ("./data/map/");

	if (dp != NULL){
		while (ep = readdir(dp))
			i++;

		(void) closedir (dp);
	}else perror ("Couldn't open the directory");

	return i-2;
}

void ReadTextureDatFile(string textName){
	string filename = "data/text/text_" + textName + ".dat";
	ifstream inputFile(filename);
	if(!inputFile.is_open()) err("Could not load texture " + textName + "!");
    int cycl = 0;
	while(inputFile.is_open() && inputFile.good()){
		string inp;
		getline(inputFile, inp);
		if(textName == "all") All_Textures[cycl-1] = atoi(inp.c_str());
		if(textName == "lost") lost[cycl-1] = atoi(inp.c_str());
		if(textName == "sky") sky[cycl-1] = atoi(inp.c_str());
		if(textName == "title") title[cycl-1] = atoi(inp.c_str());
		if(textName == "sprites") sprites[cycl-1] = atoi(inp.c_str());
		if(textName == "won") won[cycl-1] = atoi(inp.c_str());
		if(textName == "hud") hud[cycl-1] = atoi(inp.c_str());
        cycl++;
	}
}

void ReadFontDatFile(string fontName){
	string filename = "data/fonts/" + fontName + ".dat";
	ifstream inputFile(filename);
	if(!inputFile.is_open()) err("Could not load font " + fontName + "!");
    int cycl = 0;
	while(inputFile.is_open() && inputFile.good()){
		string inp;
		getline(inputFile, inp);
		if(fontName == "font") font[cycl-1] = atoi(inp.c_str());
        cycl++;
	}
}

void ReadLangFile(string lang){
	string filename = "data/lang/" + lang + ".lang";
	ifstream inputFile(filename);
	if(!inputFile.is_open()) err("Could not load language " + lang + "!");
    int cycl = 0;
	while(inputFile.is_open() && inputFile.good()){
		string inp;
		getline(inputFile, inp);
		currentLang[cycl] = inp;
        cycl++;
	}
}