#include "spawner.hpp"

Spawner::Spawner() {}

Spawner::~Spawner() {}

std::vector<Enemy> Spawner::SpawnWave(int rows, int cols)
{
  std::vector<Enemy> enemies;

  float enemyWidth = 30.0f;
  float enemyHeight = 25.0f;
  float paddingX = 10.0f;
  float paddingY = 10.0f;

  // Oblicz całkowitą szerokość siatki
  float totalWidth = cols * enemyWidth + (cols - 1) * paddingX;
  // Wyśrodkuj siatkę na ekranie
  float startX = (GetScreenWidth() - totalWidth) / 2.0f;
  float startY = 40.0f;

  for (int row = 0; row < rows; row++)
  {
    for (int col = 0; col < cols; col++)
    {
      float x = startX + col * (enemyWidth + paddingX);
      float y = startY + row * (enemyHeight + paddingY);
      enemies.emplace_back(Vector2{x, y});
    }
  }

  return enemies;
}
