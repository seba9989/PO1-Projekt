#pragma once
#include <vector>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#include "../projectile/projectile.hpp"
#include <entity/entity.hpp>

class Player : public Entity
{
 private:
  float hp = 3;
  std::vector<Projectile> projectile_s = {};
  int projectileCountMax = 1;

  float margin = 24.0f;
  float radius = 12.0f;

 public:
  Player();
  ~Player();

  void Update();
  void Draw();
  void Shoot();
  void TakeDamage();
  bool IsDead() const;
  float GetHP() const;
  Rectangle GetBounds() const;
  std::vector<Projectile>& GetProjectiles();
  void RemoveProjectile(int index);
};