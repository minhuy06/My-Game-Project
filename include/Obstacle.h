#pragma once
#include "raylib.h"

enum class ObstacleType {
    GATE = 0,        // Cổng phát sáng
    SPIKE_UP = 1,    // Tam giác nhọn hướng lên
    BLOCK = 2,       // Khối vi mạch
    SPIKE_MAT = 3,   // Thảm gai tia laser
    ORB = 4,         // Quả cầu năng lượng
    SPIKE_DOWN = 5   // Gai treo ngược
};

class Obstacle
{
private:
    float x, y;
    float width, height;
    float speed;
    ObstacleType typeID;
    bool active;
public:
    Obstacle(ObstacleType id, float startX, float startY, float w, float h);
    Obstacle(ObstacleType id, float startX, float startY, float w, float h, float spd, bool isActive);
    void update();
    void draw();
    Rectangle getHitbox();
};
