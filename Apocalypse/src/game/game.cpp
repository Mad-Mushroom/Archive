#include "game.h"

Object TestObj("Obj");
Object TestPlatform("Platform");
Object STestPlatform("2Platform");

GUIElement TestEl;

void InitObjects(){
    TestObj.Texture = LoadTexture("res/game/text/placeholder.png");
    TestObj.Position = {0,0};
    TestObj.Size = {100,100};
    TestPlatform.Texture = LoadTexture("res/game/text/placeholder.png");
    TestPlatform.Position = {0, 700};
    TestPlatform.Size = {1280, 100};
    STestPlatform.Texture = LoadTexture("res/game/text/placeholder.png");
    STestPlatform.Position = {800, 600};
    STestPlatform.Size = {300, 100};

    TestEl.Name = "TestElement";
    TestEl.font = LoadFont("res/game/font/pixelcraft.otf");
    TestEl.Text = "Hello World!";
    TestEl.FontSize = 20;
    TestEl.ForegroundColor = WHITE;
    TestEl.BackgroundColor = BLACK;
    TestEl.Position = {100,100};
    TestEl.Size = {200, 100};

    GUI.AddElement(TestEl);

    Objects.AddObject(TestObj);
    Objects.AddObject(TestPlatform);
    Objects.AddObject(STestPlatform);

    Objects.Objects.at(0).Physics.Gravitation = true;
    Objects.Objects.at(0).Physics.Mass = 0.2;
}

void Init(){
    CreateWindow(1280, 720, "Apocalypse");

    Physics.SetupPhysics(9.81);

    InitObjects();

    Physics.AddForceToObject(0, 1, 2.5, {-1, 0});
    Physics.AddForceToObject(0, 3, 2.5, {1, 0});
}

void Update(){
    ClearBackground(BLUE);

    Physics.CalculatePhysics();

    Objects.DrawAllObjects();

    GUI.Elements.at(0).DrawElement();

    DrawRectangle(300, 100, 20, 20, WHITE);

    if(GUI.Elements.at(0).clicked) DrawRectangle(300, 100, 20, 20, BLACK);

    DrawText(to_string(Physics.CheckIfObjectIsCollidingVec(0).x).c_str(), 0, 0, 20, WHITE);
    DrawText(to_string(Physics.CheckIfObjectIsCollidingVec(0).y).c_str(), 0, 20, 20, WHITE);
    
    if(UserInput.KeyDown(KEY_A)) DrawRectangle(300, 100, 20, 20, BLACK);
}