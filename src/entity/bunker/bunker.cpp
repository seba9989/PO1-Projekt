#include "bunker.hpp"
#include <algorithm>

Bunker::Bunker(Vector2 position)
{
  this->position = position;
  this->speed = 0.0f;
}

void Bunker::Update()
{
  // Bunkry się nie poruszają
}

void Bunker::Draw()
{
  if (IsDead()) return;

  DrawRectangleV(position, Vector2{ width, height }, ORANGE);
  DrawRectangleLines(position.x, position.y, width, height, DARKGRAY);
}

Rectangle Bunker::GetBounds() const
{
  return Rectangle{ position.x, position.y, width, height };
}

void Bunker::TakeDamage()
{
  hp = 0;
}

bool Bunker::IsDead() const { return hp <= 0; }
