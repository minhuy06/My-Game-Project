#include "../include/Obstacle.h"
#include <cmath>

Obstacle::Obstacle(ObstacleType id, float startX, float startY, float w, float h){
    typeID = id;
    x = startX;
    y = startY;
    width = w;
    height = h;
    speed = 0.0f;
    active = true;
}

Obstacle::Obstacle(ObstacleType id, float startX, float startY, float w, float h, float spd, bool isActive) {
    typeID = id; x = startX; y = startY; width = w; height = h;
    speed = spd;
    active = isActive;
}

void Obstacle::update(){
    if (speed <= 0.0f || !active) return;

    // Lấy Delta Time (thời gian giữa 2 frame) để đảm bảo tốc độ di chuyển đồng đều trên mọi cấu hình máy
    const float dt = GetFrameTime();
    
    // Di chuyển chướng ngại vật sang trái
    x -= speed * dt;

    // Ẩn chướng ngại vật khi nó đi qua hẳn mép trái màn hình
    // Điều kiện (x + width < 0.0f) đảm bảo toàn bộ chiều dài của vật thể đã đi khuất màn hình
    if (x + width < 0.0f) {
        active = false;
    }
}

void Obstacle::draw(){
    if (speed > 0.0f && !active) return;  // Nếu là vật thể Gameplay (có tốc độ) và đã bị ăn (!active) -> Ẩn đi
    if (speed > 0.0f && (x < -50.0f || x > 850.0f)) return;  // Không vẽ nếu vật thể Gameplay đang ở ngoài mép màn hình

    // Các bảng màu Neon chính
    Color neonCyan = { 0, 255, 255, 255 };
    Color neonPink = { 255, 0, 255, 255 };
    Color electricBlue = { 44, 115, 232, 255 };
    Color darkCore = { 10, 10, 25, 255 };

    if(typeID == ObstacleType::GATE){ // Chướng ngại vật thứ nhất
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
    else if (typeID == ObstacleType::SPIKE_UP){
        // Vẽ chướng ngại vật thứ hai: Một hình tam giác nhọn hướng lên trên với hiệu ứng Neon Pink
        // Vẽ bóng phát sáng (Glow)
        DrawTriangle({x + width/2, y - 5}, {x - 5, y + height + 2}, {x + width + 5, y + height + 2}, Fade(neonPink, 0.3f));
        // Vẽ thân gai
        DrawTriangle({x + width/2, y}, {x, y + height}, {x + width, y + height}, neonPink);
        // Vẽ lõi tối bên trong để tạo chiều sâu
        DrawTriangle({x + width/2, y + 10}, {x + 5, y + height - 2}, {x + width - 5, y + height - 2}, darkCore);
    }

    // BLOCK: Khối xếp cạnh nhau
    else if (typeID == ObstacleType::BLOCK) { 
        // Vẽ nền khối
        DrawRectangleGradientEx({x, y, width, height}, electricBlue, darkCore, darkCore, electricBlue);
        // Vẽ viền sáng
        DrawRectangleLinesEx({x, y, width, height}, 2, neonCyan);
        // Vẽ chi tiết vi mạch nhỏ bên trong
        DrawRectangle(x + 10, y + 10, 5, 5, neonCyan);
        DrawRectangle(x + width - 15, y + height - 15, 5, 5, neonCyan);
    }

    // Thảm gai
    else if (typeID == ObstacleType::SPIKE_MAT) { 
        for(int i = 0; i < 2; i++) { // Vẽ 2 gai nhỏ trên một ô
            float subX = x + i * 20;
            DrawTriangle({subX + 10, y}, {subX, y + height}, {subX + 20, y + height}, neonPink);
            DrawLineEx({subX + 10, y}, {subX + 10, y + height}, 2, WHITE); // Tia lade trắng ở giữa
        }
    }

    // Quả cầu năng lượng (Hiệu ứng nhịp thở)
    else if (typeID == ObstacleType::ORB) { 
        float time = GetTime() * 5.0f;
        float pulse = sin(time) * 3.0f; // Tạo hiệu ứng co giãn

        // Vẽ các vòng tròn đồng tâm phát sáng
        DrawCircleGradient({ x + width/2, y + height/2 }, 20 + pulse, Fade(YELLOW, 0.5f), BLANK);
        DrawCircle(x + width/2, y + height/2, 12 + pulse/2, YELLOW);
        DrawCircleLines(x + width/2, y + height/2, 15 + pulse, WHITE);
    }

    // Gai treo ngược (Giống gai trên nhưng đảo ngược)
    else if (typeID == ObstacleType::SPIKE_DOWN) { 
        DrawTriangle({x - 5, y - 2}, {x + width/2, y + height + 5}, {x + width + 5, y - 2}, Fade(neonCyan, 0.3f));
        DrawTriangle({x, y}, {x + width/2, y + height}, {x + width, y}, neonCyan);
        DrawTriangle({x + 5, y + 2}, {x + width/2, y + height - 10}, {x + width - 5, y + 2}, darkCore);
    }
}
// Trả về vùng va chạm (Hitbox) của chướng ngại vật
Rectangle Obstacle::getHitbox() {
    // Tùy theo loại chướng ngại vật mà chỉnh hitbox lại cho phù hợp với hình ảnh vẽ ra
    switch (typeID) {
        case ObstacleType::SPIKE_UP:
            // Tam giác hướng lên: Không lấy phần không khí hai bên ngọn gai
            // - Dịch X vào 20%, Dịch Y xuống 30%
            // - Thu hẹp chiều rộng còn 60%, chiều cao còn 70%
            return { x + width * 0.2f, y + height * 0.3f, width * 0.6f, height * 0.7f };
            
        case ObstacleType::SPIKE_DOWN:
            // Gai lộn ngược: Ngược lại với SPIKE_UP, bám sát mép trên
            return { x + width * 0.2f, y, width * 0.6f, height * 0.7f };
            
        case ObstacleType::ORB:
            // Quả cầu tròn: Bỏ qua 4 góc vuông của Box, chỉ lấy vùng lõi ở giữa
            return { x + width * 0.2f, y + height * 0.2f, width * 0.6f, height * 0.6f };
            
        case ObstacleType::GATE:
            // Cổng phát sáng: Chỉ va chạm với phần lõi (bỏ qua phần ánh sáng tỏa ra bên ngoài)
            return { x + 10.0f, y + 10.0f, width - 20.0f, height - 20.0f };

        // Các trường hợp khối vuông (BLOCK), thảm gai (SPIKE_MAT) hoặc mặc định: Lấy toàn bộ kích thước
        default:
            return { x, y, width, height };
    }
}