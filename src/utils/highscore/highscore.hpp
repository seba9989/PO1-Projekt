#pragma once
#include <vector>
#include <string>

/**
 * @brief Struktura przechowująca pojedynczy wynik.
 */
struct ScoreEntry {
    std::string name;
    int score;
};

/**
 * @brief Zarządca wyników odczytujący i zapisujący dane do pliku tekstowego.
 */
class HighscoreManager {
private:
    std::string filepath;
    std::vector<ScoreEntry> scores;

public:
    /**
     * @brief Inicjalizuje obiekt zarządzający wynikami.
     * 
     * @param path Ścieżka do pliku z wynikami.
     */
    HighscoreManager(const std::string& path = "highscores.txt");

    /**
     * @brief Odczytuje wyniki z pliku tekstowego do pamięci programu.
     */
    void LoadScores();

    /**
     * @brief Dodaje nowy wynik, sortuje listę i zapisuje do pliku.
     * 
     * @param name Nazwa gracza.
     * @param score Ilość zdobytych punktów.
     */
    void AddScore(const std::string& name, int score);

    /**
     * @brief Pobiera wybraną liczbę najlepszych wyników graczy.
     * 
     * @param count Liczba wyników do pobrania.
     * @return Zwraca wektor struktur ScoreEntry.
     */
    std::vector<ScoreEntry> GetTopScores(int count = 5) const;
};
