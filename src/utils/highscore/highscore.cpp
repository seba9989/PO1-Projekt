#include "highscore.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

HighscoreManager::HighscoreManager(const std::string& path) : filepath(path) {
    LoadScores();
}

void HighscoreManager::LoadScores() {
    scores.clear();
    std::ifstream file(filepath);
    if (!file.is_open()) return;

    std::string name;
    int score;
    while (file >> name >> score) {
        scores.push_back({name, score});
    }
    file.close();

    // Sort descending by score
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });
}

void HighscoreManager::AddScore(const std::string& name, int score) {
    // If name is empty, provide a default
    std::string safeName = name.empty() ? "UNKNOWN" : name;
    
    // Replace spaces with underscores to prevent parsing issues
    std::replace(safeName.begin(), safeName.end(), ' ', '_');

    // Sprawdź czy dany gracz już istnieje na liście
    auto it = std::find_if(scores.begin(), scores.end(), [&safeName](const ScoreEntry& e) {
        return e.name == safeName;
    });

    if (it != scores.end()) {
        // Jeśli istnieje, zaktualizuj wynik tylko jeśli nowy jest wyższy
        if (score > it->score) {
            it->score = score;
        }
    } else {
        // Jeśli nie istnieje, dodaj nowy wpis
        scores.push_back({safeName, score});
    }
    
    // Sort descending
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.score > b.score;
    });

    // Save back to file
    std::ofstream file(filepath);
    if (file.is_open()) {
        for (const auto& entry : scores) {
            file << entry.name << " " << entry.score << "\n";
        }
        file.close();
    }
}

std::vector<ScoreEntry> HighscoreManager::GetTopScores(int count) const {
    std::vector<ScoreEntry> top;
    for (size_t i = 0; i < scores.size() && i < (size_t)count; ++i) {
        top.push_back(scores[i]);
    }
    return top;
}
