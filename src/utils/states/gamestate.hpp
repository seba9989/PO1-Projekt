#pragma once

/**
 * @brief Stany gry do zarządzania główną pętlą (maszyna stanów).
 */
enum class GameState {
    MENU,           ///< Ekran główny gry.
    HELP,           ///< Ekran pomocy ze sterowaniem.
    PLAYING,        ///< Właściwa rozgrywka.
    GAMEOVER,       ///< Ekran po utracie żyć (nieużywany po usunięciu przejścia na rzecz NAME_INPUT).
    NAME_INPUT,     ///< Ekran wpisywania nicku do tabeli wyników po zgonie.
    LEADERBOARD     ///< Tablica najlepszych wyników (Highscores).
};
