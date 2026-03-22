#pragma once
#include "raylib.h"

class SkinManager
{
    private:
        int currentSkinID;
    public:
        SkinManager();
        void setCurrentSkin(int id);
        int getCurrentSkin();
        void drawSkin(float x, float y, float size);
};