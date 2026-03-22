#include "../include/Player.h"

Player::Player(float startX, float startY){
    x = startX;
    y = startY;
    size = 60.0f;
    velocity = 0.0f;
    gravity = 0.5f;
}

void Player::update(){
}

void Player::draw(SkinManager& skinManager){
    skinManager.drawSkin(this->x, this->y, this->size);
}