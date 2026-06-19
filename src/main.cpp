#include <cstdlib>
#include <ctime>
#include "raylib.h"
#include "gui/pause/pause.h"
#include "entity/player/player.hpp"
#include "entity/enemy/enemy.hpp"
#include "utils/collision/collision.hpp"
#include "utils/spawner/spawner.hpp"

int main(void)
{
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Space Invaders");

  std::srand(std::time(nullptr));

  SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

  // Stany gry
  bool gameOver = false;
  bool gameWon = false;
  int score = 0;

  Player player;
  Spawner spawner;
  std::vector<Enemy> enemies = spawner.SpawnWave(5, 11);
  CollisionManager collisionManager;

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    if (!PAUSE && !gameOver && !gameWon)
    {
      // Strzelanie gracza
      if (IsKeyPressed(KEY_SPACE))
      {
        player.Shoot();
      }

      // Update gracza (ruch + pociski)
      player.Update();

      // Update wrogów (ruch + strzelanie + pociski)
      Enemy::needsDropDown = false;
      for (auto& enemy : enemies)
      {
        enemy.Update();
      }

      // Jeśli którykolwiek wróg dotknął krawędzi — wszyscy schodzą w dół
      if (Enemy::needsDropDown)
      {
        Enemy::moveDirection *= -1;
        for (auto& enemy : enemies)
        {
          enemy.DropDown();
        }
      }

      // Kolizje: pocisk gracza -> wróg
      collisionManager.CheckProjectileEnemyCollisions(player.GetProjectiles(), enemies);

      // Kolizje: pocisk wroga -> gracz
      collisionManager.CheckEnemyProjectilePlayerCollisions(enemies, player);

      // Zlicz zabitych wrogów i usuń martwych
      int beforeCount = static_cast<int>(enemies.size());
      std::erase_if(enemies, [](const Enemy& e) { return e.IsDead(); });
      int killed = beforeCount - static_cast<int>(enemies.size());
      score += killed * 100;

      // Sprawdź warunki końca gry
      if (player.IsDead())
      {
        gameOver = true;
      }
      if (enemies.empty())
      {
        gameWon = true;
      }
    }

    // Restart gry klawiszem R
    if ((gameOver || gameWon) && IsKeyPressed(KEY_R))
    {
      gameOver = false;
      gameWon = false;
      score = 0;
      player = Player();
      Enemy::moveDirection = 1;
      Enemy::needsDropDown = false;
      enemies = spawner.SpawnWave(5, 11);
    }

    // Draw
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      player.Draw();

      for (auto& enemy : enemies)
      {
        enemy.Draw();
      }

      // HUD — wynik i życia
      DrawText(TextFormat("SCORE: %d", score), 10, 10, 20, DARKGRAY);
      DrawText(TextFormat("HP: %.0f", player.GetHP()), screenWidth - 100, 10, 20, DARKGRAY);

      // Ekran Game Over
      if (gameOver)
      {
        DrawText("GAME OVER", screenWidth / 2 - 120, screenHeight / 2 - 30, 40, RED);
        DrawText("Nacisnij R aby zagrac ponownie", screenWidth / 2 - 170, screenHeight / 2 + 20, 20, DARKGRAY);
      }

      // Ekran wygranej
      if (gameWon)
      {
        DrawText("YOU WIN!", screenWidth / 2 - 100, screenHeight / 2 - 30, 40, GREEN);
        DrawText("Nacisnij R aby zagrac ponownie",  screenWidth / 2 - 170, screenHeight / 2 + 20, 20, DARKGRAY);
      }

      PauseMenu();
    }
    EndDrawing();
  }

  // De-ini
  CloseWindow();  // Close window

  return 0;
}