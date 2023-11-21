#pragma once

#include "main.h"

struct Settings {
    bool fullscreen;
    string langs[2] = {
        "english",
        "german",
    };
    int currentLanguage;
};

extern Settings settings;

void LoadSettings(){
    string filename = "data/settings.set";
	ifstream inputFile(filename);
	if(!inputFile.is_open()) err("Could not load settings!");
    int cycl = 0;
	while(inputFile.is_open() && inputFile.good()){
		string inp;
		getline(inputFile, inp);
		if(cycl == 0) settings.fullscreen = to_bool(inp);
        if(cycl == 1) settings.currentLanguage = atoi(inp.c_str());
        cycl++;
	}
}

void SaveSettings(){
    string filename = "data/settings.set";
    ofstream outFile(filename);
    outFile << settings.fullscreen << endl;
    outFile << settings.currentLanguage << endl;
}

void ApplySettings(){
    LoadSettings();
    if(settings.fullscreen) toggleFullscreen(true);
    cout << "Loading Language..." << endl;
    ReadLangFile(settings.langs[settings.currentLanguage]);
}