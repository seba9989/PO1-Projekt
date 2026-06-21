#include <cstdlib>
#include <ctime>
#include <numeric>
#include <map>
#include <string>
#include "raylib.h"
#include "gui/pause/pause.h"
#include "entity/player/player.hpp"
#include "entity/enemy/enemy.hpp"
#include "entity/bunker/bunker.hpp"
#include "entity/powerup/powerup.hpp"
#include "entity/ufo/ufo.hpp"
#include "utils/collision/collision.hpp"
#include "utils/spawner/spawner.hpp"
#include "utils/states/gamestate.hpp"
#include "utils/highscore/highscore.hpp"

/**
 * @file main.cpp
 * @brief Główny plik projektu z pętlą gry Space Invaders.
 * 
 * Zawiera maszynę stanów do obsługi GUI oraz wywołania systemów gry.
 */

int main(void)
{
  // Inicjalizacja gry
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Space Invaders");
  SetExitKey(KEY_NULL); // Zapobiega zamykaniu okna przez klawisz ESC

  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  SetTargetFPS(60);

  // Maszyna Stanow
  GameState currentState = GameState::MENU;

  // System Wynikow
  HighscoreManager highscoreManager("highscores.txt");
  std::string playerName = "";
  int nameLetterCount = 0;

  // Zmienne stanu gry
  bool gameOver = false;
  int currentLevel = 1;
  int score = 0;

  Player player;
  Spawner spawner;
  std::vector<Enemy> enemies = spawner.SpawnWave(5, 11, currentLevel);
  std::vector<PowerUp> powerups;
  Ufo ufo;
  CollisionManager collisionManager;

  // Tworzenie bunkrow w ksztalcie
  std::vector<Bunker> bunkers;
  auto ResetBunkers = [&]() {
      bunkers.clear();
      for (int b = 0; b < 4; b++)
      {
        float offsetX = 100.0f + b * 180.0f;
        float offsetY = screenHeight - 100.0f;
        for (int row = 0; row < 4; row++)
        {
          for (int col = 0; col < 6; col++)
          {
            if (row >= 2 && (col == 2 || col == 3)) continue;
            bunkers.emplace_back(Vector2{ offsetX + col * 10.0f, offsetY + row * 10.0f });
          }
        }
      }
  };
  ResetBunkers();

  // Glowna petla gry
  while (!WindowShouldClose())
  {
    // === UPDATE PHASE ===
    switch (currentState) {
      case GameState::MENU:
        if (IsKeyPressed(KEY_ONE)) currentState = GameState::PLAYING;
        if (IsKeyPressed(KEY_TWO)) currentState = GameState::LEADERBOARD;
        if (IsKeyPressed(KEY_THREE)) currentState = GameState::HELP;
        break;

      case GameState::HELP:
        if (IsKeyPressed(KEY_ESCAPE)) currentState = GameState::MENU;
        break;

      case GameState::LEADERBOARD:
        if (IsKeyPressed(KEY_ESCAPE)) currentState = GameState::MENU;
        break;

      case GameState::PLAYING:
        if (!PAUSE && !gameOver)
        {
          // Obsługa wejścia gracza
          if (IsKeyPressed(KEY_SPACE))
          {
            player.Shoot();
          }

          // Aktualizacja logiki gracza
          player.Update();

          // Aktualizacja wrogów
          Enemy::needsDropDown = false;
          for (auto& enemy : enemies)
          {
            enemy.Update();
          }

          // Obniżenie wrogów
          if (Enemy::needsDropDown)
          {
            Enemy::moveDirection *= -1;
            for (auto& enemy : enemies)
            {
              enemy.DropDown();
            }
          }

          // Aktualizacja bunkrów
          for (auto& bunker : bunkers)
          {
            bunker.Update();
          }

          // Aktualizacja powerupów
          for (auto& p : powerups)
          {
              p.Update();
          }

          // Sprawdzanie kolizji
          collisionManager.CheckCollisionsSingleShooter(player, enemies);
          collisionManager.CheckCollisionsSingleShooter(player, bunkers);
          collisionManager.CheckCollisions(enemies, player);
          collisionManager.CheckCollisions(enemies, bunkers);

          // Obsługa UFO (szansa 1 na 3000 w klatce)
          if (!ufo.active && GetRandomValue(1, 3000) == 1) {
              ufo.Spawn();
          }
          ufo.Update();

          // Kolizje gracza z UFO
          if (ufo.active) {
              for (auto& projectile : player.GetProjectiles()) {
                  if (!projectile.IsActive()) continue;
                  Rectangle projRect = {
                      projectile.GetPosition().x - projectile.GetRadius(),
                      projectile.GetPosition().y - projectile.GetRadius(),
                      projectile.GetRadius() * 2, projectile.GetRadius() * 2
                  };
                  if (CheckCollisionRecs(projRect, ufo.GetBounds())) {
                      projectile.SetActive(false);
                      ufo.active = false;
                      ufo.lastScore = ufo.scoreValue;
                      score += ufo.scoreValue;
                      ufo.popupTimer = 1.0f;
                      ufo.deathPos = ufo.GetPosition();
                      break;
                  }
              }
          }

          // Zbieranie powerupow przez gracza
          for (auto& p : powerups) {
              if (p.active && CheckCollisionRecs(p.GetBounds(), player.GetBounds())) {
                  p.active = false;
                  if (p.type == PowerUpType::HEAL) {
                      player.Heal(1.0f);
                  } else if (p.type == PowerUpType::DOUBLE_SHOT) {
                      player.ActivateDoubleShot(5.0f); // 5 sekund podwójnego strzału
                  }
                  score += 500;
              }
          }

          // Zliczanie punktów i dropów
          for (auto& enemy : enemies) {
              if (enemy.IsDead()) {
                  score += 100 + 25 * enemy.row;
                  // Szansa 25% na wypadniecie skrzynki
                  if (GetRandomValue(1, 100) <= 25) {
                      powerups.emplace_back(enemy.GetPosition());
                  }
              }
          }

          std::erase_if(enemies, [](const Enemy& e) { return e.IsDead(); });
          std::erase_if(bunkers, [](const Bunker& b) { return b.IsDead(); });
          std::erase_if(powerups, [](const PowerUp& p) { return !p.active; });

          // Mechanika strzelania wroga (tylko dolny rząd)
          std::map<int, Enemy*> bottomEnemies;
          for (auto& e : enemies)
          {
            e.canShoot = false;
            if (bottomEnemies.find(e.col) == bottomEnemies.end() || bottomEnemies[e.col]->row < e.row)
            {
              bottomEnemies[e.col] = &e;
            }
          }
          for (auto const& [col, e] : bottomEnemies)
          {
            e->canShoot = true;
          }

          // Warunki zakończenia gry
          if (player.IsDead()) gameOver = true;
          
          // Warunek przejscia na kolejny poziom
          if (enemies.empty()) 
          {
             currentLevel++;
             enemies = spawner.SpawnWave(5, 11, currentLevel);
             ResetBunkers();
             powerups.clear();
             ufo.active = false;
             ufo.popupTimer = 0.0f;
             player.Heal(1.0f);
             Enemy::moveDirection = 1;
             Enemy::needsDropDown = false;
          }
        }

        // Obsługa przejscia do zapisu
        if (gameOver)
        {
          if (IsKeyPressed(KEY_SPACE))
          {
             currentState = GameState::NAME_INPUT;
             playerName = "";
             nameLetterCount = 0;
          }
        }
        break;

      case GameState::NAME_INPUT:
        int key = GetCharPressed();
        while (key > 0)
        {
          if ((key >= 32) && (key <= 125) && (nameLetterCount < 15))
          {
            playerName += (char)key;
            nameLetterCount++;
          }
          key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && nameLetterCount > 0)
        {
          playerName.pop_back();
          nameLetterCount--;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
          highscoreManager.AddScore(playerName, score);
          
          // Twardy reset rozgrywki
          gameOver = false;
          currentLevel = 1;
          score = 0;
          player = Player();
          Enemy::moveDirection = 1;
          Enemy::needsDropDown = false;
          enemies = spawner.SpawnWave(5, 11, currentLevel);
          ResetBunkers();
          powerups.clear();
          ufo.active = false;
          ufo.popupTimer = 0.0f;
          
          currentState = GameState::LEADERBOARD;
        }
        break;
    }

    // === DRAWING PHASE ===
    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (currentState) {
        case GameState::MENU:
            DrawText("SPACE INVADERS", screenWidth/2 - MeasureText("SPACE INVADERS", 40)/2, 100, 40, DARKBLUE);
            DrawText("1. Graj", screenWidth/2 - MeasureText("1. Graj", 20)/2, 200, 20, DARKGRAY);
            DrawText("2. Najlepsze Wyniki", screenWidth/2 - MeasureText("2. Najlepsze Wyniki", 20)/2, 230, 20, DARKGRAY);
            DrawText("3. Pomoc / Sterowanie", screenWidth/2 - MeasureText("3. Pomoc / Sterowanie", 20)/2, 260, 20, DARKGRAY);
            DrawText("Autorzy: Kordian Dziedzic, Sebastian Grzybowski", 10, screenHeight - 20, 10, GRAY);
            break;

        case GameState::HELP:
            DrawText("POMOC / STEROWANIE", screenWidth/2 - MeasureText("POMOC / STEROWANIE", 30)/2, 50, 30, DARKBLUE);
            DrawText("- A / D lub Strzalki - Poruszanie Statkiem", 100, 150, 20, DARKGRAY);
            DrawText("- Spacja - Strzelanie w kosmitow", 100, 190, 20, DARKGRAY);
            DrawText("- ESC - Pauzowanie gry", 100, 230, 20, DARKGRAY);
            DrawText("- Ze zniszczonych wrogow moga wypasc skrzynki (+1 HP, +500 pkt)", 50, 270, 20, DARKGREEN);
            DrawText("Wcisnij ESC aby wrocic do Menu", screenWidth/2 - MeasureText("Wcisnij ESC aby wrocic do Menu", 20)/2, screenHeight - 50, 20, GRAY);
            break;

        case GameState::LEADERBOARD:
            DrawText("TABLICA WYNIKOW", screenWidth/2 - MeasureText("TABLICA WYNIKOW", 30)/2, 50, 30, DARKBLUE);
            {
                auto topScores = highscoreManager.GetTopScores(5);
                if (topScores.empty()) {
                    DrawText("Brak wynikow. Zagraj najpierw w gre!", screenWidth/2 - MeasureText("Brak wynikow. Zagraj najpierw w gre!", 20)/2, 150, 20, DARKGRAY);
                } else {
                    for (size_t i = 0; i < topScores.size(); i++) {
                        DrawText(TextFormat("%d. %s - %d", (int)i+1, topScores[i].name.c_str(), topScores[i].score), screenWidth/2 - 100, 120 + (int)i*40, 20, DARKGRAY);
                    }
                }
            }
            DrawText("Wcisnij ESC aby wrocic do Menu", screenWidth/2 - MeasureText("Wcisnij ESC aby wrocic do Menu", 20)/2, screenHeight - 50, 20, GRAY);
            break;

        case GameState::PLAYING:
            player.Draw();
            for (auto& enemy : enemies) enemy.Draw();
            for (auto& bunker : bunkers) bunker.Draw();
            for (auto& p : powerups) p.Draw();
            ufo.Draw();

            // HUD
            DrawText(TextFormat("SCORE: %d", score), 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("LEVEL: %d", currentLevel), screenWidth/2 - 40, 10, 20, DARKGRAY);
            DrawText(TextFormat("HP: %.0f", player.GetHP()), screenWidth - 100, 10, 20, DARKGRAY);

            // Ekran Game Over
            if (gameOver)
            {
              DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40)/2, screenHeight / 2 - 30, 40, RED);
              DrawText("Nacisnij SPACJE aby zapisac wynik", screenWidth / 2 - MeasureText("Nacisnij SPACJE aby zapisac wynik", 20)/2, screenHeight / 2 + 20, 20, DARKGRAY);
            }

            PauseMenu();
            break;

        case GameState::NAME_INPUT:
            DrawText("ZAPISZ SWOJ WYNIK", screenWidth/2 - MeasureText("ZAPISZ SWOJ WYNIK", 30)/2, 100, 30, DARKBLUE);
            DrawText("Wpisz swoj nick:", screenWidth/2 - MeasureText("Wpisz swoj nick:", 20)/2, 180, 20, DARKGRAY);
            
            DrawRectangle(screenWidth/2 - 150, 220, 300, 40, LIGHTGRAY);
            DrawRectangleLines(screenWidth/2 - 150, 220, 300, 40, DARKGRAY);
            DrawText(playerName.c_str(), screenWidth/2 - MeasureText(playerName.c_str(), 20)/2, 230, 20, MAROON);
            
            DrawText("Nacisnij ENTER aby zatwierdzic", screenWidth/2 - MeasureText("Nacisnij ENTER aby zatwierdzic", 20)/2, 300, 20, GRAY);
            break;
    }

    EndDrawing();
  }

  // Deinicjalizacja
  CloseWindow();
  return 0;
}