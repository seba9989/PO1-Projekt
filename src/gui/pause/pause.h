#pragma once
#include "raylib.h"

/**
 * @brief Globalna flaga pauzy.
 * Jeśli true, pętla gry zostaje zamrożona.
 */
extern bool PAUSE;

/**
 * @brief Rysuje menu pauzy oraz obsługuje logikę klawisza Esc.
 */
void PauseMenu();