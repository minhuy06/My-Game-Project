#pragma once
#include "raylib.h"

class UI{
    private:
        Texture2D iconPlay;
        Texture2D iconMap;
        Texture2D iconSkin;
        Texture2D iconGuide;
        Font myFont;
        float defaultThickness = 3.0f;
        float defaultChamfer = 15.0f;
        void drawOctagonBorder(float x, float y, float width, float height, float cLarge, float cSmall, float thickness, Color color);

    public:
        void init();
        void unload();
        void drawEntireButton(float x, float y, float width, float height, const char* text, Texture2D icon);
        void drawEntireButton(float x, float y, float width, float height, const char* text); // Dùng để vẽ khung điểm
        void drawRhythmicLines();
        void drawBackgroundColor(int y, Color colorTop, Color colorBottom);
        void drawFadingPlanet(float x, float y, float radius, Color glowColor, Color bgColor);
        void drawNeonTitle(const char* text, float x, float y, float fontSize, Color coreColor, Color outlineColor, Color glowColor);
        void drawMainMenu(int latestScore);
};