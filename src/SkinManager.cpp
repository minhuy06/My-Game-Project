#include "../include/SkinManager.h"

// Game vừa chạy, gán skin mặc định
SkinManager::SkinManager(){
    currentSkinID = 0;
}

void SkinManager::setCurrentSkin(int id){
    currentSkinID = id;
}

int SkinManager::getCurrentSkin(){
    return currentSkinID;
}

// Vẽ skin
void SkinManager::drawSkin(float x, float y, float size){
    if(currentSkinID == 0){
        Color color = { 1, 255, 195, 255 };

        // Vẽ 6 hình chữ nhật to dần lên nhưng mờ dần đi
        int layerCount = 6;
        for(int i = layerCount; i > 0; i--){
            float alpha = (float)i/layerCount * 0.1f;
            float currentSize = size + (layerCount - i) * 4.0f;
            float offset = (currentSize - size) / 2.0f;
            DrawRectangle((int)(x - offset), (int)(y - offset), (int)currentSize, (int)currentSize, Fade(color, alpha));
        }

        Rectangle cube = {x, y, size, size};
        DrawRectangleLinesEx(cube, 4.0f, color);

        // Vẽ họa tiết tâm hình chữ nhật
        DrawLineEx({x + size/2, y + size/4}, {x + size*3/4, y + size/2}, 3.0f, color);
        DrawLineEx({x + size*3/4, y + size/2}, {x + size/2, y + size*3/4}, 3.0f, color);
        DrawLineEx({x + size/2, y + size*3/4}, {x + size/4, y + size/2}, 3.0f, color);
        DrawLineEx({x + size/4, y + size/2}, {x + size/2, y + size/4}, 3.0f, color);
        DrawCircle((int)(x + size/2), (int)(y + size/2), 6.0f, color);
    }

    else if (currentSkinID == 1){
        // Skin khác
    }
}