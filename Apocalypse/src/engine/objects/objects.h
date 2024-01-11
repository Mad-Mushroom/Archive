#pragma once

#include "../engine.h"

using namespace std;

class Force {
public:
    float force;
    Vector_2 direction;
    float duration;
};

class PhysicsObject {
public:
    bool Gravitation;
    float Mass;
    bool Collision = true;
    vector<Force> Forces;
    int ForcesCount;
};


class Object {
public:
    string Name;

    Vector_2 Position;
    Vector_2 Size;
    Texture2D Texture;

    PhysicsObject Physics;

    Object(string name);

    void DrawObject();
};

class ObjectsClass {
public:
    vector<Object> Objects;
    int ObjectCount;

    void AddObject(Object object);
    int GetObject(string Name);
    void DrawAllObjects();
};

extern ObjectsClass Objects;