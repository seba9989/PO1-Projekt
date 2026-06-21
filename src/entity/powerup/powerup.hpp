#pragma once
#include "raylib.h"
#include "../entity.hpp"

/**
 * @brief Typy zrzutów zaopatrzenia.
 */
enum class PowerUpType {
    HEAL,           ///< Skrzynka lecząca gracza (+1 HP).
    DOUBLE_SHOT     ///< Skrzynka dająca podwójny strzał.
};

/**
 * @brief Klasa reprezentująca bonus wypadający ze zniszczonych wrogów.
 */
class PowerUp : public Entity {
public:
    bool active;
    PowerUpType type; ///< Rodzaj bonusu zdefiniowany z enum.

    /**
     * @brief Inicjalizuje nową skrzynkę bonusową w podanym miejscu.
     * 
     * @param position Początkowa pozycja skrzynki.
     */
    PowerUp(Vector2 position);

    /**
     * @brief Aktualizuje pozycję skrzynki (opadanie w dół ekranu).
     */
    void Update() override;

    /**
     * @brief Rysuje skrzynkę na ekranie.
     */
    void Draw() override;

    /**
     * @brief Zwraca obwiednię kolizji skrzynki.
     * @return Rectangle reprezentujący granice.
     */
    Rectangle GetBounds() const;
};
