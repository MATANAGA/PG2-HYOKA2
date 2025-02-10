#ifndef PLAYER_H
#define PLAYER_H

#include <Novice.h>
#include "Vector2.h"
#include "Bullet.h"
#include <vector>

class Player {
private:
    Vector2 pos;
    float speed;
    int health;
    float radius;
    int shootCoolTime;
    int textureID;
    bool isAlive;

public:
    Player();
    float GetRadius() const { return radius; }
    void Update(const char* keys, std::vector<Bullet>& bullets);
    void Draw();
    void Shoot(std::vector<Bullet>& bullets);
    bool GetIsAlive() const { return isAlive; }
    Vector2 GetPosition() const { return pos; }
    void TakeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            health = 0;
            isAlive = false;
        }
    }
};

#endif
