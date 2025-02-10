#include "Bullet.h"
#include <cmath>

Bullet::Bullet(float x, float y) {
    pos.x = x;
    pos.y = y;
    speed = 8;
    radius = 8;
    isAlive = true;
    dx = 0;
    dy = -1;
    textureID = Novice::LoadTexture("./Resources/Images/mizu.png");
}

Bullet::Bullet(float x, float y, float dx, float dy) {
    pos.x = x;
    pos.y = y;
    speed = 5;
    radius = 8;
    isAlive = true;
    this->dx = dx;
    this->dy = dy;
    textureID = Novice::LoadTexture("./Resources/Images/mizu.png");
}

void Bullet::Update() {
    pos.x += dx * speed;
    pos.y += dy * speed;
    if (pos.y <= 10 || pos.y >= 720 || pos.x <= 0 || pos.x >= 1280) {
        isAlive = false;
    }
}

void Bullet::Draw() {
    if (isAlive) {
        Novice::DrawSprite((int)pos.x, (int)pos.y, textureID, 0.1f, 0.1f, 0.0f, WHITE);
    }
}

bool Bullet::CheckCollision(float targetX, float targetY, float targetRadius) const {

    float deltaX = targetX - pos.x;
    float deltaY = targetY - pos.y;
    float distanceSquared = deltaX * deltaX + deltaY * deltaY;
    float radiusSum = targetRadius + radius;
    return distanceSquared < (radiusSum * radiusSum);
}
