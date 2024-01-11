#include "objects.h"

void Object::DrawObject(){
    Texture.width = Size.x;
    Texture.height = Size.y;

    DrawTexture(Texture, Position.x, Position.y, WHITE);
}

Object::Object(string name){
    Name = name;
}

void ObjectsClass::AddObject(Object object){
    ObjectCount++;

    Objects.push_back(object);
}

int ObjectsClass::GetObject(string Name){
    for(int i=0; i<ObjectCount; i++){
        if(Objects.at(i).Name == Name) return i;
    }
    return 0;
}

void ObjectsClass::DrawAllObjects(){
    for(int i=0; i<ObjectCount; i++){
        Objects.at(i).DrawObject();
    }
}