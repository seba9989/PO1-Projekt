#pragma once
#include <vector>
#include <raylib.h>
#include "entity/projectile/projectile.hpp"
#include "entity/enemy/enemy.hpp"
#include "entity/player/player.hpp"

class CollisionManager
{
 public:
  void CheckProjectileEnemyCollisions(std::vector<Projectile>& projectiles, std::vector<Enemy>& enemies);
  void CheckEnemyProjectilePlayerCollisions(std::vector<Enemy>& enemies, Player& player);
};