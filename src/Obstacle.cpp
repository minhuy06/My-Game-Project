#include "../include/Obstacle.h"

Obstacle::Obstacle(int id, float startX, float startY, float w, float h){
    typeID = id;
    x = startX;
    y = startY;
    width = w;
    height = h;
    speed = 5.0f;
}

void Obstacle::update(){
}

void Obstacle::draw(){
    if(typeID == 0){ // Chướng ngại vật thứ nhất
        Color cyan = { 0, 255, 255, 255 };
        Color purple = { 200, 100, 255, 255 };
        Color darkBg = { 11, 30, 104, 255 };

        // Vẽ khung chướng ngại vật phát sáng (Chuyển màu từ Cyan xuống Tím)
        DrawRectangleGradientV((int)x, (int)y, (int)width, (int)height, cyan, purple);

        // Vẽ lõi chướng ngại vật tối đen
        float thickness = 10.0f;
        DrawRectangle((int)(x + thickness), (int)(y + thickness), (int)(width - thickness * 2), (int)(height - thickness * 2), darkBg);

        // Vẽ các gai nhọn
        float spikeSize = 25.0f;
        int numSpikes = 3;

        for(int i = 1; i <= numSpikes; i++){
            // Khi i=1 -> Y nằm ở 1/4 cổng (25%)
            // Khi i=2 -> Y nằm ở 2/4 cổng (50% - Chính giữa)
            // Khi i=3 -> Y nằm ở 3/4 cổng (75%)
            float spikeY = y + height * (i / (float)(numSpikes + 1)); 

            // Gai Trái
            DrawTriangle({x - spikeSize, spikeY}, {x, spikeY + spikeSize}, {x, spikeY - spikeSize}, cyan);
            
            // Gai Phải
            DrawTriangle({x + width, spikeY - spikeSize}, {x + width, spikeY + spikeSize}, {x + width + spikeSize, spikeY}, purple);
        }
    }
}