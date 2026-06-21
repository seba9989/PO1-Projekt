#pragma once
#include <raylib.h>
#include <entity/entity.hpp>

/**
 * @brief Klasa reprezentująca pojedynczy blok bunkra.
 *
 * Bunkier jest niszczalną przesłoną (voxel-like), składającą się z wielu takich
 * bloków. Każdy blok ma domyślnie 1 HP, więc niszczy się od pojedynczego
 * trafienia.
 */
class Bunker : public Entity
{
 private:
  int hp = 1;            ///< Aktualne punkty życia bloku bunkra.
  int maxHp = 1;         ///< Maksymalne punkty życia bloku bunkra.
  float width = 10.0f;   ///< Szerokość pojedynczego bloku w pikselach.
  float height = 10.0f;  ///< Wysokość pojedynczego bloku w pikselach.

 public:
  /**
   * @brief Inicjalizuje pojedynczy blok bunkra.
   * @param position Pozycja startowa (lewy górny róg) bloku.
   */
  Bunker(Vector2 position);

  /**
   * @brief Zwalnia zasoby bloku bunkra.
   */
  ~Bunker() = default;

  /**
   * @brief Aktualizuje logikę bloku (obecnie blok jest statyczny, więc nic nie
   * robi).
   */
  void Update() override;

  /**
   * @brief Rysuje blok bunkra na ekranie.
   */
  void Draw() override;

  /**
   * @brief Zwraca granice kolizji bloku bunkra.
   * @return Prostokąt kolizyjny obiektu.
   */
  Rectangle GetBounds() const;

  /**
   * @brief Zadaje obrażenia blokowi (redukuje HP do 0).
   */
  void TakeDamage();

  /**
   * @brief Sprawdza czy blok został zniszczony.
   * @return true jeśli hp <= 0.
   */
  bool IsDead() const;
};
