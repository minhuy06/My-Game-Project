#include "../include/UI.h"
#include "../include/Player.h"
#include "../include/Obstacle.h"
#include <cmath>

// Hàm vẽ nút
void UI::drawOctagonBorder(float x, float y, float width, float height, float cLarge, float cSmall, float thickness, Color color) {
    // Cạnh trên
    DrawLineEx({x + cLarge, y}, {x + width - cSmall, y}, thickness, color); 
    
    // Cạnh dưới
    DrawLineEx({x + cSmall, y + height}, {x + width - cLarge, y + height}, thickness, color); 
    
    // Cạnh trái
    DrawLineEx({x, y + cLarge}, {x, y + height - cSmall}, thickness, color); 
    
    // Cạnh phải 
    DrawLineEx({x + width, y + cSmall}, {x + width, y + height - cLarge}, thickness, color); 

    // Góc Trên - Trái 
    DrawLineEx({x, y + cLarge}, {x + cLarge, y}, thickness, color); 
    
    // Góc Trên - Phải 
    DrawLineEx({x + width - cSmall, y}, {x + width, y + cSmall}, thickness, color); 
    
    // Góc Dưới - Trái
    DrawLineEx({x, y + height - cSmall}, {x + cSmall, y + height}, thickness, color); 
    
    // Góc Dưới - Phải
    DrawLineEx({x + width - cLarge, y + height}, {x + width, y + height - cLarge}, thickness, color);
}

// Nạp ảnh và phông chữ
void UI::init(){
    Image imgPlay = LoadImage("data/img/play.png");
    Image imgMap = LoadImage("data/img/map.png");
    Image imgSkin = LoadImage("data/img/skin.png");
    Image  imgGuide = LoadImage("data/img/huong_dan.png");

    ImageResize(&imgPlay, 400, 400);
    ImageResize(&imgMap, 400, 400);
    ImageResize(&imgSkin, 400, 400);
    ImageResize(&imgGuide, 400, 400);

    iconPlay = LoadTextureFromImage(imgPlay);
    iconMap = LoadTextureFromImage(imgMap);
    iconSkin = LoadTextureFromImage(imgSkin);
    iconGuide = LoadTextureFromImage(imgGuide);

    const char* vnAlphabet = "AĂÂBCDĐEÊGHIKLMNOÔƠPQRSTUƯVXY aăâbcdđeêghiklmnoôơpqrstuưvxy ÁÀẢÃẠẮẰẲẴẶẤẦẨẪẬ ÉÈẺẼẸẾỀỂỄỆ ÍÌỈĨỊ ÓÒỎÕỌỐỒỔỖỘỚỜỞỠỢ ÚÙỦŨỤỨỪỬỮỰ ÝỲỶỸỴ áàảãạắằẳẵặấầẩẫậ éèẻẽẹếềểễệ íìỉĩị óòỏõọốồổỗộớờởỡợ úùủũụứừửữự ýỳỷỹỵ 0123456789!@#$%^&*()_+{}|:\"<>?-=[]\\;',./";
    int codepointCount = 0;
    int *codepoints = LoadCodepoints(vnAlphabet, &codepointCount);
    myFont = LoadFontEx("data/myFont.ttf", 100, codepoints, codepointCount);
    UnloadCodepoints(codepoints);
    SetTextureFilter(myFont.texture, TEXTURE_FILTER_BILINEAR); // Đánh bóng chữ

}
void UI::unload(){
    UnloadFont(myFont);
    UnloadTexture(iconPlay);
    UnloadTexture(iconMap);
    UnloadTexture(iconSkin);
    UnloadTexture(iconGuide);
}

// Hàm phân chia 2 màu nền giao diện Menu
void UI::drawBackgroundColor(int y, Color colorTop, Color colorBottom){
    ClearBackground(colorTop);
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int bottomHeight = screenHeight - y;
    DrawRectangle(0, y, screenWidth, bottomHeight, colorBottom);
}

// Hàm vẽ hành tinh
void UI::drawFadingPlanet(float x, float y, float radius, Color glowColor, Color bgColor) {
    Vector2 center = {x, y};
    int layerCount = 10;
    
    // Vẽ quầng sáng 
    for(int i = layerCount; i > 0; i--) {
        // Alpha dao động từ 0.01 (ngoài cùng) đến 0.15 (gần lõi)
        float alpha = (float)(layerCount - i + 1) / layerCount * 0.15f; 
        Color alphaGlow = Fade(glowColor, alpha);
        
        // Bán kính đi từ to (radius + 20) lùi dần về (radius + 2)
        float currentRadius = radius + (i * 2.0f); 
        
        DrawCircleV(center, currentRadius, alphaGlow);
    }


    // Tạo một tâm bóng tối dịch chuyển lệch sang phải và xuống dưới
    float offset = radius * 0.2f; 
    int shadowX = (int)(x - offset);
    int shadowY = (int)(y - offset);
    
    // Vẽ một hình tròn Gradient bằng đúng màu nền để che đi bề mặt
    // Tâm hình tròn này tối đen (bgColor), và mờ dần ra viền (Fade = 0.0f)
    DrawCircleGradient(shadowX, shadowY, radius * 2.0f, bgColor, Fade(bgColor, 0.0f));
}

// Hàm vẽ nút hoàn chỉnh
void UI::drawEntireButton(float x, float y, float width, float height, const char* text, Texture2D icon){
    drawOctagonBorder(x, y, width, height, 40.0f, 20.0f, defaultThickness, SKYBLUE);
    drawOctagonBorder(x - 7.0f, y - 7.0f, width + 14.0f, height + 14.0f, 42.0f, 22.0f, defaultThickness + 2.0f, SKYBLUE);

    // Dán Icon lên nút
    float iconY = y + ((height - icon.height) / 2.0f) - 10.0f;
    DrawTexture(icon, x - 50.0f, iconY, WHITE);
    
    // Chữ căn giữa tự động
    float fontSize = 35;
    float spacing = 3.0f;
    Vector2 textSize = MeasureTextEx(myFont, text, fontSize, spacing);

    int textX = (int)(x + (width - textSize.x) / 2.0f);
    int textY = (int)(y + ((height - textSize.y) / 2.0f) + 40.0f);
    DrawTextEx(myFont, text, { (float)textX, (float)textY }, fontSize, spacing, WHITE);
}

// Vẽ nút cho ô điểm
void UI::drawEntireButton(float x, float y, float width, float height, const char* text){
    drawOctagonBorder(x, y, width, height, 20.0f, 10.0f, defaultThickness, SKYBLUE);
    drawOctagonBorder(x - 7.0f, y - 7.0f, width + 14.0f, height + 14.0f, 22.0f, 12.0f, defaultThickness + 2.0f, SKYBLUE);

    float fontSize = 35;
    float spacing = 3.0f;
    Vector2 textSize = MeasureTextEx(myFont, text, fontSize, spacing);
    int textX = (int)(x + (width - textSize.x) / 2.0f);
    int textY = (int)(y + (height - textSize.y) / 2.0f);
    DrawTextEx(myFont, text, { (float)textX, (float)textY }, fontSize, spacing, WHITE);
}

void UI::drawRhythmicLines() {
    // Xác định khu vực vẽ
    float startX = 100.0f;       
    float totalWidth = 600.0f;  
    float baseY = 550.0f;

    int numBars = 60; // Số lượng cột phù hợp với chiều rộng
    float barWidth = totalWidth / (float)numBars; 
    float padding = 2.0f; // Khoảng hở giữa các cột
    float actualWidth = barWidth - padding;

    for (int i = 0; i < numBars; i++) {
        float x = startX + i * barWidth;

        // Quy đổi vị trí cột thành tỷ lệ (từ 0.0 đến 1.0 của khu vực vẽ)
        float t = (float)i / numBars; 

        float finalHeight = 0.0f;
        // Thuật toán hàm Gaussian
        // Đỉnh núi số 1
        // Dốc sườn trái mở rộng, sườn phải hẹp hơn
        float peak1 = 0.0f;
        float centre1 = 0.35f; // Đỉnh 1 nằm ở khoảng 35% màn hình
        float A1 = 160.0f;      // Chiều cao tối đa
        float w1_left = 0.015f; // Độ rộng sườn trái
        float w1_right = 0.007f; // Độ rộng sườn phải

        // Tính toán Gaussian bất đối xứng cho Đỉnh 1
        if (t < centre1) 
            peak1 = A1 * exp(-pow(t - centre1, 2) / w1_left);
        else 
            peak1 = A1 * exp(-pow(t - centre1, 2) / w1_right);

        // Đỉnh núi số 2
        float peak2 = 0.0f;
        float centre2 = 0.75f; // Đỉnh 2 nằm ở khoảng 75% màn hình
        float A2 = 90.0f;       // Chiều cao tối đa
        float w2_left = 0.012f; // Độ rộng sườn trái
        float w2_right = 0.010f; // Độ rộng sườn phải

        // Tính toán Gaussian bất đối xứng cho Đỉnh 2
        if (t < centre2)
            peak2 = A2 * exp(-pow(t - centre2, 2) / w2_left);
        else 
            peak2 = A2 * exp(-pow(t - centre2, 2) / w2_right);

        // --- NOISE VÀ CHÂN NÚI ---
        float baseHeight = 15.0f; // Chiều cao cơ bản cố định ở chân núi
        // Thêm noise ngẫu nhiên nhẹ ở chân núi để tạo sự tự nhiên
        // Noise ngẫu nhiên từ 0 đến 8.0 pixel
        float randomNoise = (8.0f * (float)GetRandomValue(0, 100) / 100.0f);

        // Tổng hợp chiều cao: Đỉnh + Noise
        finalHeight = baseHeight + peak1 + peak2 + randomNoise;

        // --- MÀU SẮC ---
        Color topColor;
        // Đỉnh 1 cao vượt 80px -> Chóp Tím đậm
        if (finalHeight > 80.0f) {
            topColor = { 160, 100, 255, 220 };
        } 
        // Đỉnh 2 trên 40px -> Chóp Tím nhạt
        else if (finalHeight > 40.0f) {
            topColor = { 180, 150, 255, 220 };
        }
        // Chân đỉnh và các thanh nhỏ -> Xanh lục lam
        else {
            topColor = { 0, 255, 255, 220 };
        }
        
        // Chân đỉnh luôn có màu xanh dương đậm
        Color bottomColor = { 0, 100, 200, 100 }; 

        // Tọa độ Y kéo ngược từ mốc 550 lên
        float y = baseY - finalHeight;

        // Vẽ cột với màu pha trộn từ ngọn xuống gốc
        DrawRectangleGradientV((int)x, (int)y, (int)actualWidth, (int)finalHeight, topColor, bottomColor);
    }
}

// Hàm chính vẽ giao diện Menu
void UI::drawMainMenu(int latestScore){
    // Hàm tô màu nền giao diện
    drawBackgroundColor(550, { 11, 30, 104, 255 }, { 5, 15, 60, 255 });
    
    Color darkSapphire = { 11, 30, 104, 255 }; 
    Color planetCyan = { 0, 255, 255, 255 };
    // Gọi hàm vẽ trăng khuyết
    drawFadingPlanet(50, 50, 200, planetCyan, darkSapphire);
    drawFadingPlanet(1500, 50, 100, planetCyan, darkSapphire);

    // Hàm vẽ tên game chính giữa màn hình
    DrawTextEx(myFont, "HÀNH TRÌNH VƯỢT ẢI", {350.0f, 120.0f}, 100.0f, 3.0f, { 0, 255, 255, 255 });

    // Hàm vẽ khung điểm
    const char* scoreText = TextFormat("Điểm mới nhất: %d%%", latestScore);
    drawEntireButton(1150, 30, 370, 70, scoreText);

    // Hàm vẽ nhân vật
    SkinManager skinManager;
    skinManager.drawSkin(900.0f, 360.0f, 80.0f);

    // Hàm vẽ chướng ngại vật
    Obstacle obstacle(0, 1150.0f, 330.0f, 120.0f, 220.0f);
    obstacle.draw();

    // Hàm vẽ nốt nhạc
    drawRhythmicLines();

    // Hàm vẽ 4 nút chức năng chính
    drawEntireButton(100, 600, 300, 140, "CHƠI NGAY", iconPlay);
    drawEntireButton(450, 600, 300, 140, "MÀN CHƠI", iconMap);
    drawEntireButton(800, 600, 300, 140, "NGOẠI HÌNH", iconSkin);
    drawEntireButton(1150, 600, 300, 140, "HƯỚNG DẪN", iconGuide);
}