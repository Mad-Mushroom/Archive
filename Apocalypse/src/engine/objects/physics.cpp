#include "physics.h"

void PhysicsClass::SetupPhysics(float gForce){
    gravitationForce = gForce;
}

void PhysicsClass::CalculatePhysics(){
    for(int i=0; i<Objects.ObjectCount; i++){
        if(Objects.Objects.at(i).Physics.Gravitation == true && !CheckIfObjectIsColliding(i)) Objects.Objects.at(i).Position.y += Objects.Objects.at(i).Physics.Mass * gravitationForce;
    
        for(int j=0; j<Objects.Objects.at(i).Physics.ForcesCount; j++){
            if(Objects.Objects.at(i).Physics.Forces.at(j).duration >= 0){
                if(CheckIfObjectIsCollidingVec(i).x+2 < Objects.Objects.at(i).Size.x) Objects.Objects.at(i).Position.x += (Objects.Objects.at(i).Physics.Forces.at(j).direction.x * Objects.Objects.at(i).Physics.Forces.at(j).force) - Objects.Objects.at(i).Physics.Mass/10;
                if(CheckIfObjectIsCollidingVec(i).y+2 < Objects.Objects.at(i).Size.y) Objects.Objects.at(i).Position.y += (Objects.Objects.at(i).Physics.Forces.at(j).direction.y * Objects.Objects.at(i).Physics.Forces.at(j).force) - Objects.Objects.at(i).Physics.Mass/10;
                Objects.Objects.at(i).Physics.Forces.at(j).duration -= (float)1/144;
            }
        }
    }
}

bool PhysicsClass::CheckIfObjectIsColliding(int ObjIndex){
    for(int i=0; i<Objects.ObjectCount; i++){
        if(Objects.Objects.at(i).Name == Objects.Objects.at(ObjIndex).Name) continue;
        if(!Objects.Objects.at(i).Physics.Collision || !Objects.Objects.at(ObjIndex).Physics.Collision) return false;
        if(Objects.Objects.at(ObjIndex).Position.y + Objects.Objects.at(ObjIndex).Size.y >= Objects.Objects.at(i).Position.y && Objects.Objects.at(ObjIndex).Position.y <= Objects.Objects.at(i).Position.y + Objects.Objects.at(i).Size.y){
            if(Objects.Objects.at(ObjIndex).Position.x + Objects.Objects.at(ObjIndex).Size.x >= Objects.Objects.at(i).Position.x && Objects.Objects.at(ObjIndex).Position.x <= Objects.Objects.at(i).Position.x + Objects.Objects.at(i).Size.x){
                return true;
            }
        }
    }
    return false;
}

Vector_2 PhysicsClass::CheckIfObjectIsCollidingVec(int ObjIndex){
    for(int i=0; i<Objects.ObjectCount; i++){
        //cout << Objects.Objects.at(i).Name << " - " << Objects.Objects.at(i).Position.x << " : " << Objects.Objects.at(i).Position.x + Objects.Objects.at(i).Size.x << " - " << Objects.Objects.at(i).Position.y << " : " << Objects.Objects.at(i).Position.y + Objects.Objects.at(i).Size.y << endl;
        if(Objects.Objects.at(i).Name == Objects.Objects.at(ObjIndex).Name) continue;
        if(!Objects.Objects.at(i).Physics.Collision || !Objects.Objects.at(ObjIndex).Physics.Collision) return {0,0};
        if(Objects.Objects.at(ObjIndex).Position.y + Objects.Objects.at(ObjIndex).Size.y >= Objects.Objects.at(i).Position.y && Objects.Objects.at(ObjIndex).Position.y <= Objects.Objects.at(i).Position.y + Objects.Objects.at(i).Size.y){
            if(Objects.Objects.at(ObjIndex).Position.x + Objects.Objects.at(ObjIndex).Size.x >= Objects.Objects.at(i).Position.x && Objects.Objects.at(ObjIndex).Position.x <= Objects.Objects.at(i).Position.x + Objects.Objects.at(i).Size.x){
                return {Objects.Objects.at(i).Position.x - Objects.Objects.at(ObjIndex).Position.x, Objects.Objects.at(i).Position.y - Objects.Objects.at(ObjIndex).Position.y};
            }
        }
    }
    return {0,0};
}

void PhysicsClass::AddForceToObject(int ObjIndex, float force, float duration, Vector_2 direction){
    Force tmp;
    tmp.force = force;
    tmp.direction = direction;
    tmp.duration = duration;
    Objects.Objects.at(ObjIndex).Physics.Forces.push_back(tmp);
    Objects.Objects.at(ObjIndex).Physics.ForcesCount++;
}