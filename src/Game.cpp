#include "../include/Game.h"
#include "raylib.h"

Game::Game() {
    currentState = MENU_MAIN; // Mở game lên là vào Menu
}

void Game::init() {
    InitWindow(1550, 850, "Hanh trinh vuot ai");
    ui.init();

    // Tải dữ liệu màn chơi từ file txt ngay khi khởi tạo game
    levelManager.loadLevel("data/levels/level_1.txt");

    SetTargetFPS(60);
}

void Game::update() {
    switch (currentState) {
        case MENU_MAIN:
            // Nhấn Enter hoặc Space để bắt đầu chơi
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                currentState = PLAYING;
            }
            break;
            
        case PLAYING:
            // Chỉ cập nhật (di chuyển) chướng ngại vật khi đang trong trạng thái PLAYING
            levelManager.update();
            break;
            
        case GAME_OVER:
            // (Sẽ làm sau) Xử lý logic khi thua cuộc (VD: Nhấn R để chơi lại)
            break;
    }
}

void Game::render() {
    BeginDrawing();
    
    // Quét dọn màn hình cũ bằng màu đen
    ClearBackground(BLACK);

    switch (currentState) {
        case MENU_MAIN:
            ui.drawMainMenu(85); // Tạm truyền số 85 vào làm điểm mẫu
            break;
        case PLAYING:
            levelManager.draw();
            break;
        case GAME_OVER:
            // ui.drawGameOver();
            break;
    }
    
    EndDrawing();
}

void Game::run() {
    while (!WindowShouldClose()) {
        update();
        render();
    }
    CloseWindow();
}