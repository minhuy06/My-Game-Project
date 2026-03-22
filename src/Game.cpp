#include "../include/Game.h"
#include "raylib.h"

Game::Game() {
    currentState = MENU_MAIN; // Mở game lên là vào Menu
}

void Game::init() {
    InitWindow(1550, 850, "Hanh trinh vuot ai");
    ui.init();
    SetTargetFPS(60);
}

void Game::update() {
    // Logic click chuột sẽ viết ở đây sau
}

void Game::render() {
    BeginDrawing();
    
    switch (currentState) {
        case MENU_MAIN:
            ui.drawMainMenu(85); // Tạm truyền số 85 vào làm điểm mẫu
            break;
        case PLAYING:
            // player.draw();
            // level.draw();
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