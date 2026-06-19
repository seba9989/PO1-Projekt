#pragma once
#include <raylib.h>

class Entity
{
 protected:
  Vector2 position;
  float speed;

 public:
  virtual void Draw() = 0;
  virtual ~Entity() = default;
  Vector2 GetPosition() const;
};