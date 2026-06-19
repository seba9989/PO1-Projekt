#include "enemy.hpp"
#include <cstdlib>

// Inicjalizacja pól statycznych
int Enemy::moveDirection = 1;
bool Enemy::needsDropDown = false;

Enemy::Enemy()
{
  position = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  speed = 1.5f;
}

Enemy::Enemy(Vector2 pos)
{
  position = pos;
  speed = 1.5f;
}

Enemy::~Enemy() {}

void Enemy::Update()
{
  // Ruch w poziomie
  position.x += speed * moveDirection;

  // Sprawdź czy wróg dotknął krawędzi ekranu
  if (position.x + width >= GetScreenWidth() - margin || position.x <= margin)
  {
    needsDropDown = true;
  }

  // Aktualizuj pociski wroga
  for (auto& p : projectile_s)
  {
    p.Update();
  }
  std::erase_if(projectile_s, [](const Projectile& p) { return !p.IsActive(); });

  // Losowe strzelanie (szansa 1/400 na klatkę)
  if (std::rand() % 400 == 0)
  {
    Shoot();
  }
}

void Enemy::Draw()
{
  if (IsDead()) return;
  DrawRectangle(position.x, position.y, width, height, color_s.at(hp - 1));

  // Rysuj pociski wroga
  for (auto& p : projectile_s)
  {
    p.Draw();
  }
}

void Enemy::Shoot()
{
  if (static_cast<int>(projectile_s.size()) < projectileCountMax)
  {
    // Pocisk startuje ze środka dolnej krawędzi wroga, leci w dół (+1)
    Vector2 shootPos = {position.x + width / 2.0f, position.y + height};
    projectile_s.emplace_back(shootPos, 1, 2.5f);
  }
}

void Enemy::DropDown()
{
  position.y += dropAmount;
}

float Enemy::GetRadius() const { return width; }

Rectangle Enemy::GetBounds() const
{
  return Rectangle{position.x, position.y, width, height};
}

void Enemy::TakeDamage() { hp -= 1; }

bool Enemy::IsDead() const { return hp <= 0; }

std::vector<Projectile>& Enemy::GetProjectiles() { return projectile_s; }