#pragma once
#include <vector>
#include <raylib.h>
#include "entity/enemy/enemy.hpp"

/**
 * @brief Klasa narzędziowa fabryki (Spawner) służąca do generowania bytów.
 * 
 * Odpowiada za tworzenie kolekcji obiektów (np. całych fal wrogów) i ustawianie
 * ich na odpowiednich pozycjach w oparciu o szablony C++.
 */
class Spawner
{
 public:
  /**
   * @brief Inicjalizuje obiekt spawnera.
   */
  Spawner() = default;

  /**
   * @brief Zwalnia zasoby spawnera.
   */
  ~Spawner() = default;

  /**
   * @brief Generyczna funkcja do masowego tworzenia identycznych obiektów.
   * 
   * @tparam T Typ obiektu do wygenerowania (np. Projectile, Bunker).
   * @tparam Args Typy argumentów konstruktora obiektu T.
   * @param count Liczba obiektów do utworzenia.
   * @param args Argumenty przekazywane do konstruktora każdego obiektu.
   * @return Wektor wygenerowanych obiektów.
   */
  template <typename T, typename... Args>
  std::vector<T> Spawn(int count, Args&&... args)
  {
    std::vector<T> entities;
    for (int i = 0; i < count; ++i)
    {
      entities.emplace_back(std::forward<Args>(args)...);
    }
    return entities;
  }

  /**
   * @brief Generuje uporządkowaną falę wrogów (siatkę 2D).
   * 
   * @param rows Liczba rzędów wrogów.
   * @param cols Liczba kolumn wrogów.
   * @param level Aktualny poziom trudności.
   * @return Wektor zawierający falę wrogów ustawionych na pozycjach startowych.
   */
  std::vector<Enemy> SpawnWave(int rows, int cols, int level = 1)
  {
    std::vector<Enemy> wave;
    float startX = (GetScreenWidth() - (cols * 50.0f)) / 2.0f;
    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < cols; c++) {
        wave.emplace_back(Vector2{startX + c * 50.0f, 50.0f + r * 40.0f}, r, c, level);
      }
    }
    return wave;
  }
};
