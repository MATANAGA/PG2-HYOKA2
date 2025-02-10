#ifndef ENEMY_H
#define ENEMY_H

#include <Novice.h>
#include "Vector2.h"
#include "Bullet.h"
#include <vector>

class Enemy {
private:
    Vector2 pos;
    float speed;
    int health;
    float radius;
    int textureID;
    bool isAlive;
    int shootCoolTime;
    std::vector<Bullet> bullets;

public:
    const std::vector<Bullet>& GetBullets() const { return bullets; }
    void RemoveBullet(size_t index) { bullets.erase(bullets.begin() + index); }
    Enemy(float x, float y);
    void Update(const Vector2& playerPos);
    void Shoot(const Vector2& playerPos);
    void Draw();
    void TakeDamage(int damage);
    bool GetIsAlive() const { return isAlive; }
    Vector2 GetPosition() const { return pos; }
};

#endif
