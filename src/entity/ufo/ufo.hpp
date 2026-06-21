#pragma once
#include <raylib.h>
#include <raymath.h>
#include "../entity.hpp"

/**
 * @brief Klasa statku matki (UFO), pojawiającego się sporadycznie jako cel bonusowy.
 */
class Ufo : public Entity {
public:
    bool active;        ///< Flaga wskazująca, czy UFO jest na ekranie.
    int scoreValue;     ///< Wartość punktowa, jaką UFO daje po zestrzeleniu.
    float popupTimer;   ///< Czas (w sekundach) wyświetlania informacji o zdobytym bonusie.
    Vector2 deathPos;   ///< Pozycja, w której UFO zostało zniszczone (dla wyświetlenia napisu).
    int lastScore;      ///< Zapisany wynik punktowy z ostatniego zestrzelenia.

    /**
     * @brief Inicjalizuje obiekt statku UFO.
     */
    Ufo();

    /**
     * @brief Aktualizuje pozycję UFO i licznik napisu bonusowego.
     */
    void Update() override;

    /**
     * @brief Rysuje UFO na ekranie, lub animację napisu bonusowego po jego śmierci.
     */
    void Draw() override;

    /**
     * @brief Aktywuje UFO i ustala jego pozycję oraz losową wartość punktową.
     */
    void Spawn();

    /**
     * @brief Zwraca obwiednię kolizji UFO.
     * @return Rectangle określający wymiary UFO do wykrywania zderzeń.
     */
    Rectangle GetBounds() const;
};
