#pragma once
#include "raylib.h"

class Obstacle
{
private:
    float x, y;
    float width, height;
    float speed;
    int typeID;
public:
    Obstacle(int id, float startX, float startY, float w, float h);
    void update();
    void draw();
};
