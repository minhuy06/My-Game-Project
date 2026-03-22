#pragma once
#include "UI.h"

enum GameState{
    MENU_MAIN,
    PLAYING,
    GAME_OVER
};
class Game{
    private:
        GameState currentState;
        UI ui;
    public:
        Game();
        void init(); //Khởi tạo cửa sổ Raylib
        void update(); // Xử lý logic (Click chuột, nhảy,..)
        void render(); // Vẽ ra màn hình
        void run(); // Vòng lặp chính
};