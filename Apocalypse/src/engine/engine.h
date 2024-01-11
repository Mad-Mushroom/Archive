#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"

#include "customVariables.h"
#include "console/console.h"
#include "objects/objects.h"
#include "objects/physics.h"
#include "userinput/userinput.h"
#include "gui/gui.h"
#include "timer/timer.h"

using namespace std;

void CreateWindow(int SizeX, int SizeY, string Title);

void Init();
void Update();