#pragma once
#include <vector>
#include <raylib.h>
#include "entity/projectile/projectile.hpp"

/**
 * @brief Menedżer odpowiadający za rozwiązywanie kolizji w grze.
 * 
 * Wykorzystuje szablony (templates), aby generycznie sprawdzać kolizje 
 * pomiędzy obiektami potrafiącymi strzelać (posiadającymi wektor Projectile)
 * a obiektami będącymi celami (implementującymi GetBounds() i TakeDamage()).
 */
class CollisionManager
{
 public:
  /**
   * @brief Sprawdza kolizje pomiędzy wektorem strzelców a wektorem celów.
   * 
   * @tparam TShooter Typ obiektu strzelającego (np. Enemy).
   * @tparam TTarget Typ obiektu celu (np. Bunker).
   * @param shooters Referencja do wektora obiektów strzelających.
   * @param targets Referencja do wektora obiektów będących celami.
   */
  template <typename TShooter, typename TTarget>
  void CheckCollisions(std::vector<TShooter>& shooters, std::vector<TTarget>& targets)
  {
    for (auto& shooter : shooters)
    {
      CheckCollisionsSingleShooter(shooter, targets);
    }
  }

  /**
   * @brief Sprawdza kolizje pomiędzy wektorem strzelców a pojedynczym celem.
   * 
   * @tparam TShooter Typ obiektu strzelającego (np. Enemy).
   * @tparam TTarget Typ obiektu celu (np. Player).
   * @param shooters Referencja do wektora obiektów strzelających.
   * @param target Referencja do pojedynczego obiektu będącego celem.
   */
  template <typename TShooter, typename TTarget>
  void CheckCollisions(std::vector<TShooter>& shooters, TTarget& target)
  {
    if (target.IsDead()) return;

    for (auto& shooter : shooters)
    {
      for (auto& projectile : shooter.GetProjectiles())
      {
        if (!projectile.IsActive()) continue;

        Rectangle projRect = {
          projectile.GetPosition().x - projectile.GetRadius(),
          projectile.GetPosition().y - projectile.GetRadius(),
          projectile.GetRadius() * 2, projectile.GetRadius() * 2
        };

        if (CheckCollisionRecs(projRect, target.GetBounds()))
        {
          target.TakeDamage();
          projectile.SetActive(false);
        }
      }
    }
  }

  /**
   * @brief Sprawdza kolizje pomiędzy pojedynczym strzelcem a wektorem celów.
   * 
   * @tparam TShooter Typ obiektu strzelającego (np. Player).
   * @tparam TTarget Typ obiektu celu (np. Enemy, Bunker).
   * @param shooter Referencja do pojedynczego obiektu strzelającego.
   * @param targets Referencja do wektora obiektów będących celami.
   */
  template <typename TShooter, typename TTarget>
  void CheckCollisionsSingleShooter(TShooter& shooter, std::vector<TTarget>& targets)
  {
    for (auto& projectile : shooter.GetProjectiles())
    {
      if (!projectile.IsActive()) continue;

      Rectangle projRect = {
        projectile.GetPosition().x - projectile.GetRadius(),
        projectile.GetPosition().y - projectile.GetRadius(),
        projectile.GetRadius() * 2, projectile.GetRadius() * 2
      };

      for (auto& target : targets)
      {
        if (target.IsDead()) continue;

        if (CheckCollisionRecs(projRect, target.GetBounds()))
        {
          target.TakeDamage();
          projectile.SetActive(false);
          break;  // Pocisk zniszczony, nie rani kolejnych celów
        }
      }
    }
  }
};