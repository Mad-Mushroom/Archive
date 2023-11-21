#pragma once

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "include/glad/glad.h"

//#include "objects/objects.h"
#include "console/console.h"
#include "renderer/renderer.h"

using namespace std;

void Init();
void Update();

bool CreateWindow(int SizeX, int SizeY, const char* title);