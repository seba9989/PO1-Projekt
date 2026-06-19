#include "projectile.hpp"

Projectile::Projectile(Vector2 position, int direction, float speed)
{
  this->position = position;
  this->direction = direction;
  this->speed = speed;
}

Projectile::~Projectile() {}

void Projectile::Update()
{
  position.y += speed * direction;
  if (IsOutOfBounds()) active = false;
}

void Projectile::Draw()
{
  Color color = (direction == -1) ? MAROON : GREEN;
  DrawCircleV(position, 6, color);
}

bool Projectile::IsOutOfBounds() const
{
  return position.y < 0.0f || position.y > GetScreenHeight() || position.x < 0.0f || position.x > GetScreenWidth();
}

bool Projectile::IsActive() const { return active; }
Vector2 Projectile::GetPosition() const { return position; }
float Projectile::GetRadius() const { return 6.0f; }
void Projectile::SetActive(bool active) { this->active = active; }