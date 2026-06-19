#pragma once
#include <vector>
#include <raylib.h>
#include "entity/enemy/enemy.hpp"

class Spawner
{
 public:
  Spawner();
  ~Spawner();
  std::vector<Enemy> SpawnWave(int rows, int cols);
};
