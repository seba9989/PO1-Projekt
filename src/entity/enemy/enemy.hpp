#pragma once
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include "../projectile/projectile.hpp"
#include <entity/entity.hpp>

/**
 * @brief Klasa reprezentująca wrogiego kosmitę.
 *
 * Kosmici poruszają się wspólnie w rzędach i kolumnach, mogą schodzić w dół
 * ekranu i strzelać własnymi pociskami.
 */
class Enemy : public Entity
{
 private:
  float hp = 3;  ///< Punkty życia wroga.
  std::vector<Color> color_s = {
    RED, ORANGE, BLUE
  };  ///< Paleta kolorów wskazująca stan HP.
  std::vector<Projectile> projectile_s = {};  ///< Kontener aktywnych pocisków
                                              ///< wystrzelonych przez wroga.
  int projectileCountMax =
      1;  ///< Maksymalna liczba pocisków wroga jednocześnie na ekranie.

  float margin = 24.0f;     ///< Margines ekranu używany do detekcji nawrotów.
  float width = 30.0f;      ///< Szerokość prostokąta wroga.
  float height = 25.0f;     ///< Wysokość prostokąta wroga.
  float dropAmount = 5.0f;  ///< O ile pikseli w dół przesuwa się wróg przy
                            ///< dojściu do krawędzi.

 public:
  static int moveDirection;  ///< Globalny kierunek ruchu wszystkich wrogów (1 =
                             ///< prawo, -1 = lewo).
  static bool needsDropDown;  ///< Flaga wskazująca, czy cała fala musi
                              ///< przesunąć się w dół (ktoś dotknął krawędzi).

  bool canShoot = false;  ///< Flaga logiczna determinująca, czy dany wróg jest
                          ///< w linii frontu i może strzelać.
  int shootChance =
      100;      ///< Szansa na strzał w każdej klatce (losowanie z przedziału).
  int row = 0;  ///< Indeks rzędu wroga w fali (0 to najwyższy).
  int col = 0;  ///< Indeks kolumny wroga w fali.

  /**
   * @brief Inicjalizuje wroga (ustawia w centrum ekranu).
   */
  Enemy();

  /**
   * @brief Inicjalizuje wroga dla trybu fali.
   *
   * @param position Pozycja początkowa na ekranie.
   * @param row Rząd wroga (liczony od góry).
   * @param col Kolumna wroga (liczona od lewej).
   * @param level Aktualny poziom gry (determinuje prędkość strzelania i ruchu).
   */
  Enemy(Vector2 position, int row, int col, int level = 1);

  /**
   * @brief Zwalnia zasoby wroga.
   */
  ~Enemy();

  /**
   * @brief Aktualizuje pozycję wroga oraz obsługuje logikę losowego strzelania.
   */
  void Update() override;

  /**
   * @brief Rysuje wroga oraz jego pociski na ekranie.
   */
  void Draw() override;

  /**
   * @brief Wymusza opadnięcie wroga o `dropAmount` pikseli w dół.
   */
  void DropDown();

  /**
   * @brief Inicjuje wystrzelenie pocisku przez wroga (w kierunku gracza).
   */
  void Shoot();

  /**
   * @brief Zwraca promień (rozmiar) wroga.
   * @return Promień/szerokość używana m.in. przy niektórych kolizjach.
   */
  float GetRadius() const;

  /**
   * @brief Oblicza i zwraca prostokątny obszar zajmowany przez wroga (kolizja).
   * @return Obiekt Rectangle otaczający przeciwnika.
   */
  Rectangle GetBounds() const;

  /**
   * @brief Zadaje wrogowi obrażenia (redukuje HP).
   */
  void TakeDamage();

  /**
   * @brief Sprawdza czy wróg zginął (hp <= 0).
   * @return true jeśli martwy, false w przeciwnym razie.
   */
  bool IsDead() const;

  /**
   * @brief Zwraca wektor pocisków wystrzelonych przez tego wroga.
   * @return Referencja do kolekcji obiektów Projectile.
   */
  std::vector<Projectile>& GetProjectiles();
};