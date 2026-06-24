#include "enemy.hpp"
#include <cstdlib>

// Inicjalizacja pól statycznych
int Enemy::moveDirection = 1;
bool Enemy::needsDropDown = false;

Enemy::Enemy()
{
  position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
  speed = 1.5f;
}

Enemy::Enemy(Vector2 position, int row, int col, int level)
{
  this->position = position;
  this->speed =
      0.5f + (level * 0.2f);  // Zwiększanie prędkości ruchu wraz z poziomem
  this->shootChance = 100 - (level * 5);  // Zwiększanie szansy na strzał
  if (this->shootChance < 20)
    this->shootChance = 20;  // Hard cap, żeby gra była w ogóle możliwa
  this->row = row;
  this->col = col;
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
  std::erase_if(projectile_s,
                [](const Projectile& p) { return !p.IsActive(); });

  // Losowe strzelanie bazujące na shootChance (które zależy od poziomu)
  if (canShoot && (std::rand() % shootChance == 0))
  {
    Shoot();
  }
}

void Enemy::Draw()
{
  if (IsDead()) return;

  Color c = color_s.at(hp - 1);
  float x = position.x;
  float y = position.y;

  // Czułki
  DrawRectangle(x + 4, y, 4, 5, c);
  DrawRectangle(x + 22, y, 4, 5, c);
  // Górna część głowy
  DrawRectangle(x + 8, y + 4, 14, 6, c);
  // Główny tułów
  DrawRectangle(x, y + 10, 30, 10, c);
  // Oczy (wycięte, czyli czarne)
  DrawRectangle(x + 6, y + 12, 4, 4, BLACK);
  DrawRectangle(x + 20, y + 12, 4, 4, BLACK);
  // Nóżki / Macki
  DrawRectangle(x, y + 20, 6, 5, c);
  DrawRectangle(x + 10, y + 20, 4, 5, c);
  DrawRectangle(x + 16, y + 20, 4, 5, c);
  DrawRectangle(x + 24, y + 20, 6, 5, c);

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
    Vector2 shootPos = { position.x + width / 2.0f, position.y + height };
    projectile_s.emplace_back(shootPos, 1, 2.5f);
  }
}

void Enemy::DropDown() { position.y += dropAmount; }

float Enemy::GetRadius() const { return width; }

Rectangle Enemy::GetBounds() const
{
  return Rectangle{ position.x, position.y, width, height };
}

void Enemy::TakeDamage() { hp -= 1; }

bool Enemy::IsDead() const { return hp <= 0; }

std::vector<Projectile>& Enemy::GetProjectiles() { return projectile_s; }