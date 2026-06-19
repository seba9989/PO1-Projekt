#include "player.hpp"

Player::Player()
{
  position = {GetScreenWidth() / 2.0f, GetScreenHeight() - 24.0f};
  speed = 4.0f;
}

Player::~Player() {}

void Player::Update()
{
  // Obsługa ruchu gracza
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
  {
    position.x -= speed;
  }
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
  {
    position.x += speed;
  }

  position.x = Clamp(position.x, margin, GetScreenWidth() - margin);

  // Aktualizacja pocisków
  for (auto& p : projectile_s)
  {
    p.Update();
  }
  std::erase_if(projectile_s, [](const Projectile& p) { return !p.IsActive(); });
}

void Player::Draw()
{
  // Rysuj pociski
  for (auto& p : projectile_s)
  {
    p.Draw();
  }

  // Rysuj gracza
  DrawCircleV(position, radius, MAROON);
}

void Player::Shoot()
{
  if (static_cast<int>(projectile_s.size()) < projectileCountMax)
  {
    projectile_s.emplace_back(Vector2(position), -1);
  }
}

void Player::TakeDamage() { hp -= 1; }

bool Player::IsDead() const { return hp <= 0; }

float Player::GetHP() const { return hp; }

Rectangle Player::GetBounds() const
{
  return Rectangle{position.x - radius, position.y - radius, radius * 2, radius * 2};
}

std::vector<Projectile>& Player::GetProjectiles() { return projectile_s; }

void Player::RemoveProjectile(int index)
{
  if (index >= 0 && index < static_cast<int>(projectile_s.size()))
  {
    projectile_s.erase(projectile_s.begin() + index);
  }
}