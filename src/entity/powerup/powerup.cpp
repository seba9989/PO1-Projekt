#include "powerup.hpp"

PowerUp::PowerUp(Vector2 position) {
    this->position = position;
    this->active = true;
    this->speed = 2.0f; // Szybkość opadania
    // Losujemy typ skrzynki (50% HEAL, 50% DOUBLE_SHOT)
    this->type = (GetRandomValue(0, 1) == 0) ? PowerUpType::HEAL : PowerUpType::DOUBLE_SHOT;
}

void PowerUp::Update() {
    if (!active) return;
    
    position.y += speed;

    // Dezaktywuj jeśli wyleci za dół ekranu
    if (position.y > GetScreenHeight()) {
        active = false;
    }
}

void PowerUp::Draw() {
    if (!active) return;
    // Różny kolor w zależności od typu
    Color boxColor = (type == PowerUpType::HEAL) ? GREEN : SKYBLUE;
    DrawRectangleV(position, { 15.0f, 15.0f }, boxColor);
    DrawText((type == PowerUpType::HEAL) ? "+" : "x2", position.x + ((type == PowerUpType::HEAL) ? 3.0f : 1.0f), position.y + 1.0f, 15, WHITE);
}

Rectangle PowerUp::GetBounds() const {
    return { position.x, position.y, 15.0f, 15.0f };
}
