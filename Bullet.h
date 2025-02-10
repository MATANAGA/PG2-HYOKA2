#ifndef BULLET_H
#define BULLET_H

#include <Novice.h>
#include "Vector2.h"

class Bullet {
private:
    Vector2 pos;
    float speed;
    float radius;
    int textureID;
    bool isAlive;
    float dx, dy;  // 用于方向控制

public:
    Bullet(float x, float y);  // ✅ 需要有这个声明
    Bullet(float x, float y, float dx, float dy); // ✅ 另一个构造函数
    void Update();
    void Draw();

    bool CheckCollision(float targetX, float targetY, float targetRadius)const;
    bool GetIsAlive() const { return isAlive; }
};

#endif
