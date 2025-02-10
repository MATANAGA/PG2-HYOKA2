#include "Enemy.h"
#include <cmath>  
#include <cstdlib> 

Enemy::Enemy(float x, float y) {
    pos.x = x;
    pos.y = y;
    speed = 2;
    health = 1000;
    radius = 32;
    isAlive = true;
    shootCoolTime = 5;
    textureID = Novice::LoadTexture("./Resources/Images/yinyang.png");
}

void Enemy::Update(const Vector2& playerPos) {
    // 让敌人出现在屏幕内
    if (pos.y < 50) {
        pos.y += speed;
    }
    else {
        pos.x += speed;
        if (pos.x >= 600 - radius || pos.x <= 100 + radius) {
            speed = -speed;
        }
    }

    // 发射子弹逻辑
    if (shootCoolTime > 0) {
        shootCoolTime--;
    }
    if (shootCoolTime <= 0) {
        Shoot(playerPos);
        shootCoolTime = 160;
    }

    // 更新子弹
    for (auto it = bullets.begin(); it != bullets.end();) {
        it->Update();
        if (!it->GetIsAlive()) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Enemy::Draw() {
    if (isAlive) {
        Novice::DrawSprite((int)pos.x, (int)pos.y, textureID, 1.3f, 1.3f, 0.0f, WHITE);
        for (auto& bullet : bullets) {
            bullet.Draw();
        }
    }

}

void Enemy::Shoot(const Vector2& playerPos) {
    // 计算子弹朝向玩家的方向
    float dx = playerPos.x - pos.x;
    float dy = playerPos.y - pos.y;
    float length = sqrt(dx * dx + dy * dy);
    if (length == 0) return;  // 避免除以零
    dx /= length;
    dy /= length;

    bullets.push_back(Bullet(pos.x, pos.y, dx, dy));  // 生成子弹
}

void Enemy::TakeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        isAlive = false;
    }
}
