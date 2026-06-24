#include "raylib.h"

bool PAUSE = false;

void PauseMenu()
{
  if (IsKeyPressed(KEY_ESCAPE)) PAUSE = !PAUSE;
  if (PAUSE) DrawText("PAUSED", 350, 200, 30, GRAY);
}