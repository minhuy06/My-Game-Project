#include "../include/LevelManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

LevelManager::LevelManager() {}

void LevelManager::loadLevel(const std::string& filepath){
    // Xoa tất cả chướng ngại vật cũ trước khi tải mới
    obstacles.clear();

    std::ifstream file(filepath);
    if(!file.is_open()){
        std::cout << "Lỗi: Không thể mở file map tại " << filepath << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file, line)){
        if (line.empty()) continue; // Bỏ qua dòng trống

        std::stringstream ss(line);
        int typeID;
        float x, y, width, height, speed;

        // Tách các giá trị ngăn cách bởi dấu cách
        if (ss >> typeID >> x >> y >> width >> height >> speed){
            // Ép typeID thành ObstacleType
            ObstacleType type = static_cast<ObstacleType>(typeID);

            // Tạo chướng ngại vật mới và thêm vào danh sách
            obstacles.push_back(Obstacle(type, x, y, width, height, speed, true));
        }
    }
    file.close();
}

void LevelManager::update(){
    for(auto& obs : obstacles){
        obs.update();
    }
}

void LevelManager::draw(){
    for(auto& obs : obstacles){
        obs.draw();
    }
}

std::vector<Obstacle>& LevelManager::getObstacles(){
    return obstacles;
}