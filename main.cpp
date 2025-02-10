#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

const char kWindowTitle[] = "GC1D_04_エイハツ";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

enum Scene
{
	GAMECLEAR,
	GAMEOVER,
	TITLE,
	PLAY

};
int currentScene = TITLE;
int enemyDead = 0;
int playerHealth = 100;



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	char keys[256] = { 0 }, preKeys[256] = { 0 };

	Player player;
	std::vector<Enemy> enemies;




	for (int i = 0; i < 10; i++) {
		float x = 100.0f + (i % 5) * 200.0f;
		float y = -50.0f - (i / 5) * 100.0f;
		enemies.emplace_back(x, y);
	}

	std::vector<Bullet> playerBullets;

	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		player.Update(keys, playerBullets);

		switch (currentScene)
		{
		case GAMECLEAR:
			Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0, 0x606000FF, kFillModeSolid);

			Novice::ScreenPrintf(10, 10, "Game Clear Press Space Back To Title");

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				currentScene = TITLE;

				// 🔹 **重置敌人**
				enemies.clear();
				for (int i = 0; i < 10; i++) {
					float x = 100.0f + (i % 5) * 200.0f;
					float y = -50.0f - (i / 5) * 100.0f;
					enemies.emplace_back(x, y);
				}

				playerBullets.clear();
				enemyDead = 0;
			}
			break;
		case TITLE:
			Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0, BLACK, kFillModeSolid);
			Novice::ScreenPrintf(10, 10, "Press Space To Game Start");

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				currentScene = PLAY;

				enemies.clear();
				for (int i = 0; i < 10; i++) {
					float x = 100.0f + (i % 5) * 200.0f;
					float y = -50.0f - (i / 5) * 100.0f;
					enemies.emplace_back(x, y);
				}

				playerBullets.clear();
				enemyDead = 0;
			}
			break;
		case GAMEOVER:
			Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0, 0x600000FF, kFillModeSolid);
			Novice::ScreenPrintf(10, 10, "Game Over! Press Space To Return To Title");

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				currentScene = TITLE;

				// Reset the enemies
				enemies.clear();
				for (int i = 0; i < 10; i++) {
					float x = 100.0f + (i % 5) * 200.0f;
					float y = -50.0f - (i / 5) * 100.0f;
					enemies.emplace_back(x, y);
				}
				player = Player();  // 重新初始化玩家
				playerBullets.clear();
				enemyDead = 0;
				playerHealth = 100;  // Reset player health
			}
			break;
		case PLAY:
			if (enemyDead == 10)
			{
				currentScene = GAMECLEAR;
			}
			if (playerHealth <= 0) {
				currentScene = GAMEOVER;
			}
			for (auto& enemy : enemies) {
				if (enemy.GetIsAlive()) {
					enemy.Update(player.GetPosition());

					// 🔹 **新增玩家与敌人的碰撞检测**
					float dx = player.GetPosition().x - enemy.GetPosition().x;
					float dy = player.GetPosition().y - enemy.GetPosition().y;
					float distance = (float)sqrt(dx * dx + dy * dy);

					if (distance < player.GetRadius() + 32) { // 32 是敌人的半径
						player.TakeDamage(100); // 玩家直接死亡
						playerHealth = 0;
						currentScene = GAMEOVER;
					}

					// 子弹与玩家碰撞检测
					auto& enemyBullets = enemy.GetBullets();
					for (size_t i = 0; i < enemyBullets.size();) {
						if (enemyBullets[i].CheckCollision(player.GetPosition().x, player.GetPosition().y, player.GetRadius())) {
							player.TakeDamage(100);
							playerHealth -= 100;
							enemy.RemoveBullet(i);
						}
						else {
							++i;
						}
					}
				}
			}

			for (auto& enemy : enemies) {
				if (enemy.GetIsAlive()) {
					enemy.Update(player.GetPosition());

					auto& enemyBullets = enemy.GetBullets();
					for (size_t i = 0; i < enemyBullets.size();) {
						if (enemyBullets[i].CheckCollision(player.GetPosition().x, player.GetPosition().y, player.GetRadius())) {
							player.TakeDamage(100);
							playerHealth -= 100;
							enemy.RemoveBullet(i);
						}
						else {
							++i;
						}
					}
				}

			}

			for (auto& enemy : enemies) {
				if (enemy.GetIsAlive()) {
					enemy.Update(player.GetPosition());
				}
			}
			for (auto it = playerBullets.begin(); it != playerBullets.end();) {
				it->Update();
				if (!it->GetIsAlive()) {
					it = playerBullets.erase(it);
				}
				else {
					++it;
				}
			}

			for (auto& enemy : enemies) {
				if (enemy.GetIsAlive()) {
					for (auto it = playerBullets.begin(); it != playerBullets.end();) {
						if (it->CheckCollision(enemy.GetPosition().x, enemy.GetPosition().y, 32)) {
							enemy.TakeDamage(1000);
							it = playerBullets.erase(it);
							enemyDead++;
						}
						else {
							++it;
						}
					}
				}
			}

			player.Draw();
			for (auto& enemy : enemies) {
				enemy.Draw();
			}
			for (auto& bullet : playerBullets) {
				bullet.Draw();
			}
			Novice::ScreenPrintf(100, 100, ("%d"), enemyDead);
			break;
		}


		Novice::EndFrame();

		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	Novice::Finalize();
	return 0;
}
