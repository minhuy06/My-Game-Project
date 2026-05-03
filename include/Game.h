#pragma once
#include "UI.h"
#include "LevelManager.h"

enum GameState{
    MENU_MAIN,
    PLAYING,
    GAME_OVER
};
class Game{
    private:
        GameState currentState;
        UI ui;
        LevelManager levelManager;
    public:
        Game();
        void init(); //Khởi tạo cửa sổ Raylib
        void update(); // Xử lý logic (Click chuột, nhảy,..)
        void render(); // Vẽ ra màn hình
        void run(); // Vòng lặp chính
};