#include "ufo.hpp"
#include <cstdlib>

Ufo::Ufo() {
    active = false;
    speed = 3.0f;
    popupTimer = 0.0f;
    scoreValue = 0;
    lastScore = 0;
}

void Ufo::Spawn() {
    active = true;
    
    // UFO pojawia się z lewej lub prawej strony
    bool fromLeft = (GetRandomValue(0, 1) == 0);
    
    // Y ustawiamy na 280 (pomiędzy wrogami a bunkrami/graczem)
    position.y = 280.0f; 
    
    if (fromLeft) {
        position.x = -40.0f;
        speed = 3.0f; // w prawo
    } else {
        position.x = GetScreenWidth() + 40.0f;
        speed = -3.0f; // w lewo
    }
    
    // Losowa wartość od 500 do 1500 (krok co 500)
    scoreValue = GetRandomValue(1, 3) * 500;
}

void Ufo::Update() {
    // Licznik dla napisu bonusowego
    if (popupTimer > 0) {
        popupTimer -= GetFrameTime();
    }

    if (!active) return;

    position.x += speed;

    // Jeżeli przeleci za ekran, dezaktywuj
    if (position.x > GetScreenWidth() + 50.0f || position.x < -50.0f) {
        active = false;
    }
}

void Ufo::Draw() {
    // Rysowanie wyskakującego napisu
    if (popupTimer > 0) {
        DrawText(TextFormat("+%d", lastScore), deathPos.x, deathPos.y, 20, YELLOW);
    }

    if (!active) return;

    // Rysowanie UFO (żółty kolor wg prośby)
    float x = position.x;
    float y = position.y;

    // Czasza górna
    DrawRectangle(x + 10, y, 20, 10, YELLOW);
    // Pierścień środkowy
    DrawRectangle(x, y + 10, 40, 10, YELLOW);
    // Dolne "światła" lub dno
    DrawRectangle(x + 5, y + 20, 10, 5, YELLOW);
    DrawRectangle(x + 25, y + 20, 10, 5, YELLOW);
}

Rectangle Ufo::GetBounds() const {
    return { position.x, position.y, 40.0f, 25.0f };
}
