#include "Player.h"

Player::Player() {
    pos.x = 500;
    pos.y = 500;
    speed = 10;
    health = 30;
    radius = 12;
    shootCoolTime = 0;  // 初始化冷却时间
    isAlive = true;
    textureID = Novice::LoadTexture("./Resources/Images/player.png");
}

void Player::Update(const char* keys, std::vector<Bullet>& bullets) {
    if (keys[DIK_RIGHT]) { pos.x += speed; }
    if (keys[DIK_LEFT]) { pos.x -= speed; }
    if (keys[DIK_UP]) { pos.y -= speed; }
    if (keys[DIK_DOWN]) { pos.y += speed; }

    // 限制玩家移动范围
    if (pos.x < 0) pos.x = 0;
    if (pos.x > 1280 - radius) pos.x = 1280 - radius;
    if (pos.y < 0) pos.y = 0;
    if (pos.y > 650 - radius) pos.y = 650 - radius;

    // 发射子弹 (按 Z 键)
    if (shootCoolTime > 0) {
        shootCoolTime--;  // 让冷却时间递减
    }
    if (keys[DIK_Z] && shootCoolTime <= 0) {
        Shoot(bullets);
        shootCoolTime = 10;  // 重新设置冷却时间
    }
}



void Player::Draw() {
    Novice::DrawSprite((int)pos.x, (int)pos.y, textureID, 0.5f, 0.5f, 0.0f, WHITE);

}

void Player::Shoot(std::vector<Bullet>& bullets) {
    bullets.push_back(Bullet(pos.x + radius / 2, pos.y));
}

