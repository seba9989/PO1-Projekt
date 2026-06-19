#pragma once
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include "../projectile/projectile.hpp"
#include <entity/entity.hpp>

class Enemy : public Entity
{
 private:
  float hp = 3;
  std::vector<Color> color_s = {RED, ORANGE, BLUE};
  std::vector<Projectile> projectile_s = {};
  int projectileCountMax = 1;

  float margin = 24.0f;
  float width = 30.0f;
  float height = 25.0f;
  float dropAmount = 5.0f;

 public:
  static int moveDirection;    // 1 = prawo, -1 = lewo
  static bool needsDropDown;   // flaga: czy wrogowie mają skoczyć w dół

  Enemy();
  Enemy(Vector2 pos);
  ~Enemy();

  void Update();
  void Draw();
  void DropDown();
  void Shoot();

  Vector2 GetPosition() const;
  float GetRadius() const;
  Rectangle GetBounds() const;
  void TakeDamage();
  bool IsDead() const;
  std::vector<Projectile>& GetProjectiles();
};