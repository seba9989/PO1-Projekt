#pragma once
#include "raylib.h"

/**
 * @brief Klasa reprezentująca pocisk (laser).
 * 
 * Może zostać wystrzelony zarówno przez gracza jak i wroga. 
 * Posiada swój kierunek, prędkość i rozmiar.
 */
class Projectile
{
 private:
  Vector2 position = {}; ///< Aktualna pozycja pocisku.
  float speed = 4.0f;    ///< Prędkość przemieszczania się pocisku.
  bool active = true;    ///< Status pocisku (false oznacza, że powinien zostać usunięty).
  int direction = -1;    ///< Kierunek lotu: -1 = w górę (gracz), +1 = w dół (wróg).

 public:
  /**
   * @brief Inicjalizuje obiekt pocisku.
   * 
   * @param position Pozycja startowa pocisku.
   * @param direction Kierunek (-1 dla gracza, 1 dla wroga). Domyślnie -1.
   * @param speed Szybkość lotu pocisku. Domyślnie 4.0f.
   */
  Projectile(Vector2 position, int direction = -1, float speed = 4.0f);

  /**
   * @brief Zwalnia zasoby pocisku.
   */
  ~Projectile();

  /**
   * @brief Aktualizuje logikę pocisku (przesuwa w zadanym kierunku).
   */
  void Update();

  /**
   * @brief Rysuje pocisk (prostokątny laser) na ekranie.
   */
  void Draw();

  /**
   * @brief Sprawdza, czy pocisk wyleciał poza górną lub dolną krawędź ekranu.
   * @return true jeśli pocisk znajduje się poza ekranem.
   */
  bool IsOutOfBounds() const;

  /**
   * @brief Sprawdza, czy pocisk jest wciąż aktywny w grze.
   * @return true jeśli aktywny.
   */
  bool IsActive() const;

  /**
   * @brief Pobiera aktualną pozycję pocisku.
   * @return Wektor 2D z pozycją (x,y).
   */
  Vector2 GetPosition() const;

  /**
   * @brief Pobiera promień kolizji (lub połowę szerokości) pocisku.
   * @return Promień pocisku w pikselach.
   */
  float GetRadius() const;

  /**
   * @brief Ustawia status aktywności pocisku (np. po trafieniu zmieniany na false).
   * @param active Nowy status aktywności.
   */
  void SetActive(bool active);
};