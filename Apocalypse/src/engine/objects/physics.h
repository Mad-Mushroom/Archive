#pragma once

#include "../engine.h"

class PhysicsClass {
public:
    float gravitationForce;

    void SetupPhysics(float gravitationForce);
    void CalculatePhysics();
    bool CheckIfObjectIsColliding(int ObjIndex);
    Vector_2 CheckIfObjectIsCollidingVec(int ObjIndex);
    bool CheckObjectCollision(int Obj1Index, int Obj2Index);
    void AddForceToObject(int ObjIndex, float force, float duration, Vector_2 direction);
};

extern PhysicsClass Physics;