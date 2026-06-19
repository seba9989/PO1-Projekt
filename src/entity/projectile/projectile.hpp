#pragma once
#include "raylib.h"

class Projectile
{
 private:
  Vector2 position = {};
  float speed = 4.0f;
  bool active = true;
  int direction = -1;  // -1 = w górę (gracz), +1 = w dół (wróg)

 public:
  Projectile(Vector2 position, int direction = -1, float speed = 4.0f);
  ~Projectile();

  void Update();
  void Draw();
  bool IsOutOfBounds() const;
  bool IsActive() const;
  Vector2 GetPosition() const;
  float GetRadius() const;
  void SetActive(bool active);
};