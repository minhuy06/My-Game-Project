#pragma once
#include <vector>
#include <string>
#include "Obstacle.h"

class LevelManager {
private:
    std::vector<Obstacle> obstacles;
    
public:
    LevelManager();
    
    // Hàm đọc dữ liệu từ file txt
    void loadLevel(const std::string& filepath);
    
    // Hàm cập nhật và vẽ toàn bộ chướng ngại vật
    void update();
    void draw();
    
    // Trả về danh sách chướng ngại vật để  xét va chạm
    std::vector<Obstacle>& getObstacles(); 
};