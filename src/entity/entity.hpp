#pragma once
#include <raylib.h>

/**
 * @brief Abstrakcyjna klasa bazowa dla wszystkich bytów w grze.
 * 
 * Klasa Entity definiuje wspólny interfejs dla obiektów takich jak gracz,
 * wrogowie czy bunkry, nakazując implementację metod aktualizacji i rysowania.
 */
class Entity
{
 protected:
  Vector2 position; ///< Pozycja obiektu na ekranie 2D.
  float speed;      ///< Szybkość poruszania się obiektu.

 public:
  /**
   * @brief Zwalnia zasoby wirtualnej klasy bazowej.
   */
  virtual ~Entity() = default;

  /**
   * @brief Aktualizuje logikę obiektu (np. ruch, strzelanie).
   * 
   * Funkcja wywoływana raz na klatkę (frame) dla każdego obiektu dziedziczącego.
   */
  virtual void Update() = 0;

  /**
   * @brief Rysuje obiekt na ekranie.
   * 
   * Funkcja wywoływana wewnątrz pętli BeginDrawing/EndDrawing.
   */
  virtual void Draw() = 0;

  /**
   * @brief Pobiera aktualną pozycję obiektu.
   * 
   * @return Wektor 2D reprezentujący pozycję (x, y).
   */
  Vector2 GetPosition() const;
};