#include "player.hpp"

Player::Player()
{
  position = {GetScreenWidth() / 2.0f, GetScreenHeight() - 24.0f};
  speed = 4.0f;
}

Player::~Player() {}

void Player::Update()
{
  if (doubleShotTimer > 0.0f) {
      doubleShotTimer -= GetFrameTime();
  }

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

  // Rysuj gracza (klasyczny statek Space Invaders)
  float x = position.x - radius;
  float y = position.y - radius;

  // Główna baza statku (dół)
  DrawRectangle(x, y + 14, 24, 10, LIME);
  // Drugie piętro statku
  DrawRectangle(x + 2, y + 8, 20, 6, LIME);
  // Działo (środek)
  DrawRectangle(x + 10, y, 4, 8, LIME);
}

void Player::Shoot()
{
  if (doubleShotTimer > 0.0f)
  {
    // Ograniczamy do 4 strzałów (2 podwójne) na ekranie jednocześnie
    if (projectile_s.size() < 4)
    {
      projectile_s.emplace_back(Vector2{ position.x - 8, position.y - radius }, -1, 5.0f);
      projectile_s.emplace_back(Vector2{ position.x + 8, position.y - radius }, -1, 5.0f);
    }
  }
  else
  {
    if (projectile_s.size() < projectileCountMax)
    {
      projectile_s.emplace_back(Vector2{ position.x, position.y - radius }, -1, 5.0f);
    }
  }
}

void Player::ActivateDoubleShot(float duration)
{
    doubleShotTimer = duration;
}

void Player::TakeDamage() { hp -= 1; }

void Player::Heal(float amount) { hp += amount; }

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