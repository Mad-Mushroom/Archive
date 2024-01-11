#include "engine.h"

using namespace std;

ConsoleClass Console;
ObjectsClass Objects;
PhysicsClass Physics;
UserInputClass UserInput;
GuiClass GUI;

void CreateWindow(int SizeX, int SizeY, string Title){
	InitWindow(SizeX, SizeY, Title.c_str());
	SetTargetFPS(144);
}

int main(){
    Init();
	Texture2D TitleTexture = LoadTexture("res/engine/title.png");
	TitleTexture.width = GetScreenWidth();
	TitleTexture.height = GetScreenHeight();
	Timer IntroTimer;
	IntroTimer.StartTimer(2);
	while (!WindowShouldClose()){
		if(!IntroTimer.TimerDone()){
			BeginDrawing();
				DrawTexture(TitleTexture, 0, 0, WHITE);
				ClearBackground(BLACK);
			EndDrawing();
			IntroTimer.UpdateTimer();
		}else{
			BeginDrawing();
			Update();
			EndDrawing();
		}
	}
	CloseWindow();
    return 0;
}
