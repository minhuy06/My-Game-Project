#pragma once
#include "raylib.h"
#include "SkinManager.h"

class Player{
    private:
        float x, y; // Tọa độ người chơi
        float size;
        Color color;

        // Các biến vật lý dùng tính toán di chuyển
        float velocity;
        float gravity;

        public:
            Player(float startX, float startY);
            void update(); // Xử lý rớt xuống/nhảy lên
            void draw(SkinManager& skinManager); // Vẽ chính mình lên màn hình
};